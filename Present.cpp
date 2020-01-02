#include "Main.h"
#include "imgui_internal.h"
#include "mrc.hpp"
#include "Variables.h"

Options g_Options;

IDirect3DStateBlock9* pixel_state = NULL; IDirect3DVertexDeclaration9* vertDec; IDirect3DVertexShader9* vertShader;
DWORD dwOld_D3DRS_COLORWRITEENABLE;
PresentFn oPresent;

tReset oResetScene;

void SaveState(IDirect3DDevice9* pDevice)
{
	pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
	pDevice->GetVertexDeclaration(&vertDec);
	pDevice->GetVertexShader(&vertShader);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_SRGBTEXTURE, NULL);
}

void RestoreState(IDirect3DDevice9* pDevice) // not restoring everything. Because it's not needed.
{
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, true);
	pDevice->SetVertexDeclaration(vertDec);
	pDevice->SetVertexShader(vertShader);
}

namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	IMGUI_API bool ComboBoxArray(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

	void SelectTabs(int *selected, const char* items[], int item_count, ImVec2 size = ImVec2(0, 0))
	{
		auto color_grayblue = GetColorU32(ImVec4(0.48f, 0.48f, 0.48f, 0.20f));
		auto color_deepblue = GetColorU32(ImVec4(0.12f, 0.12f, 0.12f, 0.15f));
		auto color_shade_hover = GetColorU32(ImVec4(0.8f, 0.8f, 0.8f, 0.05f));
		auto color_shade_clicked = GetColorU32(ImVec4(0.1f, 0.1f, 0.1f, 0.1f));
		auto color_black_outlines = GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

		ImGuiStyle &style = GetStyle();

		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return;

		std::string names;
		for (size_t i = 0; i < static_cast<unsigned>(item_count); i++)
			names += items[i];

		ImGuiContext* g = GImGui;
		const ImGuiID id = window->GetID(names.c_str());
		const ImVec2 label_size = CalcTextSize(names.c_str(), NULL, true);

		ImVec2 Min = window->DC.CursorPos;
		ImVec2 Max = ((size.x <= 0 || size.y <= 0) ? ImVec2(Min.x + GetContentRegionMax().x - style.WindowPadding.x, Min.y + label_size.y * 2) : Min);

		ImRect bb(Min, Max);
		ItemSize(bb, style.FramePadding.y);
		if (!ItemAdd(bb, &id))
			return;

		PushClipRect(ImVec2(Min.x, Min.y - 1), ImVec2(Max.x, Max.y + 1), false);

		window->DrawList->AddRectFilledMultiColor(Min, Max, color_grayblue, color_grayblue, color_deepblue, color_deepblue); // Main gradient.

		ImVec2 mouse_pos = GetMousePos();
		bool mouse_click = g->IO.MouseClicked[0];

		float TabSize = ceil((Max.x - Min.x) / item_count);

		for (size_t i = 0; i < static_cast<unsigned>(item_count); i++)
		{
			ImVec2 Min_cur_label = ImVec2(Min.x + (int)TabSize * i, Min.y);
			ImVec2 Max_cur_label = ImVec2(Min.x + (int)TabSize * i + (int)TabSize, Max.y);

			// Imprecision clamping. gay but works :^)
			Max_cur_label.x = (Max_cur_label.x >= Max.x ? Max.x : Max_cur_label.x);

			if (mouse_pos.x > Min_cur_label.x && mouse_pos.x < Max_cur_label.x &&
				mouse_pos.y > Min_cur_label.y && mouse_pos.y < Max_cur_label.y)
			{
				if (mouse_click)
					*selected = i;
				else if (i != *selected)
					window->DrawList->AddRectFilled(Min_cur_label, Max_cur_label, color_shade_hover);
			}

			if (i == *selected) {
				window->DrawList->AddRectFilled(Min_cur_label, Max_cur_label, color_shade_clicked);
				window->DrawList->AddRectFilledMultiColor(Min_cur_label, Max_cur_label, color_deepblue, color_deepblue, color_grayblue, color_grayblue);
				window->DrawList->AddLine(ImVec2(Min_cur_label.x - 1.5f, Min_cur_label.y - 1), ImVec2(Max_cur_label.x - 0.5f, Min_cur_label.y - 1), color_black_outlines);
			}
			else
				window->DrawList->AddLine(ImVec2(Min_cur_label.x - 1, Min_cur_label.y), ImVec2(Max_cur_label.x, Min_cur_label.y), color_black_outlines);
			window->DrawList->AddLine(ImVec2(Max_cur_label.x - 1, Max_cur_label.y), ImVec2(Max_cur_label.x - 1, Min_cur_label.y - 0.5f), color_black_outlines);

			const ImVec2 text_size = CalcTextSize(items[i], NULL, true);
			float pad_ = style.FramePadding.x + g->FontSize + style.ItemInnerSpacing.x;
			ImRect tab_rect(Min_cur_label, Max_cur_label);
			RenderTextClipped(Min_cur_label, Max_cur_label, items[i], NULL, &text_size, style.WindowTitleAlign, &tab_rect);
		}

		window->DrawList->AddLine(ImVec2(Min.x, Min.y - 0.5f), ImVec2(Min.x, Max.y), color_black_outlines);
		window->DrawList->AddLine(ImVec2(Min.x, Max.y), Max, color_black_outlines);
		PopClipRect();
	}
}
void GUI_Init(IDirect3DDevice9* pDevice)
{
	ImGui_ImplDX9_Init(g_Globals->CSGOWindow, pDevice);

	ImGuiStyle        _style = ImGui::GetStyle();

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.71f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.06f, 0.06f, 0.06f, 0.01f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.71f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.07f, 0.07f, 0.07f, 0.48f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.07f, 0.48f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.07f, 0.07f, 0.07f, 0.48f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.66f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.00f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.37f, 0.00f, 0.12f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.44f, 0.00f, 0.13f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.00f, 0.27f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.00f, 0.23f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.00f, 0.23f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(1.00f, 0.00f, 0.30f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 0.00f, 0.30f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.00f, 0.33f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.10f, 0.10f, 0.10f, 0.90f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(1.00f, 0.00f, 0.33f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 0.00f, 0.36f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_CloseButton] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_CloseButtonHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_CloseButtonActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.00f, 0.30f, 0.35f);
	colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

	_style.WindowPadding = ImVec2(8, 8);      // Padding within a window
	_style.WindowMinSize = ImVec2(32, 32);    // Minimum window size
	_style.WindowRounding = 9.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
	_style.WindowTitleAlign = ImVec2(5.f, 0.5f);// Alignment for title bar text
	_style.FramePadding = ImVec2(4, 3);      // Padding within a framed rectangle (used by most widgets)
	_style.FrameRounding = 0.0f;             // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
	_style.ItemSpacing = ImVec2(0, 4);      // Horizontal and vertical spacing between widgets/lines
	_style.ItemInnerSpacing = ImVec2(4, 4);      // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
	_style.TouchExtraPadding = ImVec2(0, 0);      // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
	_style.IndentSpacing = 21.0f;            // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
	_style.ColumnsMinSpacing = 6.0f;             // Minimum horizontal spacing between two columns
	_style.ScrollbarSize = 8.0f;            // Width of the vertical scrollbar, Height of the horizontal scrollbar
	_style.ScrollbarRounding = 9.0f;             // Radius of grab corners rounding for scrollbar
	_style.GrabMinSize = 10.0f;            // Minimum width/height of a grab box for slider/scrollbar
	_style.GrabRounding = 0.0f;             // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
	_style.ButtonTextAlign = ImVec2(0.5f, 0.5f);// Alignment of button text when button is larger than text.
	_style.DisplayWindowPadding = ImVec2(22, 22);    // Window positions are clamped to be visible within the display area by at least this amount. Only covers regular windows.
	_style.DisplaySafeAreaPadding = ImVec2(4, 4);      // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
	_style.AntiAliasedLines = true;             // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
	_style.CurveTessellationTol = 1.25f;            // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
	
	Drawing::GetInstance().InitDeviceObjects(pDevice);
	
	Global::init = true;
}
typedef void(*CL_FullUpdate_t) (void);
CL_FullUpdate_t CL_FullUpdate = nullptr;

