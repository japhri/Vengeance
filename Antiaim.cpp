#include "Antiaim.h"
#include "Autowall.h"
#include "Math.h"


float get_curtime() {
	C_BaseEntity* pLocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	if (!g_Globals->local)
		return 0;
	int g_tick = 0;
	CUserCmd* g_pLastCmd = nullptr;
	if (!g_pLastCmd || g_pLastCmd->hasbeenpredicted) {
		g_tick = g_Globals->local->GetTickBase();
	}
	else {
		++g_tick;
	}
	g_pLastCmd = g_Globals->usercmd;
	float curtime = g_tick * G_Globals->intervalPerTick;
	return curtime;
}


bool next_lby_update()
{
	C_BaseEntity* pLocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	if (g_Globals->local)
	{
		auto net_channel = G_Engine->GetNetChannel();
		static float next_lby_update_time = 0;
		const float current_time = get_curtime();

		if (g_Globals->local->GetVelocity().Length2D() > 0.1) {
			next_lby_update_time = current_time + 0.22f;
		}
		else {
			if ((next_lby_update_time < current_time && !net_channel->m_nChokedPackets)) {
				next_lby_update_time = current_time + 1.1f;
				return true;
			}
		}
	}
	return false;
}



void antiaim::doAntiAims(CUserCmd* cmd, bool* bSendPacket)
{
	g_Globals->antiaiming = false;

	freestandingUpdated = false;

	cameraViewAngles = cmd->viewangles;

	if (!g_Options.antiAimEnable)
		return;

	C_BaseEntity *LocalPlayer = (C_BaseEntity*)G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	

	if (cmd->buttons & IN_USE)
		return;
	if (LocalPlayer->IsProtected() || *LocalPlayer->GetFlags() & FL_FROZEN)
		return;


	auto gitwep = LocalPlayer->GetWeapon();

	if (!gitwep)
		return;



	if (LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || LocalPlayer->GetMoveType() == MOVETYPE_LADDER)
		return;

	if (cmd->buttons & IN_ATTACK)
		return;


	g_Globals->antiaiming = true;

	float curpos = cmd->viewangles.y + 180.f;

	float realYaw;
	float fakeYaw;
	bool hasFake = g_Options.antiAimFake;

	AntiAimSetting *antiAimYaw = nullptr;
	AntiAimSetting *antiAimFake = nullptr;

	// Jumping AA
	if (!(*LocalPlayer->GetFlags() & FL_ONGROUND))
	{
		antiAimYaw = &g_Options.antiAimJumpingReal;
		antiAimFake = &g_Options.antiAimJumpingFake;
	}
	// Moving AA
	else if (LocalPlayer->Velocity().Length() > 14.0)
	{
		antiAimYaw = &g_Options.antiAimMovingReal;
		antiAimFake = &g_Options.antiAimMovingFake;
	}
	// Standing AA
	else
	{
		antiAimYaw = &g_Options.antiAimStillReal;
		antiAimFake = &g_Options.antiAimStillFake;
	}

	realYaw = buildYaw(antiAimYaw);
	fakeYaw = buildYaw(antiAimFake);

	if (hasFake && *bSendPacket)
		lastFake = fakeYaw;
	else
		lastReal = realYaw;

	lastCameraYaw = cmd->viewangles.y;

	lastPitch = doPitch();

	cmd->viewangles = QAngle(lastPitch, (hasFake && *bSendPacket) ? fakeYaw : realYaw, 0);

	if (hasFake)
		g_Globals->sendpacket = *bSendPacket;






}

