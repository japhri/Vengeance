#include "Main.h"
#include "BackTrack.h"



void BeamRings(Vector src,Color color)
{
	// TODO: do it once per sound
	BeamInfo_t beamInfo;
	beamInfo.m_nType = TE_BEAMDISK;
	beamInfo.m_vecStart = src;
	beamInfo.m_flStartRadius = 10;
	beamInfo.m_flEndRadius = 285;
	beamInfo.m_flRed = static_cast<float>(color.r());
	beamInfo.m_flGreen = static_cast<float>(color.g());
	beamInfo.m_flBlue = static_cast<float>(color.b());
	beamInfo.m_pszModelName = "sprites/purplelaser1.vmt";
	beamInfo.m_nModelIndex = G_ModelInfo->GetModelIndex("sprites/purplelaser1.vmt");
	beamInfo.m_nHaloIndex = G_ModelInfo->GetModelIndex("sprites/purplelaser1.vmt");
	beamInfo.m_flHaloScale = 5;
	beamInfo.m_nStartFrame = 0;
	beamInfo.m_flBrightness = 255;
	beamInfo.m_flFrameRate = 10;
	beamInfo.m_flLife = 1.0;
	beamInfo.m_flWidth = 5;
	beamInfo.m_flAmplitude = 0;
	beamInfo.m_flSpeed = 10;
	beamInfo.m_nFlags = 0;
	beamInfo.m_flFadeLength = 0;
	beamInfo.m_nSegments = 1;
	beamInfo.m_bRenderable = true;
	
		Beam_t* myBeam = G_Beams->CreateBeamRingPoint(beamInfo);
		if (myBeam)
			G_Beams->DrawBeam(myBeam);
	
}



void Trails(C_BaseEntity* ent,Color color)
{
	C_BaseEntity* pLocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	// TODO: fix it wrong parameters
	BeamInfo_t beamInfo;
	beamInfo.m_nType = TE_BEAMFOLLOW;
	//beamInfo.m_vecStart = src;
	beamInfo.m_pStartEnt = ent;
	beamInfo.m_pEndEnt = ent;
	beamInfo.m_flStartRadius = 10;
	beamInfo.m_flEndRadius = 285;
	beamInfo.m_flRed = static_cast<float>(color.r());
	beamInfo.m_flGreen = static_cast<float>(color.g());
	beamInfo.m_flBlue = static_cast<float>(color.b());
	beamInfo.m_pszModelName = "sprites/purplelaser1.vmt";
	beamInfo.m_nModelIndex = G_ModelInfo->GetModelIndex("sprites/purplelaser1.vmt");
	beamInfo.m_nHaloIndex = G_ModelInfo->GetModelIndex("sprites/purplelaser1.vmt");
	beamInfo.m_flHaloScale = 5;
	beamInfo.m_nStartFrame = 0;
	beamInfo.m_flBrightness = 255;
	beamInfo.m_flFrameRate = 10;
	beamInfo.m_flLife = 4.0;
	beamInfo.m_flWidth = 5;
	beamInfo.m_flEndWidth = 5;
	beamInfo.m_flAmplitude = 0;
	beamInfo.m_flSpeed = 10;
	beamInfo.m_nFlags = 0;
	beamInfo.m_flFadeLength = 5.f;
	beamInfo.m_flFadeLength = 0;
	beamInfo.m_nSegments = 5;
	beamInfo.m_bRenderable = true;

	Beam_t* myBeam = G_Beams->CreateBeamFollow(beamInfo);
	if (myBeam)
		G_Beams->DrawBeam(myBeam);
	//parameters for trails //(int startEnt, int modelIndex, int haloIndex, float haloScale,float life, float width, float endWidth, float fadeLength, float r, float g, float b,float brightness);
}






void __stdcall Hooks::FrameStageNotify(ClientFrameStage_t curStage)
{

	C_BaseEntity* pLocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());

	if (!pLocalPlayer || !G_Engine->IsConnected() || !G_Engine->IsInGame())
	{
		clientVMT->GetOriginalMethod<FrameStageNotifyFn>(37)(curStage);
		return;
	}

	if (curStage == FRAME_RENDER_START)
	{

		CBasePlayerAnimState* animatioons = pLocalPlayer->GetBasePlayerAnimState();
		bool enabletp = true;
		if (enabletp && pLocalPlayer->isAlive())
		{
			animatioons->m_flHeadHeightOrOffsetFromHittingGroundAnimation = 0.f;
			*reinterpret_cast<QAngle*>(reinterpret_cast<DWORD>(pLocalPlayer + 0x31C0 + 0x8)) = g_Globals->RealAngle;
			animatioons->m_flHeadHeightOrOffsetFromHittingGroundAnimation = 0.f;
			
		}
		if (enabletp && pLocalPlayer->isAlive())
		{
			*(bool*)((DWORD)G_Input + 0xA5) = true;
			*(float*)((DWORD)G_Input + 0xA8 + 0x8) = 130; // Thirdperson Distance
		}
		else
		{
			*(bool*)((DWORD)G_Input + 0xA5) = false;
			*(float*)((DWORD)G_Input + 0xA8 + 0x8);
		}
		//pLocalPlayer->SetAngle2(Vector(0.f, pLocalPlayer->GetBasePlayerAnimState()->m_flGoalFeetYaw, 0.f));
		
	
		
	}

	if (curStage == FRAME_NET_UPDATE_START)
	{
		if (pLocalPlayer->isAlive())
		{
			Trails(pLocalPlayer, Color(0, 255, 0));
		}
	}

	if (curStage == FRAME_NET_UPDATE_END)
	{
		
		
	}

	if (curStage == FRAME_RENDER_START)
	{
	
	}
	clientVMT->GetOriginalMethod<FrameStageNotifyFn>(37)(curStage);
}


/*
void __fastcall Hooks::EmitSounds(void* thisptr,void *filter, int entity_index, int channel, const char *sound_entry, uint32_t sound_entry_hash, const char *sample, float volume, float attenuation, int seed, int flag, int pitch, const Vector *origin, const Vector *direction, void *utl_origins, bool update_positions, float sound_time, int speaker_entity, int unknown)
{
	if (strstr(sample, "null"))
		sample = "";	
	G_Cvar->ConsolePrintf("ran");
	EngineSound->GetOriginalMethod<Emitsoundfn>(5)(thisptr,filter, entity_index, channel, sound_entry, sound_entry_hash, sample, volume, attenuation, seed, flag, pitch, origin, direction, utl_origins, update_positions, sound_time, speaker_entity, unknown);

}

*/