void KnifeApplyCallbk()
{
	static auto CL_FullUpdate = reinterpret_cast<CL_FullUpdate_t>(g_Utils->FindPattern("engine.dll", reinterpret_cast<PBYTE>("\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x56\xFF\x50\x14\x8B\x34\x85"), "x????x????xxxxxxx"));
	CL_FullUpdate();
}
bool t;
void draw_menu()
{
	static int antiAimTab = 0;
	if (G_Engine->IsInGame() && G_Engine->IsConnected())
		ImGui::GetIO().MouseDrawCursor = g_Vars->Menu.Opened;
	else
		ImGui::GetIO().MouseDrawCursor = true;

	ImGui_ImplDX9_NewFrame();

	if (g_Vars->Menu.Opened)
		t = true;
	else
		t = false;

	if (t)
	{
		static const char* tabs[] = {
			"       ragebot",
			"       legitbot",
			"       visuals",
			"         misc"
		};

		ImGui::SetNextWindowSize(ImVec2(800, 600));
		ImGui::Begin("Vengeance", &g_Vars->Menu.Opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
		{
			static int pages = 0;
			ImGui::SelectTabs(&pages, tabs, ARRAYSIZE(tabs));
			switch (pages)
			{
			case 0:
			{
				ImGui::Columns(1, NULL, false);
				{
					ImGui::BeginChild("RAGECHILD", ImVec2(0, 0), true);
					{
						if (ImGui::CollapsingHeader("Ragebot##Header"))
						{
							ImGui::Columns(1, NULL, true);
							{
								ImGui::Checkbox("Enable", &g_Options.ragebotEnable);
								ImGui::Checkbox("Auto Fire", &g_Options.ragebotAutoFire);
								ImGui::Checkbox("RCS", &g_Options.ragebotRecoil);
								ImGui::Checkbox("Backtrack", &g_Options.ragebotBacktrack);
								ImGui::Checkbox("Hitchance Enable", &g_Options.ragebotHitchanceEnable);
								if (g_Options.ragebotHitchanceEnable)
									ImGui::SliderFloat("Hitchance", &g_Options.ragebotHitchanceAmount, 0, 100, "%.3f");
								ImGui::SliderFloat("Pointscale", &g_Options.ragebotPointscale, 0.0f, 1.0f, "%.3f");
								/*ImGui::SliderInt("Multipoint", &g_Options.aimbot_mp_slicing, 0, 100, "%.0f");
								ImGui::SliderInt("Min Damage", &g_Options.aimbot_mindamage, 0, 100, "%.0f");
								ImGui::Combo("lagcomp", &g_Options.lagcomp_level, lcompmode, lcount);*/
								ImGui::Checkbox("Corrections", &g_Options.ragebotCorrections);
							}
							ImGui::Columns(1);
							ImGui::Separator();
							if (ImGui::CollapsingHeader("Hitboxes##Header"))
							{
								for (int i = 0; i < hitboxListCount; i++)
								{
									ImGui::Selectable(hitboxList[i], g_Options.ragebotHitboxes + i);
								}
							}
						}
						ImGui::Separator();
						ImGui::Columns(1, NULL, true);

						if (ImGui::CollapsingHeader("AntiAim##Header"))
						{
							ImGui::Checkbox("AntiAim##Enable", &g_Options.antiAimEnable);
							ImGui::Separator();

							ImGui::Checkbox("Fake##Enable", &g_Options.antiAimFake);

							if (g_Options.allowUntrusted)
							{
								ImGui::Combo("Pitch", &g_Options.antiAimPitch, utPitch, utPitchCount);
								if (g_Options.antiAimPitch == 1)
								{
									ImGui::SliderFloat("Custom Pitch", &g_Options.antiAimPitchCustom, -1440.0, 1440.0, "%.3f", 1.0f);
								}
							}
							else
							{
								//g_Options.antiAimPitchFloat = max(-89.0, min(89.0, g_Options.antiAimPitch));

								if (g_Options.antiAimPitch > 4)
								{
									switch (g_Options.antiAimPitch)
									{
									case 5:
										g_Options.antiAimPitch = 2;
										break;
									case 6:
										g_Options.antiAimPitch = 3;
										break;
									case 7:
										g_Options.antiAimPitch = 4;
										break;
									case 8:
										g_Options.antiAimPitch = 2;
										break;
									case 9:
										g_Options.antiAimPitch = 4;
										break;
									default:
										g_Options.antiAimPitch = 0;
										break;
									}
								}

								ImGui::Combo("Pitch", &g_Options.antiAimPitch, pitch, pitchCount);

								if (g_Options.antiAimPitch == 1)
								{
									ImGui::SliderFloat("Custom Pitch", &g_Options.antiAimPitchCustom, -89.0, 89.0, "%.3f", 1.0f);
								}
							}

							ImGui::Separator();

							if (ImGui::Button("Still", ImVec2(135, 24))) antiAimTab = 0;
							ImGui::SameLine();
							if (ImGui::Button("Moving", ImVec2(135, 24))) antiAimTab = 1;
							ImGui::SameLine();
							if (ImGui::Button("Jumping", ImVec2(135, 24))) antiAimTab = 2;

							ImGui::Separator();

							AntiAimSetting *real;
							AntiAimSetting *fake;

							switch (antiAimTab)
							{
							case 0:
								ImGui::Text("Still AntiAim");

								real = &g_Options.antiAimStillReal;
								fake = &g_Options.antiAimStillFake;

								break;
							case 1:
								ImGui::Text("Moving AntiAim");

								real = &g_Options.antiAimMovingReal;
								fake = &g_Options.antiAimMovingFake;

								break;
							case 2:
								ImGui::Text("Jumping AntiAim");

								real = &g_Options.antiAimJumpingReal;
								fake = &g_Options.antiAimJumpingFake;

								break;
							default:
								return;
							}

							ImGui::Separator();

							ImGui::Columns(g_Options.antiAimFake ? 2 : 1, "aacols", false);

							ImGui::Text("Real");

							ImGui::Combo("Base##Real", &real->base, baseYaws, baseYawsCount);
							ImGui::SliderFloat("Add##Real", &real->add, -180.0f, 180.0f, "%.2f");
							ImGui::Combo("Addon##Real", &real->addon, addons, addonsCount);

							switch (real->addon)
							{
								// Jitter
							case 1:
								ImGui::Combo("Jitter Mode##Real", &real->jitterMode, jitterModes, jitterModesCount);
								if (real->jitterMode == 1)
									ImGui::SliderInt("Jitter Flip Ticks##Real", &real->jitterFlipTicks, 1, 20, "%.0f");
								ImGui::SliderFloat("Jitter Range##Real", &real->jitterRange, 0.0f, 360.0f, "%.2f");
								break;
								// Spinbot
							case 2:
								ImGui::Combo("Spinbot Mode##Real", &real->spinbotMode, spinbotModes, spinbotModesCount);
								ImGui::SliderFloat("Spinbot Speed##Real", &real->spinbotSpeed, -10.0f, 10.0f, "%.2f");
								ImGui::SliderFloat("Spinbot Range##Real", &real->spinbotRange, 0.0f, 360.0f, "%.2f");
								break;
							}

							if (g_Options.antiAimFake)
							{
								ImGui::NextColumn();

								ImGui::Text("Fake");

								ImGui::Combo("Base##Fake", &fake->base, baseYaws, baseYawsCount);
								ImGui::SliderFloat("Add##Fake", &fake->add, -180.0f, 180.0f, "%.2f");
								ImGui::Combo("Addon##Fake", &fake->addon, addons, addonsCount);

								switch (fake->addon)
								{
									// Jitter
								case 1:
									ImGui::Combo("Jitter Mode##Fake", &fake->jitterMode, jitterModes, jitterModesCount);
									if (fake->jitterMode == 1)
										ImGui::SliderInt("Jitter Flip Ticks##Fake", &fake->jitterFlipTicks, 1, 20, "%.0f");
									ImGui::SliderFloat("Jitter Range##Fake", &fake->jitterRange, 0.0f, 360.0f, "%.2f");
									break;
									// Spinbot
								case 2:
									ImGui::Combo("Spinbot Mode##Fake", &fake->spinbotMode, spinbotModes, spinbotModesCount);
									ImGui::SliderFloat("Spinbot Speed##Fake", &fake->spinbotSpeed, -10.0f, 10.0f, "%.2f");
									ImGui::SliderFloat("Spinbot Range##Fake", &fake->spinbotRange, 0.0f, 360.0f, "%.2f");
									break;
								}
							}

							ImGui::Columns(1);

							ImGui::Separator();

							ImGui::Checkbox("LBY Breaker", &g_Options.antiAimBreakLBY);
							ImGui::SliderFloat("LBY Delta", &g_Options.lbydelta, -180.0f, 180.0f);

							ImGui::Checkbox("AntiAim Flip", &g_Options.antiAimFlipEnable);
							if (g_Options.antiAimFlipEnable)
							{
								ImGui::Text("AntiAim Flip Key:");
								//ImGui::KeyBindButton(&g_Options.antiAimFlipKey);

								ImGui::Combo("AntiAim Flip Method", &g_Options.antiAimFlipMethod, flipMethods, flipMethodsCount);
							}
						}
						if (ImGui::CollapsingHeader("Freestanding Options##Header"))
						{
							ImGui::Combo("Method", &g_Options.antiAimFreestandingMethod, freestandingMethods, freestandingMethodsCount);
							if (g_Options.antiAimFreestandingMethod == 0)
							{
								ImGui::Combo("Quality", &g_Options.antiAimFreestandingQuality, freestandingQualities, freestandingQualitiesCount);
								ImGui::Combo("Scan Quality", &g_Options.antiAimFreestandingScanQuality, freestandingScanQualities, freestandingScanQualitiesCount);
								ImGui::Checkbox("Stuttered updates", &g_Options.antiAimFreestandingStutteredUpdates);
							}
							ImGui::SliderFloat("Smoothing", &g_Options.antiAimFreestandingSmoothing, 0.0f, 1.0f, "%.3f");
						}

						ImGui::EndChild();
					}
				}
			}
			break;
			case 1:
			{

			}
			break;

			case 2:
			{
				ImGui::BeginChild("VISUALSCHILD", ImVec2(0, 0), true);
				{
					ImGui::PushItemWidth(150);
					if (ImGui::Button(("Force Update")))
					{
						KnifeApplyCallbk();
					}
					if (ImGui::CollapsingHeader("ESP##Header"))
					{
						ImGui::Checkbox("ESP##Enable", &g_Options.espEnable);
						ImGui::Separator();

						ImGui::Columns(2, "espcols", false);

						/******************************** Friendly ESP ********************************/

						//ImGui::BeginChild("FriendlyESP", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.375f, 200), false);

						ImGui::Text("Friendly");
						ImGui::Checkbox("Box##Friendly", &g_Options.espFriendlyBox);
						ImGui::Checkbox("Name##Friendly", &g_Options.espFriendlyName);
						ImGui::Checkbox("Health##Friendly", &g_Options.espFriendlyHealth);
						ImGui::Checkbox("Lines##Friendly", &g_Options.espFriendlyLines);
						ImGui::Checkbox("Weapon##Friendly", &g_Options.espFriendlyWeapon);
						ImGui::Checkbox("Indicators##Friendly", &g_Options.espFriendlyIndicators);
						ImGui::Checkbox("Glow##Friendly", &g_Options.espFriendlyGlow);
						if (g_Options.espFriendlyGlow)
							ImGui::Combo("Glow Style##Friendly", &g_Options.espFriendlyGlowStyle, glowStyleList, glowStyleListCount);
						ImGui::Checkbox("Chams##Friendly", &g_Options.chamsFriendlyEnable);
						if (g_Options.chamsFriendlyEnable)
							ImGui::Combo("Chams Material##Friendly", &g_Options.chamsFriendlyMaterial, chamsMaterialList, chamsMaterialListCount);
						ImGui::Checkbox("Chams XQZ##Friendly", &g_Options.chamsFriendlyXQZEnable);
						if (g_Options.chamsFriendlyXQZEnable)
							ImGui::Combo("Chams XQZ Material##Friendly", &g_Options.chamsFriendlyXQZMaterial, chamsMaterialList, chamsMaterialListCount);
						ImGui::Checkbox("Shine##Friendly", &g_Options.espFriendlyShine);
						if (g_Options.espFriendlyShine)
							ImGui::Combo("Shine Material##Friendly", &g_Options.espFriendlyShineMaterial, shineMaterialList, shineMaterialListCount);

						//ImGui::EndChild();

						ImGui::NextColumn();

						/******************************** Enemy ESP ********************************/

						//ImGui::BeginChild("EnemyESP", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.375f, 200), false);

						ImGui::Text("Enemy");
						ImGui::Checkbox("Box##Enemy", &g_Options.espEnemyBox);
						ImGui::Checkbox("Name##Enemy", &g_Options.espEnemyName);
						ImGui::Checkbox("Health##Enemy", &g_Options.espEnemyHealth);
						ImGui::Checkbox("Lines##Enemy", &g_Options.espEnemyLines);
						ImGui::Checkbox("Weapon##Enemy", &g_Options.espEnemyWeapon);
						ImGui::Checkbox("Indicators##Enemy", &g_Options.espEnemyIndicators);
						ImGui::Checkbox("Lagcomp##Enemy", &g_Options.espEnemyLagcomp);
						ImGui::Checkbox("Glow##Enemy", &g_Options.espEnemyGlow);
						if (g_Options.espEnemyGlow)
							ImGui::Combo("Glow Style##Enemy", &g_Options.espEnemyGlowStyle, glowStyleList, glowStyleListCount);
						ImGui::Checkbox("Chams##Enemy", &g_Options.chamsEnemyEnable);
						if (g_Options.chamsEnemyEnable)
							ImGui::Combo("Chams Material##Enemy", &g_Options.chamsEnemyMaterial, chamsMaterialList, chamsMaterialListCount);
						ImGui::Checkbox("Chams XQZ##Enemy", &g_Options.chamsEnemyXQZEnable);
						if (g_Options.chamsEnemyXQZEnable)
							ImGui::Combo("Chams XQZ Material##Enemy", &g_Options.chamsEnemyXQZMaterial, chamsMaterialList, chamsMaterialListCount);
						ImGui::Checkbox("Shine##Enemy", &g_Options.espEnemyShine);
						if (g_Options.espEnemyShine)
							ImGui::Combo("Shine Material##Enemy", &g_Options.espEnemyShineMaterial, shineMaterialList, shineMaterialListCount);

						//ImGui::EndChild();

						ImGui::Columns(1);
						ImGui::Separator();

						//ImGui::BeginChild("LocalESP", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.375f, 100), false);

						ImGui::Text("Local Player");

						ImGui::Checkbox("Glow##Local", &g_Options.espLocalGlow);
						if (g_Options.espLocalGlow)
							ImGui::Combo("Glow Style##Local", &g_Options.espLocalGlowStyle, glowStyleList, glowStyleListCount);
						ImGui::Checkbox("Chams##Local", &g_Options.chamsLocalEnable);
						if (g_Options.chamsLocalEnable)
							ImGui::Combo("Chams Material##Local", &g_Options.chamsLocalMaterial, chamsMaterialList, chamsMaterialListCount);
						ImGui::Checkbox("Shine##Local", &g_Options.espLocalShine);
						if (g_Options.espLocalShine)
							ImGui::Combo("Shine Material##Local", &g_Options.espLocalShineMaterial, shineMaterialList, shineMaterialListCount);
						ImGui::Checkbox("Hand Chams##Local", &g_Options.chamsHandEnable);
						if (g_Options.chamsHandEnable)
							ImGui::Combo("Hand Chams Material##Local", &g_Options.chamsHandMaterial, chamsMaterialList, chamsMaterialListCount);

						ImGui::Checkbox("AntiAim Lines", &g_Options.antiAimLines);
						if (g_Options.antiAimLines)
						{
							ImGui::Checkbox("First Person AA Lines", &g_Options.antiAimLinesFirstPerson);

						}

						ImGui::Checkbox("AntiAim Info", &g_Options.antiAimInfo);

						ImGui::Combo("Spread Crosshair", &g_Options.spreadCrosshair, spreadCrosshairList, spreadCrosshairListCount);

						ImGui::Checkbox("Bullet Tracers", &g_Options.bulletTracersEnable);
						if (g_Options.bulletTracersEnable)
						{
							ImGui::Combo("Bullet Tracers Material", &g_Options.bulletTracersMaterial, bulletTracersMaterialList, bulletTracersMaterialListCount);
							ImGui::SliderFloat("Bullet Tracers Lifetime", &g_Options.bulletTracersLifetime, 0.0f, 5.0f, "%.3f", 1.0f);
							ImGui::SliderFloat("Bullet Tracers Width", &g_Options.bulletTracersWidth, 0.0f, 2.5f, "%.3f", 1.0f);
						}

						//ImGui::EndChild();

						ImGui::Separator();

						//ImGui::BeginChild("WeaponESP", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.375f, 100), false);

						ImGui::Text("Weapon");

						ImGui::Checkbox("Glow##Weapon", &g_Options.espWeaponGlow);
						if (g_Options.espWeaponGlow)
							ImGui::Combo("Glow Style##Weapon", &g_Options.espWeaponGlowStyle, glowStyleList, glowStyleListCount);

						ImGui::Checkbox("Chams##Weapon", &g_Options.chamsWeaponEnable);
						if (g_Options.chamsWeaponEnable)
							ImGui::Combo("Chams Material##Weapon", &g_Options.chamsWeaponMaterial, chamsMaterialList, chamsMaterialListCount);

						//ImGui::EndChild();
					}

					ImGui::Separator();

					if (ImGui::CollapsingHeader("Other##Header"))
					{
						ImGui::Checkbox("Third Person", &g_Options.thirdperson);

						ImGui::Combo("Third Person Angles", &g_Options.tpmode, tpmodee, tpcount);


						ImGui::Checkbox("Smoke Wireframe", &g_Options.smokeWireframe);

						ImGui::Checkbox("FOV Changer", &g_Options.fovEnable);

						if (g_Options.fovRelative)
							ImGui::SliderFloat("FOV", &g_Options.fov, -89.0f, 89.0f, "%.3f");
						else
							ImGui::SliderFloat("FOV", &g_Options.fov, 1.0f, 179.0f, "%.3f");
						ImGui::Checkbox("Restore FOV when scoped", &g_Options.fovRestore);
						ImGui::Checkbox("Relative FOV", &g_Options.fovRelative);

						static bool wasRelative = true;
						if (g_Options.fovRelative != wasRelative)
						{
							if (g_Options.fovRelative)
								g_Options.fov -= 90;
							else
								g_Options.fov += 90;
							wasRelative = g_Options.fovRelative;
						}

						ImGui::Checkbox("AutoWall ESP", &g_Options.autoWallEsp);
						ImGui::Checkbox("Peek ESP", &g_Options.peekEsp);

						ImGui::Checkbox("Multipoint ESP", &g_Options.multipointEsp);

						// ?

						//ImGui::SliderInt("Bones", &g_Options.bones1, 0, 128, "%.3f");

						//ImGui::Checkbox("Instant Defuse", &g_Options.instaDefuse);
					}

					ImGui::Separator();

					if (ImGui::CollapsingHeader("Style##Header"))
					{
						ImGui::Checkbox("ESP Outline##Enable", &g_Options.espOutline);

						static int lastFontSize = g_Options.espFontSize;

						ImGui::SliderInt("ESP Font Size", &g_Options.espFontSize, 10, 24, "%.0f");


						static int lastFont = g_Options.espFont;

						ImGui::Combo("ESP Font", &g_Options.espFont, fonts, fontsCount);



						ImGui::Combo("Name Style", &g_Options.espNameStyle, nameStyles, nameStylesCount);

						ImGui::Combo("Health Text Style", &g_Options.espHealthTextStyle, healthTextStyles, healthTextStylesCount);

						ImGui::Combo("Indicator Style", &g_Options.espIndicatorStyle, indicatorStyles, indicatorStylesCount);

						ImGui::Checkbox("Indicator Hover", &g_Options.espIndicatorHover);


						ImGui::Combo("Indicator Hover Size", &g_Options.espIndicatorHoverSizeStyle, indicatorHoverSizeStyles, indicatorHoverSizeStylesCount);


						ImGui::SliderFloat("Indicator Edge Distance", &g_Options.espIndicatorEdgeDistance, 0.0f, 1.0f, "%.3f", 1.0f);

						ImGui::SliderFloat("Indicator Draw Distance", &g_Options.espIndicatorDrawDistance, 0.0f, 1.0f, "%.3f", 1.0f);

						ImGui::Checkbox("Indicator Fade", &g_Options.espIndicatorFadeEnable);

						ImGui::SliderFloat("Indicator Fade Speed", &g_Options.espIndicatorFadeSpeed, 0.0f, 4.0f, "%.3f", 1.0f);

						ImGui::SliderFloat("Indicator Fade Minimum", &g_Options.espIndicatorFadeMinimum, 0.0f, 1.0f, "%.3f", 1.0f);

					}
				}
				ImGui::EndChild();
			}
			break;
			case 3:
			{
			
			}
			break;


			}
			ImGui::End();
		}

	}
}


HRESULT __stdcall Hooks::D3D9_EndScene(IDirect3DDevice9* pDevice)
{
	HRESULT result = d3d9VMT->GetOriginalMethod<EndSceneFn>(42)(pDevice);

	if (!Global::init)
		GUI_Init(pDevice);

	static void* dwReturnAddress = _ReturnAddress();

	if (dwReturnAddress == _ReturnAddress())
	{
		SaveState(pDevice);
		ImGui_ImplDX9_NewFrame();
		ImGui::Render();

		Drawing::GetInstance().SetupRenderStates();

		Drawing::GetInstance().ResetStyle();

		if (g_Vars->Menu.Opened)
		{
			g_UISystem.UpdateInput();
			g_UISystem.Draw();
		}

		RestoreState(pDevice);
	}
	return result;
}

HRESULT __stdcall Hooks::hkdReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresParam)
{
	if (!g_Globals->RenderInit)
		return oResetScene(pDevice, pPresParam);

	g_ImRender->InvalidateObjects();
	Drawing::GetInstance().InvalidateDeviceObjects();

	long hr = oResetScene(pDevice, pPresParam);

	if (hr >= 0)
	{
		g_ImRender->CreateObjects(pDevice);
		Drawing::GetInstance().RestoreDeviceObjects(pDevice);
	}

	return hr;
}

LockCursor_t oLockCursor;

void __stdcall Hooks::hk_lockcursor()
{
	if (g_Vars->Menu.Opened)
	{
		G_Surface->unlockcursor();
		return;
	}

	oLockCursor(G_Surface);
}