float antiaim::doPitch()
{
	if (!g_Options.allowUntrusted)
	{
		//g_Options.antiAimPitchFloat = max(-89.0, min(89.0, g_Options.antiAimPitch));

		if (g_Options.antiAimPitch > 4)
		{
			switch (g_Options.antiAimPitch)
			{
			case 5:
				g_Options.antiAimPitch = 2;
				break;
			case 6:
				g_Options.antiAimPitch = 3;
				break;
			case 7:
				g_Options.antiAimPitch = 4;
				break;
			case 8:
				g_Options.antiAimPitch = 2;
				break;
			case 9:
				g_Options.antiAimPitch = 4;
				break;
			default:
				g_Options.antiAimPitch = 0;
				break;
			}
		}
	}

	switch (g_Options.antiAimPitch)
	{
	case 0:
		return g_Globals->usercmd->viewangles.x;
	case 1:
		return g_Globals->usercmd->viewangles.x = g_Options.antiAimPitchCustom;
	case 2:
		return g_Globals->usercmd->viewangles.x = 89.0f;
	case 3:
		return g_Globals->usercmd->viewangles.x = 0.0f;
	case 4:
		return g_Globals->usercmd->viewangles.x = -89.0f;
	case 5:
		return g_Globals->usercmd->viewangles.x = 270.0f;
	case 6:
		return g_Globals->usercmd->viewangles.x = -360.0f;
	case 7:
		return g_Globals->usercmd->viewangles.x = -270.0f;
	case 8:
		return g_Globals->usercmd->viewangles.x = 90.0f;
	case 9:
		return g_Globals->usercmd->viewangles.x = -90.0f;
	}

	return g_Globals->usercmd->viewangles.x;
}

Vector get_hitbox_location(C_BaseEntity* obj, int hitbox_id) {
	matrix3x4_t bone_matrix[128];

	if (obj->SetupBones2(bone_matrix, 128, 0x00000100, 0.0f)) {
		if (obj->GetModel()) {
			auto studio_model = G_ModelInfo->GetStudioModel(obj->GetModel());
			if (studio_model) {
				auto hitbox = studio_model->pHitboxSet(0)->pHitbox(hitbox_id);
				if (hitbox) {
					auto min = Vector{}, max = Vector{};

					Math::VectorTransform(hitbox->bbmin, bone_matrix[hitbox->bone], min);
					Math::VectorTransform(hitbox->bbmax, bone_matrix[hitbox->bone], max);

					return (min + max) / 2.0f;
				}
			}
		}
	}
	return Vector{};
}

void angle_vectors(const Vector &angles, Vector& forward)
{
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float	sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}

/*FORCEINLINE*/ void vector_subtract(const Vector& a, const Vector& b, Vector& c)
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

void normalize(Vector &vIn, Vector &vOut)
{
	float flLen = vIn.Length();
	if (flLen == 0) {
		vOut.Init(0, 0, 1);
		return;
	}
	flLen = 1 / flLen;
	vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}


bool is_viable_target(void* pEntity)
{
	C_BaseEntity* entity = (C_BaseEntity*)pEntity;
	C_BaseEntity *LocalPlayer = (C_BaseEntity*)G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	if (!entity) return false;
	if (entity == LocalPlayer) return false;
	if (entity->GetTeamNum() == LocalPlayer->GetTeamNum()) return false;
	if (entity->IsProtected()) return false;
	if (!entity->isAlive() || entity->IsDormant()) return false;
	return true;
}

int antiaim::curtime_fixed_ticks(CUserCmd* ucmd) {
	auto LocalPlayer = (C_BaseEntity*)G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	static int g_tick = 0;
	static CUserCmd* g_pLastCmd = nullptr;
	if (!g_pLastCmd || g_pLastCmd->hasbeenpredicted) {
		g_tick = LocalPlayer->GetTickBase();
	}
	else {
		++g_tick;
	}
	g_pLastCmd = ucmd;
	return g_tick;
}
float RandomFloat(float min, float max)
{
	static auto ranFloat = reinterpret_cast<float(*)(float, float)>(GetProcAddress(GetModuleHandle("vstdlib.dll"), "RandomFloat"));
	if (ranFloat)
		return ranFloat(min, max);
	else
		return 0.f;
}

