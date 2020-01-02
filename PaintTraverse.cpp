#include "Main.h"
#include "mrc.hpp"
std::string sPanel = XorStr("FocusOverlayPanel");

#include "Visuals.h"

SpoofedConvar::SpoofedConvar() {}

SpoofedConvar::SpoofedConvar(const char* szCVar) {
	m_pOriginalCVar = G_Cvar->FindVar(szCVar);
	Spoof();
}
SpoofedConvar::SpoofedConvar(ConVar* pCVar) {
	m_pOriginalCVar = pCVar;
	Spoof();
}
SpoofedConvar::~SpoofedConvar() {
	if (IsSpoofed()) {
		DWORD dwOld;

		SetFlags(m_iOriginalFlags);
		SetString(m_szOriginalValue);

		VirtualProtect((LPVOID)m_pOriginalCVar->m_pszName, 128, PAGE_READWRITE, &dwOld);
		strcpy((char*)m_pOriginalCVar->m_pszName, m_szOriginalName);
		VirtualProtect((LPVOID)m_pOriginalCVar->m_pszName, 128, dwOld, &dwOld);

		//Unregister dummy cvar
		G_Cvar->UnregisterConCommand(m_pDummyCVar);
		free(m_pDummyCVar);
		m_pDummyCVar = nullptr;
	}
}
bool SpoofedConvar::IsSpoofed() {
	return m_pDummyCVar != nullptr;
}
void SpoofedConvar::Spoof() {
	if (!IsSpoofed() && m_pOriginalCVar) {
		//Save old name value and flags so we can restore the cvar lates if needed
		m_iOriginalFlags = m_pOriginalCVar->m_nFlags;
		strcpy(m_szOriginalName, m_pOriginalCVar->m_pszName);
		strcpy(m_szOriginalValue, m_pOriginalCVar->m_pszDefaultValue);

		sprintf_s(m_szDummyName, 128, "d_%s", m_szOriginalName);

		//Create the dummy cvar
		m_pDummyCVar = (ConVar*)malloc(sizeof(ConVar));
		if (!m_pDummyCVar) return;
		memcpy(m_pDummyCVar, m_pOriginalCVar, sizeof(ConVar));

		m_pDummyCVar->m_pNext = nullptr;
		//Register it
		G_Cvar->RegisterConCommand(m_pDummyCVar);

		//Fix "write access violation" bullshit
		DWORD dwOld;
		VirtualProtect((LPVOID)m_pOriginalCVar->m_pszName, 128, PAGE_READWRITE, &dwOld);

		//Rename the cvar
		strcpy((char*)m_pOriginalCVar->m_pszName, m_szDummyName);

		VirtualProtect((LPVOID)m_pOriginalCVar->m_pszName, 128, dwOld, &dwOld);

		SetFlags(FCVAR_NONE);
	}
}
void SpoofedConvar::SetFlags(int flags) {
	if (IsSpoofed()) {
		m_pOriginalCVar->m_nFlags = flags;
	}
}
int SpoofedConvar::GetFlags() {
	return m_pOriginalCVar->m_nFlags;
}
void SpoofedConvar::SetInt(int iValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(iValue);
	}
}
void SpoofedConvar::SetBool(bool bValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(bValue);
	}
}
void SpoofedConvar::SetFloat(float flValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(flValue);
	}
}
void SpoofedConvar::SetString(const char* szValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(szValue);
	}
}

#include "Drawing.h"
void __fastcall Hooks::PaintTraverse(void* ecx/*thisptr*/, void* edx, unsigned int vgui_panel, bool force_repaint, bool allow_force) // cl
{

	
	panelVMT->GetOriginalMethod<PaintTraverseFn>(41)(ecx, vgui_panel, force_repaint, allow_force);
	static bool spoofed = false; //will find a better method later
	if (!spoofed)
	{
		ConVar* svcheats = G_Cvar->FindVar("sv_cheats");
		SpoofedConvar svcheatsspoof = SpoofedConvar(svcheats);
		svcheatsspoof.SetInt(1);
		spoofed = true;
	}

	const char* pszPanelName = G_Panel->GetName(vgui_panel);

	if (!strstr(pszPanelName, sPanel.data()))
		return;

	int cur_height, cur_width; G_Engine->GetScreenSize(cur_width, cur_height);
	
	G_Engine->GetScreenSize(cur_width, cur_height);
	g_Globals->Screen.height = cur_height;
	g_Globals->Screen.width = cur_width;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			g_Globals->viewMatrix[i][j] = G_Engine->WorldToScreenMatrix()[i][j];
		}
	}
	if (G_Engine->IsInGame())
	{
		Visuals->DrawTaserDistance();
		
	}
}