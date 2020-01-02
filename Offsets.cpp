#include "SDK.h"
G_Offsets G_sets;

static bool bCompare(const BYTE* Data, const BYTE* Mask, const char* szMask)
{
	for (; *szMask; ++szMask, ++Mask, ++Data)
	{
		if (*szMask == 'x' && *Mask != *Data)
		{
			return false;
		}
	}
	return (*szMask) == 0;
}

DWORD WaitOnModuleHandle(std::string moduleName)
{
	DWORD ModuleHandle = NULL;
	while (!ModuleHandle)
	{
		ModuleHandle = (DWORD)GetModuleHandle(moduleName.c_str());
		if (!ModuleHandle)
			Sleep(50);
	}
	return ModuleHandle;
}

DWORD FindPattern(std::string moduleName, BYTE* Mask, char* szMask)
{
	DWORD Address = WaitOnModuleHandle(moduleName.c_str());
	MODULEINFO ModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)Address, &ModInfo, sizeof(MODULEINFO));
	DWORD Length = ModInfo.SizeOfImage;
	for (DWORD c = 0; c < Length; c += 1)
	{
		if (bCompare((BYTE*)(Address + c), Mask, szMask))
		{
			return DWORD(Address + c);
		}
	}
	return 0;
}


void SetupOffsets()
{
	//printf(XorStr(":::::Adresses & Offsets:::::\n"));
	g_pNetVars = new CNetVars();


	G_sets.nWriteableBones = g_pNetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_nForceBone")) + 0x20;
	G_sets.dwOcclusionArray = *(uintptr_t*)(FindPatternIDA(XorStr(client_dll), XorStr("A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8")) + 0x1);
	G_sets.bDidCheckForOcclusion = *(uintptr_t*)(FindPatternIDA(XorStr(client_dll), XorStr("A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8")) + 0x7);

	G_sets.InvalidateBoneCache = static_cast<DWORD>(FindPatternIDA(client_dll, "80 3D ? ? ? ? 00 74 16 A1 ? ? ? ? 48 C7 81"));

	//printf(XorStr("Array: 0x%X\n"), (DWORD)G_sets.dwOcclusionArray);
	//printf(XorStr("Bool: 0x%X\n"), (DWORD)G_sets.bDidCheckForOcclusion);

	G_sets.dwInitKeyValues = static_cast<DWORD>(FindPatternIDA(XorStr(client_dll), XorStr("8B 0E 33 4D FC 81 E1 ? ? ? ? 31 0E 88 46 03 C1 F8 08 66 89 46 12 8B C6")) - 0x45);
	//printf(XorStr("InitKeyValues: 0x%X\n"), (DWORD)G_sets.dwInitKeyValues);

	G_sets.dwLoadFromBuffer = static_cast<DWORD>(FindPatternIDA(XorStr(client_dll), XorStr("55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04")));
	//printf(XorStr("LoadFromBuffer: 0x%X\n"), (DWORD)G_sets.dwLoadFromBuffer);

	G_sets.m_ArmorValue = g_pNetVars->GetOffset("DT_CSPlayer", "m_ArmorValue");
	G_sets.m_bHasHelmet = g_pNetVars->GetOffset("DT_CSPlayer", "m_bHasHelmet");

	G_sets.m_angRotation = g_pNetVars->GetOffset("DT_CSPlayer", "m_angRotation");


	G_sets.m_flPoseParameter = g_pNetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_flPoseParameter"));
	G_sets.m_flCycle = g_pNetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_flCycle"));
	G_sets.m_flSimulationTime = g_pNetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_flSimulationTime"));
	G_sets.m_flAnimTime = g_pNetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_flAnimTime"));
	G_sets.m_nSequence = g_pNetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_nSequence"));
	G_sets.m_flLowerBodyYawTarget = g_pNetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_flLowerBodyYawTarget"));
	G_sets.m_flFlashMaxAlpha = g_pNetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_flFlashMaxAlpha"));
	G_sets.m_angEyeAngles = g_pNetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_angEyeAngles[0]"));
	G_sets.m_nTickBase = g_pNetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_nTickBase"));
	G_sets.m_fFlags = g_pNetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_fFlags"));
	G_sets.m_flNextPrimaryAttack = g_pNetVars->GetOffset(XorStr("DT_BaseCombatWeapon"), XorStr("m_flNextPrimaryAttack"));
	G_sets.m_vecOrigin = g_pNetVars->GetOffset(XorStr("DT_BaseEntity"), XorStr("m_vecOrigin"));
	G_sets.m_vecViewOffset = g_pNetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_vecViewOffset[0]"));
	G_sets.m_vecVelocity = g_pNetVars->GetOffset("DT_CSPlayer", "m_vecVelocity[0]");
	G_sets.m_vecBaseVelocity = g_pNetVars->GetOffset("DT_CSPlayer", "m_vecBaseVelocity");
	G_sets.m_flFallVelocity = g_pNetVars->GetOffset("DT_CSPlayer", "m_flFallVelocity");
	G_sets.m_bPinPulled = g_pNetVars->GetOffset(XorStr("DT_BaseCSGrenade"), XorStr("m_bPinPulled"));
	//	G_sets.m_hObserverTarget = g_pNetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_hObserverTarget"));
	G_sets.m_fThrowTime = g_pNetVars->GetOffset(XorStr("DT_BaseCSGrenade"), XorStr("m_fThrowTime"));
	G_sets.m_fAccuracyPenalty = g_pNetVars->GetOffset("DT_WeaponCSBase", "m_fAccuracyPenalty");
	G_sets.m_iClip1 = g_pNetVars->GetOffset("DT_WeaponCSBase", "m_iClip1");
	G_sets.m_bReloadVisuallyComplete = g_pNetVars->GetOffset("DT_WeaponFiveSeven", "m_bReloadVisuallyComplete");
	G_sets.m_iPrimaryReserveAmmoCount = g_pNetVars->GetOffset("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount");
	G_sets.getSequenceActivity = (DWORD)FindPatternIDA(client_dll, "55 8B EC 83 7D 08 FF 56 8B F1 74 3D");

	G_sets.m_lifeState = g_pNetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_lifeState"));
	G_sets.m_flC4Blow = g_pNetVars->GetOffset(XorStr("DT_PlantedC4"), XorStr("m_flC4Blow"));
	G_sets.m_bBombDefused = g_pNetVars->GetOffset(XorStr("DT_PlantedC4"), XorStr("m_bBombDefused"));
	G_sets.m_hOwnerEntity = g_pNetVars->GetOffset(XorStr("DT_PlantedC4"), XorStr("m_hOwnerEntity"));
	G_sets.m_flDefuseCountDown = g_pNetVars->GetOffset(XorStr("DT_PlantedC4"), XorStr("m_flDefuseCountDown"));
	

	G_sets.m_flFriction = g_pNetVars->GetOffset("DT_CSPlayer", "m_flFriction");
	G_sets.m_CollisionGroup = g_pNetVars->GetOffset("DT_BaseEntity", "m_CollisionGroup");
	G_sets.m_bIsScoped = g_pNetVars->GetOffset("DT_CSPlayer", "m_bIsScoped");
	G_sets.m_bClientSideAnimation = g_pNetVars->GetOffset("DT_BaseAnimating", "m_bClientSideAnimation");
	G_sets.dwComputeHitboxSurroundingBox = static_cast<DWORD>(FindPatternIDA(client_dll, "E9 ? ? ? ? 32 C0 5D"));

	uintptr_t player_resource_pointer = uintptr_t((uintptr_t)GetModuleHandle(client_dll) + 0x2EC5ADC);
	G_sets.dw_CSPlayerResource = (DWORD)player_resource_pointer;
	G_sets.m_iCompetetiveRanking = g_pNetVars->GetOffset(XorStr("DT_CSPlayerResource"), XorStr("m_iCompetitiveRanking"));
	G_sets.m_iCompetetiveWins = g_pNetVars->GetOffset(XorStr("DT_CSPlayerResource"), XorStr("m_iCompetitiveWins"));
	G_sets.m_iPing = g_pNetVars->GetOffset(XorStr("DT_CSPlayerResource"), XorStr("m_iPing"));

	G_sets.animstate = 0x3884;

	G_sets.m_bIsValveDS = g_pNetVars->GetOffset(XorStr("DT_CSGameRulesProxy"), XorStr("m_bIsValveDS"));

	G_sets.m_hMyWearables = g_pNetVars->GetOffset(XorStr("DT_CSPlayer"), XorStr("m_hMyWearables"));

	G_sets.m_hMyWeapons = g_pNetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_hMyWeapons"));
	G_sets.m_hActiveWeapon = g_pNetVars->GetOffset(XorStr("DT_BasePlayer"), XorStr("m_hActiveWeapon"));

	G_sets.m_flFriction = g_pNetVars->GetOffset("DT_CSPlayer", "m_flFriction");
	G_sets.m_flMaxspeed = g_pNetVars->GetOffset("DT_BasePlayer", "m_flMaxspeed");
	G_sets.m_flStepSize = g_pNetVars->GetOffset("DT_CSPlayer", "m_flStepSize");
	G_sets.m_bGunGameImmunity = g_pNetVars->GetOffset("DT_CSPlayer", "m_bGunGameImmunity");

	G_sets.m_flPostponeFireReadyTime = g_pNetVars->GetOffset("DT_WeaponCSBaseGun", "m_flPostponeFireReadyTime");
	G_sets.m_iShotsFired = g_pNetVars->GetOffset("DT_CSPlayer", "m_iShotsFired");

	/*DT_BaseAttributableItem*/
	G_sets.m_iItemDefinitionIndex = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_iItemDefinitionIndex");
	G_sets.m_iItemIDHigh = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_iItemIDHigh");
	G_sets.m_iItemIDLow = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_iItemIDLow");
	G_sets.m_iEntityQuality = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_iEntityQuality");
	G_sets.m_szCustomName = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_szCustomName");
	G_sets.m_OriginalOwnerXuidLow = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
	G_sets.m_OriginalOwnerXuidHigh = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
	G_sets.m_nFallbackPaintKit = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_nFallbackPaintKit");
	G_sets.m_nFallbackSeed = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_nFallbackSeed");
	G_sets.m_flFallbackWear = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_flFallbackWear");
	G_sets.m_nFallbackStatTrak = g_pNetVars->GetOffset("DT_BaseAttributableItem", "m_nFallbackStatTrak");
	G_sets.m_nAccountID = g_pNetVars->GetOffset("DT_FEPlayerDecal", "m_unAccountID");
	G_sets.m_iViewModelIndex = g_pNetVars->GetOffset("DT_BaseCombatWeapon", "m_iViewModelIndex");
	G_sets.m_iWorldModelIndex = g_pNetVars->GetOffset("DT_BaseCombatWeapon", "m_iWorldModelIndex");
	G_sets.m_hWeaponWorldModel = g_pNetVars->GetOffset("DT_BaseCombatWeapon", "m_hWeaponWorldModel");

	G_sets.m_nModeIndex = g_pNetVars->GetOffset("DT_BaseViewModel", "m_nModelIndex");
	G_sets.m_hViewModel = g_pNetVars->GetOffset("DT_CSPlayer", "m_hViewModel[0]");
	G_sets.m_hWeapon = g_pNetVars->GetOffset("DT_BaseViewModel", "m_hWeapon");
}


void PrintNetvars()
{

}