float antiaim::buildYaw(AntiAimSetting *antiAim)
{
	float out = 0.0;
	float offset = 0.0;

	static bool wasPressing = false;

	if (!wasPressing && G_InputSystem->IsButtonDown(g_Options.antiAimFlipKey))
	{
		g_Options.antiAimFlip = !g_Options.antiAimFlip;
	}

	wasPressing = G_InputSystem->IsButtonDown(g_Options.antiAimFlipKey);

	if (antiAim->jitterFlipTicks < 1) antiAim->jitterFlipTicks = 1;

	switch (antiAim->base)
	{
		// Camera Yaw
	case 0:
		out += g_Globals->usercmd->viewangles.y;
		break;
		// 1 = Zero
		// At Targets
	case 2:
	{
		C_BaseEntity * LocalPlayer = (C_BaseEntity*)G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
		auto fov_to_player = [](Vector view_offset, Vector view, C_BaseEntity* m_entity, int hitbox)
		{
			CONST FLOAT MaxDegrees = 180.0f;
			Vector Angles = view;
			Vector Origin = view_offset;
			Vector Delta(0, 0, 0);
			Vector Forward(0, 0, 0);
			angle_vectors(Angles, Forward);
			Vector AimPos = get_hitbox_location(m_entity, hitbox);
			vector_subtract(AimPos, Origin, Delta);
			normalize(Delta, Delta);
			FLOAT DotProduct = Forward.Dot(Delta);
			return (acos(DotProduct) * (MaxDegrees / PI));
		};

		int target = -1;
		float mfov = 181.0f;

		Vector viewoffset = LocalPlayer->GetOrigin() + LocalPlayer->GetViewOffset();
		Vector view; G_Engine->GetViewAngles(view);

		for (int i = 0; i < G_Globals->maxClients; i++) {
			C_BaseEntity* m_entity = (C_BaseEntity*)G_EntList->GetClientEntity(i);

			if (is_viable_target(m_entity)) {

				float fov = fov_to_player(viewoffset, view, m_entity, 0);
				if (fov < mfov) {
					mfov = fov;
					target = i;
				}
			}
		}

		if (target != -1)
		{
			C_BaseEntity *targetEnt = G_EntList->GetClientEntity(target);

			Vector targetPos = targetEnt->GetOrigin();
			Vector localPos = LocalPlayer->GetOrigin();

			float angleTo = atan2(targetPos.y - localPos.y, targetPos.x - localPos.x);

			out += angleTo / PI * 180.0f;
		}
		break;
	}
	// Freestanding
	case 3:
	{
		switch (g_Options.antiAimFreestandingMethod)
		{
		case 0:
		{
			if (g_Options.antiAimFreestandingScanQuality == 0 || !AutoWallFreestanding(g_Globals->usercmd, &out))
			{
				TraceRayFreestanding(g_Globals->usercmd, &out);
				//g_CVar->ConsolePrintf("AutoWall Freestanding failed, fell back to TraceRay Freestanding!\n");
			}
			break;
		}
		case 1:
		{
			//StylishFreestanding(cmd, &out);
			break;
		}
		}
		break;
	}
	}

	offset += antiAim->add;

	switch (antiAim->addon)
	{
		// Jitter
	case 1:
	{
		switch (antiAim->jitterMode)
		{
			// Random
		case 0:
			offset += RandomFloat(-antiAim->jitterRange / 2.0f, antiAim->jitterRange / 2.0f);
			break;
			// Flip
		case 1:
			if (curtime_fixed_ticks(g_Globals->usercmd) % (antiAim->jitterFlipTicks * 2) < antiAim->jitterFlipTicks)
				offset += antiAim->jitterRange / 2.0f;
			else
				offset -= antiAim->jitterRange / 2.0f;
			break;
		}
		break;
	}
	// Spinbot
	case 2:
		if (antiAim->spinbotRange == 0.0f) break;
		switch (antiAim->spinbotMode)
		{
			// Loop
		case 0:
			offset += fmod(G_Globals->curtime * antiAim->spinbotSpeed * 360.0f, antiAim->spinbotRange) - antiAim->spinbotRange / 2.0f;
			break;
			// Ping-Pong
		case 1:
		{
			float spinAmt = fmod(G_Globals->curtime * antiAim->spinbotSpeed * 360.0f, antiAim->spinbotRange * 2.0f);
			if (spinAmt < antiAim->spinbotRange)
			{
				offset += spinAmt - antiAim->spinbotRange / 2.0f;
			}
			else
			{
				offset += antiAim->spinbotRange * 1.5f - spinAmt;
			}
			break;
		}
		}
		break;
	}

	if (g_Options.antiAimFlipEnable && g_Options.antiAimFlip)
	{
		switch (g_Options.antiAimFlipMethod)
		{
			// Mirror
		case 0:
			out -= offset;
			break;
			// Add 180
		case 1:
			out += offset + 180.0f;
			break;
		}
	}
	else
		out += offset;

	return out;
}

