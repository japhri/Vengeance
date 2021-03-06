#include "Main.h"

void __stdcall ImGuiRendering::CreateObjects(IDirect3DDevice9* pDevice)
{
	if(g_Globals->CSGOWindow)
		ImGui_ImplDX9_CreateDeviceObjects();
	_drawList = new ImDrawList();
}

void __stdcall ImGuiRendering::InvalidateObjects()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	if (_drawList)
		delete _drawList;
	_drawList = nullptr;
}

void __stdcall ImGuiRendering::SetupPresent(IDirect3DDevice9* device)
{
	ImGui_ImplDX9_Init(g_Globals->CSGOWindow, device);
	g_ImRender->CreateObjects(device);
	g_Globals->RenderInit = true;
}

void __stdcall ImGuiRendering::EndPresent(IDirect3DDevice9* device)
{
	ImGui::Render();
	device->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);
}

void __stdcall ImGuiRendering::PreRender(IDirect3DDevice9* device)
{	
	device->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	ImGui_ImplDX9_NewFrame();
	_drawData.Valid = false;
	_drawList->Clear();
	_drawList->PushClipRectFullScreen();
}

void __stdcall ImGuiRendering::PostRender(IDirect3DDevice9* device)
{
	if (!_drawList->VtxBuffer.empty()) {
		_drawData.Valid = true;
		_drawData.CmdLists = &_drawList;
		_drawData.CmdListsCount = 1;
		_drawData.TotalVtxCount = _drawList->VtxBuffer.Size;
		_drawData.TotalIdxCount = _drawList->IdxBuffer.Size;
	}

	ImGui_ImplDX9_RenderDrawLists(&_drawData);
}

void ImGuiRendering::DrawString(ImFont* font, float x, float y, Color color, const char* message, ...)
{
	char output[1024] = {};
	va_list args;
	va_start(args, message);
	vsprintf_s(output, message, args);
	va_end(args);
	auto coord = ImVec2(x, y);
	auto size = ImGui::CalcTextSize(output);
	auto coord_out = ImVec2{ coord.x + 1.f, coord.y + 1.f };

	_drawList->PushTextureID(font->ContainerAtlas->TexID);
	ImGui::PushFont(font);
	_drawList->AddText(coord, color.GetU32(), output);
	ImGui::PopFont();
}

void ImGuiRendering::DrawEspBox(Vector leftUpCorn, Vector rightDownCorn, Color clr, float width)
{
	ImVec2 min = ImVec2(leftUpCorn.x, leftUpCorn.y);
	ImVec2 max = ImVec2(rightDownCorn.x, rightDownCorn.y);
	_drawList->AddRect(min, max, clr.GetU32(), 0.0F, -1, width);
}

void ImGuiRendering::DrawLine(float x1, float y1, float x2, float y2, Color clr, float thickness = 1.0f)
{
	_drawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), clr.GetU32(), thickness);
}

