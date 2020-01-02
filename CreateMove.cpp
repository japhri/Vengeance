#include "Main.h"
#include "BackTrack.h"
#include "Autowall.h"
#include "Math.h"
#include "Antiaim.h"
#include "Prediction.h"

static CPredictionSystem* Prediction = new CPredictionSystem();

void FixMovement()
{
	CUserCmd* cmd = g_Globals->usercmd;
	Vector real_viewangles;
	G_Engine->GetViewAngles(real_viewangles);

	Vector vecMove(cmd->forwardmove, cmd->sidemove, cmd->upmove);
	float speed = sqrt(vecMove.x * vecMove.x + vecMove.y * vecMove.y);

	Vector angMove;
	Math::VectorAngles(vecMove, angMove);

	float yaw = DEG2RAD(cmd->viewangles.y - real_viewangles.y + angMove.y);

	cmd->forwardmove = cos(yaw) * speed;
	cmd->sidemove = sin(yaw) * speed;

	cmd->buttons &= ~IN_RIGHT;
	cmd->buttons &= ~IN_MOVERIGHT;
	cmd->buttons &= ~IN_LEFT;
	cmd->buttons &= ~IN_MOVELEFT;
	cmd->buttons &= ~IN_FORWARD;
	cmd->buttons &= ~IN_BACK;

	if (cmd->forwardmove > 0.f)
		cmd->buttons |= IN_FORWARD;
	else if (cmd->forwardmove < 0.f)
		cmd->buttons |= IN_BACK;

	if (cmd->sidemove > 0.f)
	{
		cmd->buttons |= IN_RIGHT;
		cmd->buttons |= IN_MOVERIGHT;
	}
	else if (cmd->sidemove < 0.f)
	{
		cmd->buttons |= IN_LEFT;
		cmd->buttons |= IN_MOVELEFT;
	}
}


int LagCompBreak() {
	C_BaseEntity* local = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	Vector velocity = local->GetVelocity();
	velocity.z = 0;
	float speed = velocity.Length();
	if (speed > 0.f) {
		float distance_per_tick = speed * G_Globals->intervalPerTick;
		int choked_ticks = static_cast<int>(std::ceilf(65.f / distance_per_tick));
		return std::min<int>(choked_ticks, g_Options.FakelagAmount);
	}
	return 1;
}

int lagTicks = 0;
int lagTicksMax = 15;

template<class T, class U>
T clamp(T in, U low, U high)
{
	if (in <= low)
		return low;

	if (in >= high)
		return high;

	return in;
}

void Fakelag(CUserCmd* cmd, bool& bSendPacket)
{
	static int ticks = 0;
	C_BaseEntity* local = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	//auto units = local->GetVelocity().Length2D() * G_Globals->intervalPerTick;
	//auto ticks = static_cast<int>(clamp(ceil(65.0f / units), 1, 15));
	static int choked = 0;

	g_Globals->chokedTicks = LagCompBreak();

	if (ticks >= g_Globals->chokedTicks)
	{
		ticks = 0;
		bSendPacket = true;
	}
	else
	{
		bSendPacket = false;
		ticks++;
	}
}

void AutoZeus()
{
	for (int i = 1; i <= G_Globals->maxClients; i++)
	{
		C_BaseEntity *entity = G_EntList->GetClientEntity(i);
		if (!entity
			|| entity == g_Globals->local
			|| entity->IsDormant()
			|| !entity->isAlive()
			|| entity->IsProtected()
			|| !entity->IsPlayer()
			|| entity->GetTeamNum() == g_Globals->local->GetTeamNum()
			|| !(*entity->GetFlags() & FL_ONGROUND))
			continue;

		Vector traceStart, traceEnd;
		QAngle viewAngles;
		G_Engine->GetViewAngles(viewAngles);
		QAngle viewAnglesRcs = viewAngles + g_Globals->local->GetPunchAngle() * 2.0f;

		Math::AngleVectors(viewAnglesRcs, &traceEnd);

		traceStart = g_Globals->local->GetEyePosition();
		traceEnd = traceStart + (traceEnd * 8192.0f);

		Ray_t ray;
		trace_t Trace;
		ray.Init(traceStart, traceEnd);
		CTraceFilter traceFilter;
		traceFilter.pSkip = g_Globals->local;
		G_EngineTrace->TraceRay(ray, 0x46004003, &traceFilter, &Trace);

		if (!Trace.hit_entity)
			return;
		if (!Trace.hit_entity->IsValidTarget())
			return;

		float playerDistance = g_Globals->local->GetOrigin().DistTo(entity->GetOrigin());

			if (playerDistance <= 184.f)
				g_Globals->usercmd->buttons |= IN_ATTACK;
		
	}
}


bool __fastcall Hooks::CreateMove(void* thisptr, void*, float flInputSampleTime, CUserCmd* cmd)
{
	if (!cmd) return false;

	if (!cmd->command_number)
		return true;

	C_BaseEntity* local = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());

	g_Globals->usercmd = cmd;
	g_Globals->local = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());

	static bool lastSendPacket;
	G_Engine->SetViewAngles(cmd->viewangles);
	QAngle originalAngles = cmd->viewangles;
	CBasePlayerAnimState* animations = local->GetBasePlayerAnimState();

	if (local->isAlive())
	{
		static bool bJumped = false;
		static bool bFake = false;
		if (!bJumped && bFake)
		{
			bFake = false;
			if (local->GetFlags() && (*local->GetFlags() & FL_ONGROUND))
				g_Globals->usercmd->buttons |= IN_JUMP;
		}
		else if (g_Globals->usercmd->buttons & IN_JUMP)
		{
			if (*local->GetFlags() & FL_ONGROUND)
			{
				bJumped = true;
				bFake = true;
			}
			else
			{
				g_Globals->usercmd->buttons &= ~IN_JUMP;
				bJumped = false;
			}
		}
		else
		{
			bJumped = false;
			bFake = false;
		}
	}

	if (local->isAlive())
	{
		PVOID pebp;
		__asm mov pebp, ebp;
		bool* pbSendPacket = (bool*)(*(PDWORD)pebp - 0x1C);
		*pbSendPacket = cmd->command_number % 2;
		Prediction->EnginePrediction(cmd);
		Fakelag(g_Globals->usercmd, *pbSendPacket);
		AutoZeus();
		G_Antiaim->doIt(g_Globals->usercmd, pbSendPacket);
		QAngle VisualAngles = cmd->viewangles;
		if (*pbSendPacket)
		{

		}
		else
		{
			animations->m_flHeadHeightOrOffsetFromHittingGroundAnimation = 0.f;
			g_Globals->RealAngle = cmd->viewangles;;
			animations->m_flHeadHeightOrOffsetFromHittingGroundAnimation = 0.f;
		}
	}

	return false;
}
