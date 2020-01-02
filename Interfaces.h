#pragma once

#include "CHandle.h"
#include "IClientNetworkable.h"
#include "IBaseClientDLL.h"
#include "IVEngineClient.h"
#include "ISurface.h"
#include "Input.h"
#include "EngienTrace.h"
#include "ModelRender.h"
#include "CVar.h"
#include "xor.h"
#include "EntityStruct.h"
extern IBaseClientDLL* G_Client;
extern IVEngineClient* G_Engine;
extern IClientEntityList* G_EntList;
extern IGlobalVars* G_Globals;
extern IClientMode* G_ClientMode;
extern ISurface* G_Surface;
extern CInput* G_Input;
extern CModelInfo* G_ModelInfo;
extern CInputSystem* G_InputSystem;
extern CPanel* G_Panel;
extern IStudioRender* G_StudioRender;
extern IEngineTrace* G_EngineTrace;
extern CRenderView* G_RenderView;
extern CModelRender* G_ModelRender;
extern CMaterialSystem* G_MaterialSystem;
extern ICvar* G_Cvar;
extern CGameMovement* G_Movement;
extern CPrediction* G_Prediction;
extern IGameEventManager* G_Events;
extern CDebugOverlay* DebugOverlay;
extern IPhysicsSurfaceProps* G_PhysicProps;
extern IMoveHelper* G_MoveHelper;
extern IEngineSound* G_Sound;
extern IViewRenderBeams* G_Beams;
namespace Global
{
	extern bool ispano;
	extern bool init;
};

#define client_dll  Global::ispano ? "client.dll" : "client_panorama.dll"

extern uint64_t FindPatternIDA(const char* szModule, const char* szSignature);

extern std::uint8_t *PatternScan(void* module, const char* signature);

enum {
	CHAR_TEX_ANTLION = 'A',
	CHAR_TEX_BLOODYFLESH = 'B',
	CHAR_TEX_CONCRETE = 'C',
	CHAR_TEX_DIRT = 'D',
	CHAR_TEX_EGGSHELL = 'E',
	CHAR_TEX_FLESH = 'F',
	CHAR_TEX_GRATE = 'G',
	CHAR_TEX_ALIENFLESH = 'H',
	CHAR_TEX_CLIP = 'I',
	CHAR_TEX_PLASTIC = 'L',
	CHAR_TEX_METAL = 'M',
	CHAR_TEX_SAND = 'N',
	CHAR_TEX_FOLIAGE = 'O',
	CHAR_TEX_COMPUTER = 'P',
	CHAR_TEX_SLOSH = 'S',
	CHAR_TEX_TILE = 'T',
	CHAR_TEX_CARDBOARD = 'U',
	CHAR_TEX_VENT = 'V',
	CHAR_TEX_WOOD = 'W',
	CHAR_TEX_GLASS = 'Y',
	CHAR_TEX_WARPSHIELD = 'Z',
};

#define DAMAGE_NO			0
#define DAMAGE_EVENTS_ONLY	1	
#define DAMAGE_YES			2
#define DAMAGE_AIM			3
#define CLIP_TRACE_TO_PLAYER_SIGNATURE "53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 81 EC ? ? ? ? 8B 43 10"
typedef bool(__fastcall* IsBreakableEntityFn) (C_BaseEntity *pEntity);
extern IsBreakableEntityFn IsBreakableEntity;

extern std::uint8_t* _ClipTraceToPlayers;




class CInterfaces
{
public:
	
