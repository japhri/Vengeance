#include "Animating.h"

void BaseAnimation::Base_Animation_Set()
{
	m_flModelScale = 1.0f;
	m_flAnimTime = G_Globals->curtime;
	m_flPrevAnimTime = G_Globals->curtime;
	m_nNewSequenceParity = 0;
	m_nResetEventsParity = 0;
	m_boneCacheHandle = 0;
	m_pStudioHdr = NULL;
	m_fadeMinDist = 0;
	m_fadeMaxDist = 0;
	m_flFadeScale = 0.0f;
	m_fBoneCacheFlags = 0;
}

void BaseAnimation::Disable_Client_Animation()
{
	C_BaseEntity* Local = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	if (Client_Animation)
	{
		Local->GetClientSideAnimation() = false;
		Client_Animation = false;
	}
}

Vector BaseAnimation::GetLocalOrigin()
{
	C_BaseEntity* Local = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());

	if (Local == nullptr)
		return Vector{};

	Vector v1 = Local->GetOrigin();
	
	return v1;
}


bool BaseAnimation::AnimStates_Made()
{
	C_BaseEntity* Local = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	if (Animation_State == NULL)
	{
		Animation_State = Local->GetBasePlayerAnimState();
	}

	if (Animation_State != NULL)
		return true;
}
