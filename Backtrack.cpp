#include "BackTrack.h"
#include "Math.h"
#define TICK_INTERVAL			( G_Globals->intervalPerTick )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( TICK_INTERVAL *( t ) )

template<class T, class U>
inline T clamp(T in, U low, U high)
{
	if (in <= low)
		return low;
	else if (in >= high)
		return high;
	else
		return in;
}



bool LagCompensation::IsTickValid(tick_record record)
{
	float correct = 0;

	correct += G_Engine->GetNetChannelInfo()->GetLatency(FLOW_OUTGOING);
	correct += G_Engine->GetNetChannelInfo()->GetLatency(FLOW_INCOMING);
	correct += LagComp->GetLerpTime();

	static ConVar* sv_maxunlag = G_Cvar->FindVar("sv_maxunlag");
	correct = clamp<float>(correct, 0.0f, sv_maxunlag->GetFloat());

	float deltaTime = correct - (G_Globals->curtime - record.m_flSimulationTime);



	return fabsf(deltaTime) < 0.2f;
}

ConVar* minupdate;
ConVar* maxupdate;
ConVar * updaterate;
ConVar * interprate;
ConVar* cmin;
ConVar* cmax;
ConVar* interp;

float LagCompensation::GetLerpTime()
{
	if (!minupdate)
		minupdate = G_Cvar->FindVar(XorStr("sv_minupdaterate"));
	if (!maxupdate)
		maxupdate = G_Cvar->FindVar(XorStr("sv_maxupdaterate"));
	if (!updaterate)
		updaterate = G_Cvar->FindVar(XorStr("cl_updaterate"));
	if (!interprate)
		interprate = G_Cvar->FindVar(XorStr("cl_interp_ratio"));
	if (!cmin)
		cmin = G_Cvar->FindVar(XorStr("sv_client_min_interp_ratio"));
	if (!cmax)
		cmax = G_Cvar->FindVar(XorStr("sv_client_max_interp_ratio"));
	if (!interp)
		interp = G_Cvar->FindVar(XorStr("cl_interp"));

	float UpdateRate = updaterate->GetValue();
	float LerpRatio = interprate->GetValue();

	return max(LerpRatio / UpdateRate, interp->GetValue());
}


void LagCompensation::Save_Record(C_BaseEntity* Entity, tick_record record)
{
	record.m_angEyeAngles = Entity->GetEyeAngles();
	record.m_flCycle = Entity->GetCycle();

	record.m_nFlags = *Entity->GetFlags();
	record.m_absangles = Entity->GetAbsAngles();


	record.m_flSimulationTime = Entity->GetSimulationTime();
	record.m_flAnimTime = Entity->GetAnimationTime();
	record.m_vecAbsOrigin = Entity->GetAbsOrigin();
	record.bLowerBodyYawUpdated = false;
	record.m_nSequence = Entity->GetSequence();
	record.m_vecOrigin = Entity->GetOrigin();
	record.m_vecVelocity = Entity->GetVelocity();
	record.m_flUpdateTime = G_Globals->curtime;
	record.backtrack_time = record.m_flSimulationTime + GetLerpTime();
	record.m_vecMins = Entity->GetCollision()->VecMins();
	record.m_vecMax = Entity->GetCollision()->VecMaxs();
	record.ragpos = Entity->get_ragdoll_pos();
}