	bool GetInterfaces()
	{
		static char* clientName = "client_panorama.dll";
		HMODULE client = GetModuleHandle(clientName);
		HMODULE client2 = GetModuleHandleA(clientName);
		g_Utils->OpenConsole("Debug");
		G_Engine = (IVEngineClient*)GetPointer(XorStr("engine.dll"), XorStr("VEngineClient"));
		G_Client = (IBaseClientDLL*)GetPointer(XorStr(client_dll), XorStr("VClient"));
		G_EntList = (IClientEntityList*)GetPointer(XorStr(client_dll), XorStr("VClientEntityList"));
		G_Surface = (ISurface*)GetPointer(XorStr("vguimatsurface.dll"), XorStr("VGUI_Surface"));
		G_Input = *(CInput**)(FindPatternIDA(XorStr(client_dll), XorStr("B9 ? ? ? ? F3 0F 11 04 24 FF 50 10")) + 0x1);
		G_Globals = **(IGlobalVars***)((*(uintptr_t**)G_Client)[0] + 0x1B);
		G_ClientMode = **(IClientMode***)((*(uintptr_t**)G_Client)[10] + 0x5);
		G_Panel = (CPanel*)GetPointer(XorStr("vgui2.dll"), XorStr("VGUI_Panel"));
		G_ModelInfo = (CModelInfo*)GetPointer(XorStr("engine.dll"), XorStr("VModelInfoClient"));
		G_InputSystem = (CInputSystem*)GetPointer(XorStr("inputsystem.dll"), XorStr("InputSystemVersion"));
		G_StudioRender = (IStudioRender*)GetPointer(XorStr("studiorender.dll"), XorStr("VStudioRender"));
		G_EngineTrace = (IEngineTrace*)GetPointer(XorStr("engine.dll"), XorStr("EngineTraceClient"));
		G_Cvar = (ICvar*)GetPointer(XorStr("vstdlib.dll"), XorStr("VEngineCvar"));
		G_MaterialSystem = (CMaterialSystem*)GetPointer(XorStr("materialsystem.dll"), XorStr("VMaterialSystem"));
		G_ModelRender = (CModelRender*)GetPointer(XorStr("engine.dll"), XorStr("VEngineModel"));
		G_RenderView = (CRenderView*)GetPointer(XorStr("engine.dll"), XorStr("VEngineRenderView"));
		G_Movement = (CGameMovement*)GetPointer(XorStr(client_dll), XorStr("GameMovement"));
		G_Prediction = (CPrediction*)GetPointer(XorStr(client_dll), XorStr("VClientPrediction"));
		//G_Events = (IGameEventManager*)GetPointer(XorStr("engine.dll"), XorStr("GAMEEVENTSMANAGER002"));
		DebugOverlay = (CDebugOverlay*)GetPointer(XorStr("engine.dll"), XorStr("VDebugOverlay"));
		G_PhysicProps = (IPhysicsSurfaceProps*)GetPointer(XorStr("vphysics.dll"), XorStr("VPhysicsSurfaceProps"));
		G_MoveHelper = **(IMoveHelper***)(FindPatternIDA(XorStr(client_dll), XorStr("8B 0D ? ? ? ? 8B 46 08 68")) + 0x2);
		G_Sound = (IEngineSound*)GetPointer(XorStr("engine.dll"), XorStr("IEngineSoundClient"));
		G_Beams = *(IViewRenderBeams**)(FindPatternIDA(client_dll, "B9 ? ? ? ? A1 ? ? ? ? FF 10 A1 ? ? ? ? B9") + 1);
		IsBreakableEntity = reinterpret_cast<IsBreakableEntityFn>(PatternScan(client, "55 8B EC 51 56 8B F1 85 F6 74 68 83 BE"));
		_ClipTraceToPlayers = PatternScan(client2, CLIP_TRACE_TO_PLAYER_SIGNATURE);
		printf("Interfaces Found");
		
		return true;
	}

	void* GetPointer(const char* Module, const char* InterfaceName)
	{
		void* Interface = NULL;
		char PossibleInterfaceName[1024];

		CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(Module), XorStr("CreateInterface"));

		for (int i = 1; i < 100; i++)
		{
			sprintf_s(PossibleInterfaceName, XorStr("%s0%i"), InterfaceName, i);
			Interface = (void*)CreateInterface(PossibleInterfaceName, NULL);
			if (Interface != NULL)
			{
				printf(XorStr("%s Found: 0x%X\n"), PossibleInterfaceName, (DWORD)Interface);
				break;
			}
			sprintf_s(PossibleInterfaceName, XorStr("%s00%i"), InterfaceName, i);
			Interface = (void*)CreateInterface(PossibleInterfaceName, NULL);
			if (Interface != NULL)
			{
				printf(XorStr("%s Found: 0x%X\n"), PossibleInterfaceName, (DWORD)Interface);
				break;
			}
		}


		return Interface;
	}




};
extern CInterfaces Interfaces;