bool antiaim::TraceRayFreestanding(CUserCmd* cmd, float* out)
{
	if (!freestandingUpdated)
	{
		//g_CVar->ConsolePrintf("TR FREESTANDING\n");

		C_BaseEntity* LocalPlayer = (C_BaseEntity*)G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
		Vector eye_position = LocalPlayer->GetEyePosition2();
		float yaw = cmd->viewangles.y + 180.0f;
		float distance = 20.0f;
		float mfov = 181.0f;
		Vector viewoffset = LocalPlayer->GetOrigin() + LocalPlayer->GetViewOffset();
		Vector view; G_Engine->GetViewAngles(view);
		Vector origin = LocalPlayer->GetOrigin();
		int steps = 0;

		switch (g_Options.antiAimFreestandingQuality)
		{
		case 0:
			steps = 8;
			break;
		case 1:
			steps = 16;
			break;
		case 2:
			steps = 32;
			break;
		}

		/*std::vector<trace_t> _fromTrace;
		std::vector<Ray_t> _fromRay;

		std::vector<trace_t> _toTrace;
		std::vector<Ray_t> _toRay;*/

		static trace_t _fromTrace[32];
		static Ray_t _fromRay[32];

		static trace_t _toTrace[32];
		static Ray_t _toRay[32];

		static bool hitWall = false;
		static bool hitHead = false;

		static int stutterStep = 0;

		if (g_Options.antiAimFreestandingStutteredUpdates)
		{
			if (stutterStep == 0)
			{
				hitWall = false;
				hitHead = false;
			}

			stutterStep = 1 - stutterStep;
		}
		else
		{
			hitWall = false;
			hitHead = false;
		}

		for (int step = 0; step < steps; step++)
		{
			if (g_Options.antiAimFreestandingStutteredUpdates)
			{
				if (step % 2 == stutterStep)
				{
					//g_CVar->ConsolePrintf("Skipping step %i\n", step);
					continue;
				}
			}

			float a = (float)step / (float)steps * static_cast<float>(M_PI) * 2.0f;
			/*Vector head_position(cos(a) * distance + eye_position.x,
			sin(a) * distance + eye_position.y,
			eye_position.z);*/
			Vector head_position = LocalPlayer->GetBonePos(8);
			//float head_dist = (head_position - origin).Length2D();
			head_position = Vector(origin.x + cos(a) * distance, origin.y + sin(a) * distance, head_position.z);
			float health = 100000.0f;//100.0f;
			for (int i = 0; i < G_Engine->GetMaxClients(); ++i)
			{
				C_BaseEntity* ent = (C_BaseEntity*)G_EntList->GetClientEntity(i);
				if (!ent) continue;
				if (ent == LocalPlayer) continue;
				if (ent->GetTeamNum() == LocalPlayer->GetTeamNum()) continue;
				if (ent->IsProtected()) continue;
				if (!ent->isAlive()) continue;

				Vector dir = (head_position - ent->GetEyePosition2()).Normalized();

				trace_t fromTrace;
				Ray_t fromRay;
				CTraceFilter fromFilter;

				trace_t toTrace;
				Ray_t toRay;
				CTraceFilter toFilter;

				fromFilter.pSkip = ent;
				toFilter.pSkip = LocalPlayer;

				fromRay.Init(ent->GetEyePosition2(), ent->GetEyePosition2() + dir * 65536.0f);
				toRay.Init(head_position, head_position - dir * 65536.0f);

				G_EngineTrace->TraceRay(fromRay, MASK_SHOT, &fromFilter, &fromTrace);
				G_EngineTrace->TraceRay(toRay, MASK_SHOT, &toFilter, &toTrace);

				_fromTrace[step] = fromTrace;
				_fromRay[step] = fromRay;
				_toTrace[step] = toTrace;
				_toRay[step] = toRay;

				//g_CVar->ConsolePrintf("Updated step %i\n", step);

				if ((fromTrace.startpos - fromTrace.endpos).Length() >= (fromTrace.startpos - head_position).Length() - 32.0f || fromTrace.hit_entity->Index() == G_Engine->GetLocalPlayer())
				{
					hitHead = true;
				}
				else
				{
					hitWall = true;
				}
			}
		}

		/*if (hitHead)
		g_CVar->ConsolePrintf("HIT HEAD!\n");
		else
		g_CVar->ConsolePrintf("DID NOT HIT HEAD!\n");

		if (hitWall)
		g_CVar->ConsolePrintf("HIT WALL!\n");
		else
		g_CVar->ConsolePrintf("DID NOT HIT WALL!\n");*/

		float bestHealth = -65536.0f;

		for (int step = 0; step < steps; step++)
		{
			float a = (float)step / (float)steps * static_cast<float>(M_PI) * 2.0f;
			/*Vector head_position(cos(a) * distance + eye_position.x,
			sin(a) * distance + eye_position.y,
			eye_position.z);*/
			Vector head_position = LocalPlayer->GetBonePos(8);
			//float head_dist = (head_position - origin).Length2D();
			head_position = Vector(origin.x + cos(a) * distance, origin.y + sin(a) * distance, head_position.z);
			float health = 100000.0f;//100.0f;
			for (int i = 0; i < G_Engine->GetMaxClients(); ++i)
			{
				C_BaseEntity* ent = (C_BaseEntity*)G_EntList->GetClientEntity(i);
				if (!ent) continue;
				if (ent == LocalPlayer) continue;
				if (ent->GetTeamNum() == LocalPlayer->GetTeamNum()) continue;
				if (ent->IsProtected()) continue;
				if (!ent->isAlive()) continue;

				Vector targetDelta = ent->GetOrigin() - LocalPlayer->GetOrigin();
				float atTarget = atan2(targetDelta.y, targetDelta.x);
				float tempA = a;
				while (tempA < -M_PI) tempA += static_cast<float>(M_PI) * 2.0f;
				while (tempA > M_PI) tempA -= static_cast<float>(M_PI) * 2.0f;
				float aDelta = abs(atTarget - tempA);
				while (aDelta < -M_PI) aDelta += static_cast<float>(M_PI) * 2.0f;
				while (aDelta > M_PI) aDelta -= static_cast<float>(M_PI) * 2.0f;

				//g_CVar->ConsolePrintf("YAW %3.3f - ATTARGET %3.3f - A %3.3f\n", tempA / M_PI * 180.0f, atTarget / M_PI * 180.0f, tempA / M_PI * 180.0f);

				float dist = _toTrace[step].startpos.DistTo(_fromTrace[step].startpos);
				float toDist = _toTrace[step].startpos.DistTo(_toTrace[step].startpos);
				float fromDist = _fromTrace[step].startpos.DistTo(_fromTrace[step].endpos);

				float gap = (_toTrace[step].endpos - _fromTrace[step].endpos).Length();

				bool prioritizeBack = (hitWall && !hitHead) || (!hitWall && hitHead);

				float backScalar = 32.0f;

				if (prioritizeBack)
				{
					health += (abs(aDelta) - static_cast<float>(M_PI) / 2.0f) / static_cast<float>(M_PI) * backScalar;
				}

				if (gap <= 0.0f || toDist >= dist - fromDist - 32.0f || fromDist >= (_fromTrace[step].startpos - head_position).Length() - 32.0f || _fromTrace[step].hit_entity->Index() == G_Engine->GetLocalPlayer())
				{
					/*if (prioritizeBack)
					{
					g_CVar->ConsolePrintf("Heal => %4.4f (aDelta: %1.3f)\n", (abs(aDelta) - M_PI / 2.0f) / M_PI * backScalar, aDelta);
					}
					else
					{
					g_CVar->ConsolePrintf("\n");
					}*/
					health -= 2048.0f;
					//g_CVar->ConsolePrintf("Hit => -2048.0\n");
				}
				else
				{
					float perpendicular = 1.0f - abs(abs(aDelta) - static_cast<float>(M_PI) / 2.0f) / static_cast<float>(M_PI) * 2.0f;
					health += perpendicular * 8.0f;
					/*if (prioritizeBack)
					{
					g_CVar->ConsolePrintf("Heal => %4.4f + %4.4f (aDelta: %1.3f)\n", (abs(aDelta) - M_PI / 2.0f) / M_PI * backScalar, perpendicular * 8.0f, aDelta);
					}
					else
					{
					g_CVar->ConsolePrintf("Heal => %4.4f(aDelta: %1.3f)\n", perpendicular * 8.0f, aDelta);
					}*/
					health += gap * 1.25f - 1024.0f;
					float ratio = 1.0f - _toTrace[step].endpos.DistTo(ent->GetEyePosition2()) / _toTrace[step].startpos.DistTo(ent->GetEyePosition2());
					health -= ratio * 64.0f;
					//g_CVar->ConsolePrintf("Hit => %4.4f + %4.4f (ratio: %1.3f)\n", gap * 1.25f - 1024.0f, ratio * 64.0f, ratio);
				}
			}

			//g_CVar->ConsolePrintf("Health: %3.4f", health / 1000.0f);

			if (health > bestHealth)
			{
				//g_CVar->ConsolePrintf(" ---------------- New best!");
				bestHealth = health;
				yaw = a / static_cast<float>(M_PI) * 180.0f;
			}
			//g_CVar->ConsolePrintf("\n");
		}

		freestandingUpdated = true;

		if (!g_Options.antiAimFreestandingStutteredUpdates || stutterStep == 0)
		{
			float yawOffset = g_Utils->FindYawOffset(lastFreestanding, yaw);
			lastFreestanding += yawOffset;
			float smoothing = g_Options.antiAimFreestandingSmoothing;
			if (g_Options.antiAimFreestandingStutteredUpdates && stutterStep == 0)
			{
				smoothing *= 0.5f;
			}
			float mix = 1.0f - smoothing;
			mix = mix * mix;
			lastFreestanding = lastFreestanding * (1.0f - mix) + yaw * mix;
			lastFreestanding -= yawOffset;
			while (lastFreestanding < -180.0f) lastFreestanding += 360.0f;
			while (lastFreestanding > 180.0f) lastFreestanding -= 360.0f;
		}

		//g_CVar->ConsolePrintf("----------------\n");
	}

	*out = lastFreestanding;
	return true;
}

