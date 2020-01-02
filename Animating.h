#pragma once
#include "Main.h"

class BaseAnimation
{
	void Base_Animation_Set();
	Vector GetLocalOrigin();
	void Disable_Client_Animation();
	bool AnimStates_Made();
	void FRAME_RENDER_START();
	void FRAME_NET_UPDATE_END();

	
	float m_flModelScale;
	float m_flAnimTime;
	float m_flPrevAnimTime;
	int m_nNewSequenceParity;
	int m_nResetEventsParity;
	int m_boneCacheHandle;
	studiohdr_t *m_pStudioHdr;
	int m_fadeMinDist;
	int m_fadeMaxDist;
	float m_flFadeScale;
	int m_fBoneCacheFlags;
	bool Client_Animation = true;
	CBasePlayerAnimState * Animation_State = NULL;

}; extern BaseAnimation* BaseAnimating;