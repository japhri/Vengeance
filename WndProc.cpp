#include "Main.h"
WNDPROC                            Hooks::g_pOldWindowProc; //Old WNDPROC pointer
bool CurKey[256] = {};
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT   __stdcall Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto& io = ImGui::GetIO();
	switch (uMsg)
	{

	case WM_LBUTTONDOWN:
		CurKey[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		CurKey[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		CurKey[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		CurKey[VK_RBUTTON] = false;
		break;
	case WM_KEYDOWN:
		CurKey[wParam] = true;
		break;
	case WM_KEYUP:
		CurKey[wParam] = false;
		break;
	case WM_MOUSEMOVE:
		io.MousePos.x = static_cast<signed short>(lParam);
		io.MousePos.y = static_cast<signed short>(lParam >> 16);
		break;
	default: break;
	}
	{
		static auto isDown = false;
		static auto isClicked = false;
		if (CurKey[VK_INSERT])
		{
			isClicked = false;
			isDown = true;
		}
		else if (!CurKey[VK_INSERT] && isDown)
		{
			isClicked = true;
			isDown = false;
		}
		else
		{
			isClicked = false;
			isDown = false;
		}
		if (isClicked)
		{
			g_Vars->Menu.Opened = !g_Vars->Menu.Opened;
		}

	}
	if (g_Vars->Menu.Opened  && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(Hooks::g_pOldWindowProc, hWnd, uMsg, wParam, lParam);
}