bool antiaim::AutoWallFreestanding(CUserCmd* cmd, float* out)
{
	if (!freestandingUpdated)
	{
		//g_CVar->ConsolePrintf("AW FREESTANDING\n");

		auto LocalPlayer = (C_BaseEntity*)G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
		Vector eye_position = LocalPlayer->GetEyePosition2();
		float yaw = cmd->viewangles.y + 180.0f;
		float distance = 16.0f;
		float mfov = 181.0f;
		Vector viewoffset = LocalPlayer->GetOrigin() + LocalPlayer->GetViewOffset();
		Vector view; G_Engine->GetViewAngles(view);
		Vector origin = LocalPlayer->GetOrigin();
		float bestHealth = -1.0f;
		int steps = 0;

		switch (g_Options.antiAimFreestandingQuality)
		{
		case 0:
			steps = 8;
			break;
		case 1:
			steps = 16;
			break;
		case 2:
			steps = 192;
			break;
		}

		//std::vector<float> damages;
		static float damages[192];

		static bool hitWall = false;
		static bool hitHead = false;

		static int stutterStep = 0;

		if (g_Options.antiAimFreestandingStutteredUpdates)
		{
			if (stutterStep == 0)
			{
				hitWall = false;
				hitHead = false;
			}

			stutterStep = 1 - stutterStep;
		}
		else
		{
			hitWall = false;
			hitHead = false;
		}

		for (int step = 0; step < steps; step++)
		{
			if (g_Options.antiAimFreestandingStutteredUpdates)
			{
				stutterStep = 1 - stutterStep;
				if (step % 2 == stutterStep)
				{
					continue;
				}
			}

			//damages[step] = 0.0f;
			float a = (float)step / (float)steps * static_cast<float>(M_PI) * 2.0f;
			Vector head_position = LocalPlayer->GetBonePos(8);
			head_position = Vector(origin.x + cos(a) * distance, origin.y + sin(a) * distance, head_position.z);
			for (int i = 0; i < G_Globals->maxClients; ++i)
			{
				C_BaseEntity* ent = (C_BaseEntity*)G_EntList->GetClientEntity(i);
				if (ent == nullptr || !ent->IsValidTarget())
					continue;

				//float damage = G_Autowall->enemycanhit2(ent, ent->GetEyePosition2(), head_position); // need to fix this for 100% accurate freestanding 

				float damage = G_Autowall->EnemyCanHit(ent, ent->GetEyePosition2(), head_position);

				//damages[step] += damage;
				damages[step] = damage;

				if (damage >= 0.0f)
				{
					hitHead = true;
				}
				else
				{
					hitWall = true;
				}
			}
		}

		int hit = 0;

		for (int step = 0; step < steps; step++)
		{
			float a = (float)step / (float)steps * static_cast<float>(M_PI) * 2.0f;
			Vector head_position = LocalPlayer->GetBonePos(8);
			head_position = Vector(origin.x + cos(a) * distance, origin.y + sin(a) * distance, head_position.z);
			float health = 100.0f;
			for (int i = 0; i < G_Engine->GetMaxClients(); ++i)
			{
				C_BaseEntity* ent = (C_BaseEntity*)G_EntList->GetClientEntity(i);
				if (ent == nullptr || !ent->IsValidTarget())
					continue;

				Vector targetDelta = ent->GetOrigin() - LocalPlayer->GetOrigin();
				float atTarget = atan2(targetDelta.y, targetDelta.x);
				float tempA = a;
				while (tempA < -M_PI) tempA += static_cast<float>(M_PI) * 2.0f;
				while (tempA > M_PI) tempA -= static_cast<float>(M_PI) * 2.0f;
				float aDelta = abs(atTarget - tempA);
				while (aDelta < -M_PI) aDelta += static_cast<float>(M_PI) * 2.0f;
				while (aDelta > M_PI) aDelta -= static_cast<float>(M_PI) * 2.0f;

				//g_CVar->ConsolePrintf("YAW %3.3f - ATTARGET %3.3f - A %3.3f\n", tempA / M_PI * 180.0f, atTarget / M_PI * 180.0f, tempA / M_PI * 180.0f);

				float damage = damages[step];

				bool prioritizeBack = (hitWall && !hitHead) || (!hitWall && hitHead);

				float back = (abs(aDelta) - static_cast<float>(M_PI) / 2.0f) / static_cast<float>(M_PI);
				float backScalar = 4.0f;

				if (prioritizeBack)
				{
					health += back * backScalar;
					//g_CVar->ConsolePrintf("Heal => %4.4f (back: %1.3f)\n", back * backScalar, back);
				}
				else
				{
					//g_CVar->ConsolePrintf("Heal => 0 (wtf shit mercy)\n");
				}

				if (damage >= 0.0f)
				{
					//g_CVar->ConsolePrintf("Hit => %3.3f\n", damage);
					health -= damage;
					++hit;
				}
				else
				{
					float perpendicularScalar = 1.0f;
					float perpendicular = 1.0f - abs(abs(aDelta) - static_cast<float>(M_PI) / 2.0f) / static_cast<float>(M_PI) * 2.0f;
					health += perpendicular * perpendicularScalar;
					//g_CVar->ConsolePrintf("Heal => %4.4f (perpendicular: %1.3f)\n", perpendicular * perpendicularScalar, perpendicular);
				}
			}
			//g_CVar->ConsolePrintf("Health: %3.3f", health);
			if (health > bestHealth)
			{
				//g_CVar->ConsolePrintf(" ---------------- New best!");
				bestHealth = health;
				yaw = a / static_cast<float>(M_PI) * 180.0f;
			}
			//g_CVar->ConsolePrintf("\n");
		}

		//g_CVar->ConsolePrintf("Hit: %i\n", hit);

		//g_CVar->ConsolePrintf("----------------\n");

		if (hit <= 0)
		{
			return false;
		}

		freestandingUpdated = true;

		if (!g_Options.antiAimFreestandingStutteredUpdates || stutterStep == 0)
		{
			float yawOffset = g_Utils->FindYawOffset(lastFreestanding, yaw);
			lastFreestanding += yawOffset;
			float smoothing = g_Options.antiAimFreestandingSmoothing;
			if (g_Options.antiAimFreestandingStutteredUpdates && stutterStep == 0)
			{
				smoothing *= 0.5f;
			}
			float mix = 1.0f - smoothing;
			mix = mix * mix;
			lastFreestanding = lastFreestanding * (1.0f - mix) + yaw * mix;
			lastFreestanding -= yawOffset;
			while (lastFreestanding < -180.0f) lastFreestanding += 360.0f;
			while (lastFreestanding > 180.0f) lastFreestanding -= 360.0f;
		}
	}

	*out = lastFreestanding;
	return true;
}
void antiaim::freestanding(CUserCmd* cmd)
{
	auto LocalPlayer = (C_BaseEntity*)G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	Vector eye_position = LocalPlayer->GetEyePosition2();
	float yaw = cmd->viewangles.y;
	float distance = 16.0f;
	float mfov = 181.0f;
	Vector viewoffset = LocalPlayer->GetOrigin() + LocalPlayer->GetViewOffset();
	Vector view; G_Engine->GetViewAngles(view);
	Vector origin = LocalPlayer->GetOrigin();
	float bestHealth = -1.0f;
	int steps = 48;
	static float damages[48];
	float health = 100.0f;
	for (int step = 0; step < steps; step++)
	{
		float a = (float)step / (float)steps * static_cast<float>(M_PI) * 2.0f;
		Vector head_position = LocalPlayer->GetBonePos(8);
		head_position = Vector(origin.x + cos(a) * distance, origin.y + sin(a) * distance, head_position.z);

		for (int i = 0; i < G_Globals->maxClients; i++)
		{
			auto Entity = G_EntList->GetClientEntity(i);
			if (Entity == nullptr || !Entity->IsValidRenderable())
				continue;
			float damage = G_Autowall->EnemyCanHit(Entity, Entity->GetEyePosition2(), head_position);
			damages[step] = damage;
			if (damage > 0.f)
			{
				health -= damage;
				printf("Health getting hit %f\n", health);
		}
			if (health > bestHealth)
			{
				bestHealth = health;
				yaw = a / static_cast<float>(M_PI) * 180.0f;
			}
			
		}
	}
	printf(" best Yaw : %f\n", yaw);
}

void antiaim::doIt(CUserCmd* cmd, bool* bSendPacket)
{
	C_BaseEntity *LocalPlayer = (C_BaseEntity*)G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	if (!LocalPlayer || !LocalPlayer->GetWeapon())
		return;

	

	if ((!(cmd->buttons & IN_ATTACK) || !(cmd->buttons & IN_USE)))
	{
		if (g_Options.antiAimEnable)
		{

			QAngle oldAngle = cmd->viewangles;
			float oldForward = cmd->forwardmove;
			float oldSideMove = cmd->sidemove;


		
			doAntiAims(cmd, bSendPacket);


			Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);
		}
	}
}


