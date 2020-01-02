#include "Main.h"



void Initialize() {
	while (!(g_Globals->CSGOWindow = FindWindowA("Valve001", NULL))) // Get CSGO window handle into global vars
		Sleep(200);

	if (Interfaces.GetInterfaces())
	{
		Sleep(500);
	}
	SetupOffsets(); 
	g_Utils->InitHooks(); 
}



BOOL WINAPI DllMain(HINSTANCE Instance, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(Instance);
		g_Globals->hmDll = Instance;
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Initialize, 0, 0, 0);
		break;
	}
	return true;
}