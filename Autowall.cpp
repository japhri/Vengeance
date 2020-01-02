#include "Autowall.h"
#include "Math.h"
bool CAutowall::DidHitNonWorldEntity(C_BaseEntity* m_pEnt)
{
	return m_pEnt != NULL && m_pEnt != G_EntList->GetClientEntity(0);
}

bool CAutowall::IsWorldEntity(C_BaseEntity* m_pEnt)
{
	return m_pEnt != NULL && m_pEnt->Index() == 0;
}

bool CAutowall::isBreakableEntity(C_BaseEntity *pEntity)
{
	if (pEntity == NULL)
		return false;

	if (pEntity->Index() == 0)
		return false;

	auto takeDamage{ (char *)((uintptr_t)pEntity + *(size_t *)((uintptr_t)IsBreakableEntity + 38)) };
	auto takeDamageBackup{ *takeDamage };

	ClientClass *pClass = G_Client->GetAllClasses();

	if ((pClass->m_pNetworkName[1]) != 'F'
		|| (pClass->m_pNetworkName[4]) != 'c'
		|| (pClass->m_pNetworkName[5]) != 'B'
		|| (pClass->m_pNetworkName[9]) != 'h')
		*takeDamage = DAMAGE_YES;

	bool breakable = IsBreakableEntity(pEntity);
	*takeDamage = takeDamageBackup;

	return breakable;
}


void CAutowall::ClipTraceToPlayers(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, ITraceFilter *filter, CGameTrace *tr)
{
	_asm
	{
		mov eax, filter
		lea ecx, tr
		push ecx
		push eax
		push mask
		lea edx, vecAbsEnd
		lea ecx, vecAbsStart
		call _ClipTraceToPlayers
		add esp, 0xC
	}
}


void CAutowall::TraceLine(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, C_BaseEntity* ignore, CGameTrace* ptr)
{
	Ray_t ray;
	ray.Init(vecAbsStart, vecAbsEnd);
	CTraceFilter filter;
	filter.pSkip = ignore;

	G_EngineTrace->TraceRay(ray, mask, &filter, ptr);
}

bool CAutowall::IsArmored(C_BaseEntity* Entity, int ArmorValue, HitGroups Hitgroup)
{

	C_BaseEntity* Player = (C_BaseEntity*)Entity;

	if (!Player)
		return false;

	bool result = false;

	if (ArmorValue > 0)
	{
		switch (Hitgroup)
		{
		case HitGroups::HITGROUP_GENERIC:
		case HitGroups::HITGROUP_CHEST:
		case HitGroups::HITGROUP_STOMACH:
		case HitGroups::HITGROUP_LEFTARM:
		case HitGroups::HITGROUP_RIGHTARM:
			result = true;
			break;
		case HitGroups::HITGROUP_HEAD:
			result = Player->HasHelmet(); // DT_CSPlayer -> m_bHasHelmet
			break;
		}
	}

	return result;
}


bool CAutowall::TraceToExit(CGameTrace *enterTrace, Vector vecStartPosition, Vector vecDir, CGameTrace *exitTrace)
{
	Vector vecEnd;
	float flDistance = 0.f;
	signed int iDistanceCheck = 23;
	int iFirstContents = 0;

	do // We want to call the code once before checking for distance
	{
		flDistance += 4.f;
		vecEnd = vecStartPosition + vecDir * flDistance;

		if (!iFirstContents)
			iFirstContents = G_EngineTrace->GetPointContents(vecEnd, MASK_SHOT | CONTENTS_GRATE, NULL); /*0x4600400B*/
		int iPointContents = G_EngineTrace->GetPointContents(vecEnd, MASK_SHOT | CONTENTS_GRATE, NULL);

		if (!(iPointContents & (MASK_SHOT_HULL | CONTENTS_HITBOX)) || iPointContents & CONTENTS_HITBOX && iPointContents != iFirstContents) /*0x600400B, *0x40000000*/
		{
			Vector vecNewEnd = vecEnd - (vecDir * 4.f);

			Ray_t ray;
			ray.Init(vecEnd, vecNewEnd);

			G_EngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, nullptr, exitTrace);

			if (exitTrace->startsolid && exitTrace->surface.flags & SURF_HITBOX) //A Hitbox is infront of the enemy and the enemy is behind a solid wall
			{
				TraceLine(vecEnd, vecStartPosition, MASK_SHOT_HULL | CONTENTS_HITBOX, exitTrace->hit_entity, exitTrace);

				if (exitTrace->DidHit() && !exitTrace->startsolid) //DidHit() && !startsolid
					return true;
				continue;
			}

			if (exitTrace->DidHit() && !exitTrace->startsolid)
			{
				if (enterTrace->surface.flags & SURF_NODRAW || !(exitTrace->surface.flags & SURF_NODRAW))
				{
					if (exitTrace->plane.normal.Dot(vecDir) <= 1.f)
						return true;
					continue;
				}

				//For some reason, Skeet's pesudo claims this is || but if you use ||, you will spam windowsils. I would have to look into this.
				if (isBreakableEntity(enterTrace->hit_entity) && isBreakableEntity(exitTrace->hit_entity))
					return true;
				continue;
			}

			if (exitTrace->surface.flags & SURF_NODRAW)
			{
				if (isBreakableEntity(enterTrace->hit_entity) && isBreakableEntity(exitTrace->hit_entity))
					return true;
				else if (!(enterTrace->surface.flags & SURF_NODRAW))
					continue;
			}

			if (IsWorldEntity(enterTrace->hit_entity) && (isBreakableEntity(enterTrace->hit_entity)))
			{
				exitTrace = enterTrace;
				exitTrace->endpos = vecStartPosition + vecDir;
				return true;
			}
			continue;
		}
		--iDistanceCheck;
	} while (iDistanceCheck); //Distance check

	return false;
}


bool CAutowall::HandleBulletPenetration(CSWeaponInfo *wpn_data, FireBulletData &data)
{
	CGameTrace trace_exit;
	surfacedata_t *enterSurfaceData = G_PhysicProps->GetSurfaceData(data.enterTrace.surface.surfaceProps);
	int iEnterMaterial = enterSurfaceData->game.material;

	float enterSurfPenetrationModifier = enterSurfaceData->game.flPenetrationModifier;
	float flFinalDamageModifier = 0.16f;
	float flCombinedPenetrationModifier = 0.f;
	bool isSolidSurf = ((data.enterTrace.contents >> 3) & CONTENTS_SOLID);
	bool isLightSurf = ((data.enterTrace.surface.flags >> 7) & SURF_LIGHT);

	if (data.penetrateCount <= 0
		|| (!data.penetrateCount && !isLightSurf && !isSolidSurf && iEnterMaterial != CHAR_TEX_GLASS && iEnterMaterial != CHAR_TEX_GRATE)
		|| wpn_data->penetration <= 0.f
		|| !TraceToExit(&data.enterTrace, data.enterTrace.endpos, data.direction, &trace_exit)
		&& !(G_EngineTrace->GetPointContents(data.enterTrace.endpos, MASK_SHOT_HULL | CONTENTS_HITBOX, NULL) & (MASK_SHOT_HULL | CONTENTS_HITBOX)))
		return false;

	surfacedata_t *exitSurfaceData = G_PhysicProps->GetSurfaceData(trace_exit.surface.surfaceProps);
	int iExitMaterial = exitSurfaceData->game.material;
	float exitSurfPenetrationModifier = exitSurfaceData->game.flPenetrationModifier;

	if (iEnterMaterial == CHAR_TEX_GLASS || iEnterMaterial == CHAR_TEX_GRATE)
	{
		flCombinedPenetrationModifier = 3.f;
		flFinalDamageModifier = 0.05f;
	}

	else if (isLightSurf || isSolidSurf)
	{
		flCombinedPenetrationModifier = 1.f;
		flFinalDamageModifier = 0.16f;
	}
	else
	{
		flCombinedPenetrationModifier = (enterSurfPenetrationModifier + exitSurfPenetrationModifier) * 0.5f;
		flFinalDamageModifier = 0.16f;
	}

	if (iEnterMaterial == iExitMaterial)
	{
		if (iExitMaterial == CHAR_TEX_CARDBOARD || iExitMaterial == CHAR_TEX_WOOD)
			flCombinedPenetrationModifier = 3.f;
		else if (iExitMaterial == CHAR_TEX_PLASTIC)
			flCombinedPenetrationModifier = 2.0f;
	}

	float flThickness = (trace_exit.endpos - data.enterTrace.endpos).LengthSqr();
	float flModifier = fmaxf(0.f, 1.f / flCombinedPenetrationModifier);

	float flLostDamage = fmaxf(
		((flModifier * flThickness) / 24.f) //* 0.041666668
		+ ((data.currentDamage * flFinalDamageModifier)
			+ (fmaxf(3.75f / wpn_data->penetration, 0.f) * 3.f * flModifier)), 0.f);

	if (flLostDamage > data.currentDamage)
		return false;

	if (flLostDamage > 0.f)
		data.currentDamage -= flLostDamage;

	if (data.currentDamage < 1.f)
		return false;

	data.src = trace_exit.endpos;
	data.penetrateCount--;

	return true;
}


bool CAutowall::SimulateFireBullet(CBaseCombatWeapon* pWeapon, FireBulletData &data, bool runOnce)
{
	if (pWeapon == NULL)
		return false;

	C_BaseEntity* g_LocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	CGameTrace exitTrace;
	C_BaseEntity* pLocalEntity = (C_BaseEntity*)g_LocalPlayer;
	ClientClass* pClass = (ClientClass*)pLocalEntity->GetClientClass();
	CSWeaponInfo* weaponData = pWeapon->GetCSWeaponData();
	surfacedata_t *enterSurfaceData = G_PhysicProps->GetSurfaceData(data.enterTrace.surface.surfaceProps);
	float enterSurfPenetrationModifier = enterSurfaceData->game.flPenetrationModifier;

	data.penetrateCount = 4;
	data.traceLength = 0.0f;

	if (weaponData == NULL)
		return false;

	data.currentDamage = (float)weaponData->damage;

	if (data.penetrateCount > 0)
	{
		while (data.currentDamage > 1.f)
		{
			data.traceLengthRemaining = weaponData->range - data.traceLength;

			Vector end = (data.direction * data.traceLengthRemaining) + data.src;

			TraceLine(data.src, end, MASK_SHOT | CONTENTS_GRATE, pLocalEntity, &data.enterTrace);

			ClipTraceToPlayers(data.src, end + data.direction * 40.f, MASK_SHOT | CONTENTS_GRATE, &data.filter, &data.enterTrace);

			if (data.enterTrace.fraction == 1.0f)
				break;

			data.traceLength += data.enterTrace.fraction * data.traceLengthRemaining;
			data.currentDamage *= weaponData->range_modifier; //pow's and random numbers are for the weak, fuck off, 0.002

			if (((data.enterTrace.hitgroup <= HitGroups::HITGROUP_RIGHTLEG) && (data.enterTrace.hitgroup > HitGroups::HITGROUP_GENERIC) && (C_BaseEntity*)pLocalEntity && pClass->m_ClassID == 35 && ((C_BaseEntity*)pLocalEntity)->GetTeamNum() != ((C_BaseEntity*)data.enterTrace.hit_entity)->GetTeamNum()) && (((C_BaseEntity*)data.enterTrace.hit_entity)->GetTeamNum() == 2 || ((C_BaseEntity*)data.enterTrace.hit_entity)->GetTeamNum() == 3))
			{
				bool HeavyArmor = ((C_BaseEntity*)data.enterTrace.hit_entity)->m_bHasHeavyArmor(); // DT_CSPlayer -> m_bHasHeavyArmor
				int ArmorValue = ((C_BaseEntity*)data.enterTrace.hit_entity)->GetArmor(); // DT_CSPlayer -> m_ArmorValue

				HitGroups iHitGroup = data.enterTrace.hitgroup;

				switch (iHitGroup) //scaledamage
				{
				case HitGroups::HITGROUP_HEAD:
					if (HeavyArmor)//If the enemy is using Heavy Armor, headshots will do half damage.
						data.currentDamage *= 2.f * 0.5f;
					else
						data.currentDamage *= 2.f;
					break;
				case HitGroups::HITGROUP_STOMACH:
					data.currentDamage *= 1.25f;
					break;
				case HitGroups::HITGROUP_LEFTLEG:
				case HitGroups::HITGROUP_RIGHTLEG:
					data.currentDamage *= 0.75f;
					break;
				}

				if (IsArmored(data.enterTrace.hit_entity, ArmorValue, data.enterTrace.hitgroup))
				{
					float flBonusValue = 1.f, flArmorBonusRatio = 0.5f, flArmorRatio = weaponData->armor_ratio * 0.5f;

					if (HeavyArmor)
					{
						flArmorBonusRatio = 0.33f;
						flArmorRatio *= 0.5f;
						flBonusValue = 0.33f;
					}

					auto NewDamage = data.currentDamage * flArmorRatio;

					if (HeavyArmor)
						NewDamage *= 0.85f;

					if (((data.currentDamage - (data.currentDamage * flArmorRatio)) * (flBonusValue * flArmorBonusRatio)) > ArmorValue)
						NewDamage = data.currentDamage - (ArmorValue / flArmorBonusRatio);

					//Thanks esoterik <c>
					if (NewDamage > 115)
						NewDamage = 115;

					data.currentDamage = NewDamage;
				}
				return true;
			}

			if ((data.traceLength > 3000.f) || (enterSurfPenetrationModifier < 0.1f) || !HandleBulletPenetration(weaponData, data))
				break;

			if (runOnce)
				return true;
		}
	}
	return false;
}


bool CAutowall::EnemySimulateFireBullet(C_BaseEntity * enemy, CBaseCombatWeapon* pWeapon, FireBulletData &data, bool runOnce, Vector stop)
{
	if (pWeapon == NULL)
		return false;

	CGameTrace exitTrace;
	C_BaseEntity* pLocalEntity = (C_BaseEntity*)enemy;
	if (!pLocalEntity) return false;
	CSWeaponInfo* weaponData = pWeapon->GetCSWeaponData();
	surfacedata_t *enterSurfaceData = G_PhysicProps->GetSurfaceData(data.enterTrace.surface.surfaceProps);
	float enterSurfPenetrationModifier = enterSurfaceData->game.flPenetrationModifier;
	ClientClass* pClass = (ClientClass*)pLocalEntity->GetClientClass();
	data.penetrateCount = 4;
	data.traceLength = 0.0f;
	C_BaseEntity* g_LocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	if (weaponData == NULL)
		return false;

	data.currentDamage = (float)weaponData->damage;

	float maxDist = data.src.DistTo(stop);

	if (data.penetrateCount > 0)
	{

		while (data.currentDamage > 1.f)
		{
			data.traceLengthRemaining = weaponData->range - data.traceLength;

			Vector end = (data.direction * data.traceLengthRemaining) + data.src;

			TraceLine(data.src, end, MASK_SHOT | CONTENTS_GRATE, pLocalEntity, &data.enterTrace);

			ClipTraceToPlayers(data.src, end + data.direction * 40.f, MASK_SHOT | CONTENTS_GRATE, &data.filter, &data.enterTrace);

			if (data.enterTrace.fraction == 1.0f)
				break;

			data.traceLength += data.enterTrace.fraction * data.traceLengthRemaining;
			data.currentDamage *= weaponData->range_modifier; //pow's and random numbers are for the weak, fuck off, 0.002

			if (data.traceLength >= maxDist || (pClass->m_ClassID == 35 && ((C_BaseEntity*)pLocalEntity)->GetTeamNum() != ((C_BaseEntity*)data.enterTrace.hit_entity)->GetTeamNum()) && (((C_BaseEntity*)data.enterTrace.hit_entity)->GetTeamNum() == 2 || ((C_BaseEntity*)data.enterTrace.hit_entity)->GetTeamNum() == 3))
			{
				bool HeavyArmor;
				int ArmorValue;
				HitGroups iHitGroup;
				bool isArmored;
				if (data.traceLength >= maxDist)
				{
					HeavyArmor = g_LocalPlayer->m_bHasHeavyArmor(); // DT_CSPlayer -> m_bHasHeavyArmor
					ArmorValue = g_LocalPlayer->GetArmor(); // DT_CSPlayer -> m_ArmorValue

					iHitGroup = HitGroups::HITGROUP_HEAD;
					isArmored = IsArmored(g_LocalPlayer, ArmorValue, iHitGroup);
				}
				else
				{
					HeavyArmor = ((C_BaseEntity*)data.enterTrace.hit_entity)->m_bHasHeavyArmor(); // DT_CSPlayer -> m_bHasHeavyArmor
					ArmorValue = ((C_BaseEntity*)data.enterTrace.hit_entity)->GetArmor(); // DT_CSPlayer -> m_ArmorValue

					iHitGroup = data.enterTrace.hitgroup;
					isArmored = IsArmored(data.enterTrace.hit_entity, ArmorValue, iHitGroup);
				}

				switch (iHitGroup) //scaledamage
				{
				case HitGroups::HITGROUP_HEAD:
					if (HeavyArmor)//If the enemy is using Heavy Armor, headshots will do half damage.
						data.currentDamage *= 4.f * 0.5f;
					else
						data.currentDamage *= 4.f;
					break;
				case HitGroups::HITGROUP_STOMACH:
					data.currentDamage *= 1.25f;
					break;
				case HitGroups::HITGROUP_LEFTLEG:
				case HitGroups::HITGROUP_RIGHTLEG:
					data.currentDamage *= 0.75f;
					break;
				}

				if (isArmored)
				{
					float flBonusValue = 1.f, flArmorBonusRatio = 0.5f, flArmorRatio = weaponData->armor_ratio * 0.5f;

					if (HeavyArmor)
					{
						flArmorBonusRatio = 0.33f;
						flArmorRatio = (weaponData->armor_ratio * 0.5f) * 0.5f;
						flBonusValue = 0.33f;
					}

					auto NewDamage = data.currentDamage * flArmorRatio;

					if (HeavyArmor)
						NewDamage *= 0.85f;

					if (((data.currentDamage - (data.currentDamage * flArmorRatio)) * (flBonusValue * flArmorBonusRatio)) > ArmorValue)
						NewDamage = data.currentDamage - (ArmorValue / flArmorBonusRatio);

					//Thanks esoterik <c>
					if (NewDamage > 115)
						NewDamage = 115;

					data.currentDamage = NewDamage;

				}
				return true;
			}

			if ((data.traceLength > 3000.f) || (enterSurfPenetrationModifier < 0.1f) || !HandleBulletPenetration(weaponData, data))
				break;
			if (runOnce)
				return true;
		}
	}
	return false;
}


float CAutowall::CanHit(Vector &vecEyePos, Vector &point)
{
	C_BaseEntity* g_LocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	FireBulletData data;
	data.src = vecEyePos;
	data.filter.pSkip = g_LocalPlayer;

	Vector angles;
	Vector tmp = point - data.src;

	Math::VectorAngles(tmp, angles);
	Math::AngleVectors(angles, &data.direction);
	data.direction.NormalizeInPlace();

	if (SimulateFireBullet(g_LocalPlayer->GetWeapon(), data, false))
		return data.currentDamage;
	return -1;
}

float CAutowall::EnemyCanHit(C_BaseEntity * enemy, Vector &vecEyePos, Vector &point)
{
	FireBulletData data;
	data.src = vecEyePos;
	data.filter.pSkip = enemy;

	Vector angles;
	Vector tmp = point - data.src;

	Math::VectorAngles(tmp, angles);
	Math::AngleVectors(angles, &data.direction);
	data.direction.NormalizeInPlace();

	if (EnemySimulateFireBullet(enemy, enemy->GetWeapon(), data, false, point))
		return data.currentDamage;
	return -1;
}

float CAutowall::GetWallDamage(Vector &vecEyePos, QAngle angles)
{
	C_BaseEntity* g_LocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	FireBulletData data;
	data.src = vecEyePos;
	data.filter.pSkip = g_LocalPlayer;

	Math::AngleVectors(Vector(angles.x, angles.y, angles.z), &data.direction);
	data.direction.NormalizeInPlace();

	if (!g_LocalPlayer->GetWeapon())
		return -1;

	if (SimulateFireBullet(g_LocalPlayer->GetWeapon(), data, true))
		return data.currentDamage;

	return -1;
}
void CAutowall::GetBulletTypeParameters(float& maxRange, float& maxDistance, char* bulletType, bool sv_penetration_type)
{
	if (sv_penetration_type)
	{
		maxRange = 35.0;
		maxDistance = 3000.0;
	}
	else
	{
		//Play tribune to framerate. Thanks, stringcompare
		//Regardless I doubt anyone will use the old penetration system anyway; so it won't matter much.
		if (!strcmp(bulletType, ("BULLET_PLAYER_338MAG")))
		{
			maxRange = 45.0;
			maxDistance = 8000.0;
		}
		if (!strcmp(bulletType, ("BULLET_PLAYER_762MM")))
		{
			maxRange = 39.0;
			maxDistance = 5000.0;
		}
		if (!strcmp(bulletType, ("BULLET_PLAYER_556MM")) || !strcmp(bulletType, ("BULLET_PLAYER_556MM_SMALL")) || !strcmp(bulletType, ("BULLET_PLAYER_556MM_BOX")))
		{
			maxRange = 35.0;
			maxDistance = 4000.0;
		}
		if (!strcmp(bulletType, ("BULLET_PLAYER_57MM")))
		{
			maxRange = 30.0;
			maxDistance = 2000.0;
		}
		if (!strcmp(bulletType, ("BULLET_PLAYER_50AE")))
		{
			maxRange = 30.0;
			maxDistance = 1000.0;
		}
		if (!strcmp(bulletType, ("BULLET_PLAYER_357SIG")) || !strcmp(bulletType, ("BULLET_PLAYER_357SIG_SMALL")) || !strcmp(bulletType, ("BULLET_PLAYER_357SIG_P250")) || !strcmp(bulletType, ("BULLET_PLAYER_357SIG_MIN")))
		{
			maxRange = 25.0;
			maxDistance = 800.0;
		}
		if (!strcmp(bulletType, ("BULLET_PLAYER_9MM")))
		{
			maxRange = 21.0;
			maxDistance = 800.0;
		}
		if (!strcmp(bulletType, ("BULLET_PLAYER_45ACP")))
		{
			maxRange = 15.0;
			maxDistance = 500.0;
		}
		if (!strcmp(bulletType, ("BULLET_PLAYER_BUCKSHOT")))
		{
			maxRange = 0.0;
			maxDistance = 0.0;
		}
	}
}

bool CAutowall::FireBullet(CBaseCombatWeapon* pWeapon, Vector& direction, float& currentDamage)
{
	if (!pWeapon)
		return false;

	C_BaseEntity* g_LocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	FireBulletData data;
	data.filter = CTraceFilter();
	data.filter.pSkip = g_LocalPlayer;

	bool sv_penetration_type;
	//	  Current bullet travel Power to penetrate Distance to penetrate Range               Player bullet reduction convars			  Amount to extend ray by
	float currentDistance = 0.f, penetrationPower, penetrationDistance, maxRange, ff_damage_reduction_bullets, ff_damage_bullet_penetration, rayExtension = 40.f;
	Vector eyePosition = g_LocalPlayer->GetEyePosition();

	//For being superiour when the server owners think your autowall isn't well reversed. Imagine a meme HvH server with the old penetration system- pff
	static ConVar* penetrationSystem = G_Cvar->FindVar(("sv_penetration_type"));
	static ConVar* damageReductionBullets = G_Cvar->FindVar(("ff_damage_reduction_bullets"));
	static ConVar* damageBulletPenetration = G_Cvar->FindVar(("ff_damage_bullet_penetration"));

	sv_penetration_type = penetrationSystem->GetBool();
	ff_damage_reduction_bullets = damageReductionBullets->GetFloat();
	ff_damage_bullet_penetration = damageBulletPenetration->GetFloat();

	CSWeaponInfo* weaponData = pWeapon->GetCSWeaponData();
	trace_t enterTrace;

	//We should be skipping localplayer when casting a ray to players.
	CTraceFilter filter;
	filter.pSkip = g_LocalPlayer;

	if (!weaponData)
		return false;

	maxRange = weaponData->range;

	GetBulletTypeParameters(penetrationPower, penetrationDistance, weaponData->hud_name, sv_penetration_type);

	if (sv_penetration_type)
		penetrationPower = weaponData->penetration;

	//This gets set in FX_Firebullets to 4 as a pass-through value.
	//CS:GO has a maximum of 4 surfaces a bullet can pass-through before it 100% stops.
	//Excerpt from Valve: https://steamcommunity.com/sharedfiles/filedetails/?id=275573090
	//"The total number of surfaces any bullet can penetrate in a single flight is capped at 4." -CS:GO Official
	int possibleHitsRemaining = 4;

	//Set our current damage to what our gun's initial damage reports it will do
	currentDamage = static_cast<float>(weaponData->damage);

	//If our damage is greater than (or equal to) 1, and we can shoot, let's shoot.
	while (possibleHitsRemaining > 0 && currentDamage >= 1.f)
	{
		//Calculate max bullet range
		maxRange -= currentDistance;

		//Create endpoint of bullet
		Vector end = eyePosition + direction * maxRange;

		TraceLine(eyePosition, end, MASK_SHOT_HULL | CONTENTS_HITBOX, g_LocalPlayer, &enterTrace);
		ClipTraceToPlayers(eyePosition, end + direction * rayExtension, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &enterTrace);

		//We have to do this *after* tracing to the player.
		surfacedata_t *enterSurfaceData = G_PhysicProps->GetSurfaceData(enterTrace.surface.surfaceProps);
		float enterSurfPenetrationModifier = enterSurfaceData->game.flPenetrationModifier;
		int enterMaterial = enterSurfaceData->game.material;

		//"Fraction == 1" means that we didn't hit anything. We don't want that- so let's break on it.
		if (enterTrace.fraction == 1.f)
			break;

		//calculate the damage based on the distance the bullet traveled.
		currentDistance += enterTrace.fraction * maxRange;

		//Let's make our damage drops off the further away the bullet is.
		currentDamage *= pow(weaponData->range_modifier, (currentDistance / 500.f));

		//Sanity checking / Can we actually shoot through?
		if (currentDistance > penetrationDistance && weaponData->penetration > 0.f || enterSurfPenetrationModifier < 0.1f)
			break;

		//This looks gay as fuck if we put it into 1 long line of code.
		bool canDoDamage = (enterTrace.hitgroup != HitGroups::HITGROUP_GEAR && enterTrace.hitgroup != HitGroups::HITGROUP_GENERIC);
		//	bool isPlayer = enterTrace.m_pEnt->GetClientClass()->m_ClassID == CSClasses::CCSPlayer);
		bool isEnemy = (((C_BaseEntity*)g_LocalPlayer)->GetTeamNum() != ((C_BaseEntity*)enterTrace.hit_entity)->GetTeamNum());
		//	bool onTeam = (((CBaseEntity*)enterTrace.m_pEnt)->GetTeamNum() == (int32_t)TEAM_CT || ((CBaseEntity*)enterTrace.m_pEnt)->GetTeamNum() == (int32_t)TeamNumbers::TEAM_T);

		//TODO: Team check config
		if ((canDoDamage &&  isEnemy))
		{
			ScaleDamage2(enterTrace, weaponData, currentDamage);
			return true;
		}

		//Calling HandleBulletPenetration here reduces our penetrationCounter, and if it returns true, we can't shoot through it.
		if (!HandleBulletPenetration2(weaponData, enterTrace, eyePosition, direction, possibleHitsRemaining, currentDamage, penetrationPower, sv_penetration_type, ff_damage_reduction_bullets, ff_damage_bullet_penetration))
			break;
	}
	return false;
}

bool CAutowall::EnemyFireBullet(C_BaseEntity * enemy,CBaseCombatWeapon* pWeapon, Vector& direction, float& currentDamage)
{
	if (!pWeapon)
		return false;

	C_BaseEntity* g_LocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	FireBulletData data;
	data.filter = CTraceFilter();
	data.filter.pSkip = enemy;
	C_BaseEntity* pLocalEntity = (C_BaseEntity*)enemy;
	bool sv_penetration_type;
	//	  Current bullet travel Power to penetrate Distance to penetrate Range               Player bullet reduction convars			  Amount to extend ray by
	float currentDistance = 0.f, penetrationPower, penetrationDistance, maxRange, ff_damage_reduction_bullets, ff_damage_bullet_penetration, rayExtension = 40.f;
	Vector eyePosition = pLocalEntity->GetEyePosition();

	//For being superiour when the server owners think your autowall isn't well reversed. Imagine a meme HvH server with the old penetration system- pff
	static ConVar* penetrationSystem = G_Cvar->FindVar(("sv_penetration_type"));
	static ConVar* damageReductionBullets = G_Cvar->FindVar(("ff_damage_reduction_bullets"));
	static ConVar* damageBulletPenetration = G_Cvar->FindVar(("ff_damage_bullet_penetration"));

	sv_penetration_type = penetrationSystem->GetBool();
	ff_damage_reduction_bullets = damageReductionBullets->GetFloat();
	ff_damage_bullet_penetration = damageBulletPenetration->GetFloat();

	CSWeaponInfo* weaponData = pWeapon->GetCSWeaponData();
	trace_t enterTrace;

	//We should be skipping localplayer when casting a ray to players.
	CTraceFilter filter;


	if (!weaponData)
		return false;

	maxRange = weaponData->range;

	GetBulletTypeParameters(penetrationPower, penetrationDistance, weaponData->hud_name, sv_penetration_type);

	if (sv_penetration_type)
		penetrationPower = weaponData->penetration;

	//This gets set in FX_Firebullets to 4 as a pass-through value.
	//CS:GO has a maximum of 4 surfaces a bullet can pass-through before it 100% stops.
	//Excerpt from Valve: https://steamcommunity.com/sharedfiles/filedetails/?id=275573090
	//"The total number of surfaces any bullet can penetrate in a single flight is capped at 4." -CS:GO Official
	int possibleHitsRemaining = 4;

	//Set our current damage to what our gun's initial damage reports it will do
	currentDamage = static_cast<float>(weaponData->damage);

	//If our damage is greater than (or equal to) 1, and we can shoot, let's shoot.
	while (possibleHitsRemaining > 0 && currentDamage >= 1.f)
	{
		//Calculate max bullet range
		maxRange -= currentDistance;

		//Create endpoint of bullet
		Vector end = eyePosition + direction * maxRange;

		TraceLine(eyePosition, end, MASK_SHOT_HULL | CONTENTS_HITBOX, pLocalEntity, &enterTrace);
		ClipTraceToPlayers(eyePosition, end + direction * rayExtension, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &enterTrace);

		//We have to do this *after* tracing to the player.
		surfacedata_t *enterSurfaceData = G_PhysicProps->GetSurfaceData(enterTrace.surface.surfaceProps);
		float enterSurfPenetrationModifier = enterSurfaceData->game.flPenetrationModifier;
		int enterMaterial = enterSurfaceData->game.material;

		//"Fraction == 1" means that we didn't hit anything. We don't want that- so let's break on it.
		if (enterTrace.fraction == 1.f)
			break;

		//calculate the damage based on the distance the bullet traveled.
		currentDistance += enterTrace.fraction * maxRange;

		//Let's make our damage drops off the further away the bullet is.
		currentDamage *= pow(weaponData->range_modifier, (currentDistance / 500.f));

		//Sanity checking / Can we actually shoot through?
		if (currentDistance > penetrationDistance && weaponData->penetration > 0.f || enterSurfPenetrationModifier < 0.1f)
			break;

		//This looks gay as fuck if we put it into 1 long line of code.
		bool canDoDamage = (enterTrace.hitgroup != HitGroups::HITGROUP_GEAR && enterTrace.hitgroup != HitGroups::HITGROUP_GENERIC);
		//	bool isPlayer = enterTrace.m_pEnt->GetClientClass()->m_ClassID == CSClasses::CCSPlayer);
		bool isEnemy = (((C_BaseEntity*)pLocalEntity)->GetTeamNum() != ((C_BaseEntity*)enterTrace.hit_entity)->GetTeamNum());
		//	bool onTeam = (((CBaseEntity*)enterTrace.m_pEnt)->GetTeamNum() == (int32_t)TEAM_CT || ((CBaseEntity*)enterTrace.m_pEnt)->GetTeamNum() == (int32_t)TeamNumbers::TEAM_T);

		//TODO: Team check config
		if ((canDoDamage &&  isEnemy))
		{
			ScaleDamage2(enterTrace, weaponData, currentDamage);
			return true;
		}

		//Calling HandleBulletPenetration here reduces our penetrationCounter, and if it returns true, we can't shoot through it.
		if (!HandleBulletPenetration2(weaponData, enterTrace, eyePosition, direction, possibleHitsRemaining, currentDamage, penetrationPower, sv_penetration_type, ff_damage_reduction_bullets, ff_damage_bullet_penetration))
			break;
	}
	return false;
}

void CAutowall::ScaleDamage2(trace_t &enterTrace, CSWeaponInfo *weaponData, float& currentDamage)
{
	//Cred. to N0xius for reversing this.
	//TODO: _xAE^; look into reversing this yourself sometime

	bool hasHeavyArmor = false;
	int armorValue = ((C_BaseEntity*)enterTrace.hit_entity)->GetArmor();
	HitGroups hitGroup = enterTrace.hitgroup;

	//Fuck making a new function, lambda beste. ~ Does the person have armor on for the hitbox checked?
	auto IsArmored = [&enterTrace]()->bool
	{
		C_BaseEntity* targetEntity = (C_BaseEntity*)enterTrace.hit_entity;
		switch (enterTrace.hitgroup)
		{
		case HitGroups::HITGROUP_HEAD:
			return !!(C_BaseEntity*)targetEntity->HasHelmet(); //Fuck compiler errors - force-convert it to a bool via (!!)
		case HitGroups::HITGROUP_GENERIC:
		case HitGroups::HITGROUP_CHEST:
		case HitGroups::HITGROUP_STOMACH:
		case HitGroups::HITGROUP_LEFTARM:
		case HitGroups::HITGROUP_RIGHTARM:
			return true;
		default:
			return false;
		}
	};

	switch (hitGroup)
	{
	case HitGroups::HITGROUP_HEAD:
		currentDamage *= 4.f; //Heavy Armor does 1/2 damage
		break;
	case HitGroups::HITGROUP_STOMACH:
		currentDamage *= 1.25f;
		break;
	case HitGroups::HITGROUP_LEFTLEG:
	case HitGroups::HITGROUP_RIGHTLEG:
		currentDamage *= 0.75f;
		break;
	default:
		break;
	}

	if (armorValue > 0 && IsArmored())
	{
		float bonusValue = 1.f, armorBonusRatio = 0.5f, armorRatio = weaponData->armor_ratio / 2.f;

		//Damage gets modified for heavy armor users
		if (hasHeavyArmor)
		{
			armorBonusRatio = 0.33f;
			armorRatio *= 0.5f;
			bonusValue = 0.33f;
		}

		auto NewDamage = currentDamage * armorRatio;

		if (hasHeavyArmor)
			NewDamage *= 0.85f;

		if (((currentDamage - (currentDamage * armorRatio)) * (bonusValue * armorBonusRatio)) > armorValue)
			NewDamage = currentDamage - (armorValue / armorBonusRatio);

		currentDamage = NewDamage;
	}
}

bool CAutowall::TraceToExit2(trace_t& enterTrace, trace_t& exitTrace, Vector startPosition, Vector direction)
{
	/*
	Masks used:
	MASK_SHOT_HULL					 = 0x600400B
	CONTENTS_HITBOX					 = 0x40000000
	MASK_SHOT_HULL | CONTENTS_HITBOX = 0x4600400B
	*/

	Vector start, end;
	float maxDistance = 90.f, rayExtension = 4.f, currentDistance = 0;
	int firstContents = 0;

	while (currentDistance <= maxDistance)
	{
		//Add extra distance to our ray
		currentDistance += rayExtension;

		//Multiply the direction vector to the distance so we go outwards, add our position to it.
		start = startPosition + direction * currentDistance;

		if (!firstContents)
			firstContents = G_EngineTrace->GetPointContents(start, MASK_SHOT_HULL | CONTENTS_HITBOX, nullptr); /*0x4600400B*/
		int pointContents = G_EngineTrace->GetPointContents(start, MASK_SHOT_HULL | CONTENTS_HITBOX, nullptr);

		if (!(pointContents & MASK_SHOT_HULL) || pointContents & CONTENTS_HITBOX && pointContents != firstContents) /*0x600400B, *0x40000000*/
		{
			//Let's setup our end position by deducting the direction by the extra added distance
			end = start - (direction * rayExtension);

			//Let's cast a ray from our start pos to the end pos
			TraceLine(start, end, MASK_SHOT_HULL | CONTENTS_HITBOX, nullptr, &exitTrace);

			//Let's check if a hitbox is in-front of our enemy and if they are behind of a solid wall
			if (exitTrace.startsolid && exitTrace.surface.flags & SURF_HITBOX)
			{
				TraceLine(start, startPosition, MASK_SHOT_HULL, exitTrace.hit_entity, &exitTrace);

				if (exitTrace.DidHit() && !exitTrace.startsolid)
				{
					start = exitTrace.endpos;
					return true;
				}

				continue;
			}

			//Can we hit? Is the wall solid?
			if (exitTrace.DidHit() && !exitTrace.startsolid)
			{

				//Is the wall a breakable? If so, let's shoot through it.
				if (IsBreakableEntity(enterTrace.hit_entity) && IsBreakableEntity(exitTrace.hit_entity))
					return true;

				if (enterTrace.surface.flags & SURF_NODRAW || !(exitTrace.surface.flags & SURF_NODRAW) && (exitTrace.plane.normal.Dot(direction) <= 1.f))
				{
					float multAmount = exitTrace.fraction * 4.f;
					start -= direction * multAmount;
					return true;
				}

				continue;
			}

			if (!exitTrace.DidHit() || exitTrace.startsolid)
			{
				if (enterTrace.DidHit() && IsBreakableEntity(enterTrace.hit_entity))
				{
					exitTrace = enterTrace;
					exitTrace.endpos = start + direction;
					return true;
				}

				continue;
			}
		}
	}
	return false;
}

bool CAutowall::HandleBulletPenetration2(CSWeaponInfo* weaponData, trace_t& enterTrace, Vector& eyePosition, Vector direction, int& possibleHitsRemaining, float& currentDamage, float penetrationPower, bool sv_penetration_type, float ff_damage_reduction_bullets, float ff_damage_bullet_penetration)
{
	//Because there's been issues regarding this- putting this here.
	if (&currentDamage == nullptr)
		throw std::invalid_argument("currentDamage is null!");
	C_BaseEntity* g_LocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	FireBulletData data;
	data.filter = CTraceFilter();
	data.filter.pSkip = g_LocalPlayer;
	trace_t exitTrace;
	C_BaseEntity* pEnemy = (C_BaseEntity*)enterTrace.hit_entity;
	surfacedata_t *enterSurfaceData = G_PhysicProps->GetSurfaceData(enterTrace.surface.surfaceProps);
	int enterMaterial = enterSurfaceData->game.material;

	float enterSurfPenetrationModifier = enterSurfaceData->game.flPenetrationModifier;
	float enterDamageModifier = enterSurfaceData->game.flDamageModifier;
	float thickness, modifier, lostDamage, finalDamageModifier, combinedPenetrationModifier;
	bool isSolidSurf = ((enterTrace.contents >> 3) & CONTENTS_SOLID);
	bool isLightSurf = ((enterTrace.surface.flags >> 7) & SURF_LIGHT);

	if (possibleHitsRemaining <= 0
		//Test for "DE_CACHE/DE_CACHE_TELA_03" as the entering surface and "CS_ITALY/CR_MISCWOOD2B" as the exiting surface.
		//Fixes a wall in de_cache which seems to be broken in some way. Although bullet penetration is not recorded to go through this wall
		//Decals can be seen of bullets within the glass behind of the enemy. Hacky method, but works.
		//You might want to have a check for this to only be activated on de_cache.
		|| (enterTrace.surface.name == (const char*)0x2227c261 && exitTrace.surface.name == (const char*)0x2227c868)
		|| (!possibleHitsRemaining && !isLightSurf && !isSolidSurf && enterMaterial != CHAR_TEX_GRATE && enterMaterial != CHAR_TEX_GLASS)
		|| weaponData->penetration <= 0.f
		|| !TraceToExit2(enterTrace, exitTrace, enterTrace.endpos, direction)
		&& !(G_EngineTrace->GetPointContents(enterTrace.endpos, MASK_SHOT_HULL, nullptr) & MASK_SHOT_HULL))
		return false;

	surfacedata_t *exitSurfaceData = G_PhysicProps->GetSurfaceData(exitTrace.surface.surfaceProps);
	int exitMaterial = exitSurfaceData->game.material;
	float exitSurfPenetrationModifier = exitSurfaceData->game.flPenetrationModifier;
	float exitDamageModifier = exitSurfaceData->game.flDamageModifier;

	//Are we using the newer penetration system?
	if (sv_penetration_type)
	{
		if (enterMaterial == CHAR_TEX_GRATE || enterMaterial == CHAR_TEX_GLASS)
		{
			combinedPenetrationModifier = 3.f;
			finalDamageModifier = 0.05f;
		}
		else if (isSolidSurf || isLightSurf)
		{
			combinedPenetrationModifier = 1.f;
			finalDamageModifier = 0.16f;
		}
		else if (enterMaterial == CHAR_TEX_FLESH && (g_LocalPlayer->GetTeamNum() == pEnemy->GetTeamNum() && ff_damage_reduction_bullets == 0.f)) //TODO: Team check config
		{
			//Look's like you aren't shooting through your teammate today
			if (ff_damage_bullet_penetration == 0.f)
				return false;

			//Let's shoot through teammates and get kicked for teamdmg! Whatever, atleast we did damage to the enemy. I call that a win.
			combinedPenetrationModifier = ff_damage_bullet_penetration;
			finalDamageModifier = 0.16f;
		}
		else
		{
			combinedPenetrationModifier = (enterSurfPenetrationModifier + exitSurfPenetrationModifier) / 2.f;
			finalDamageModifier = 0.16f;
		}

		//Do our materials line up?
		if (enterMaterial == exitMaterial)
		{
			if (exitMaterial == CHAR_TEX_CARDBOARD || exitMaterial == CHAR_TEX_WOOD)
				combinedPenetrationModifier = 3.f;
			else if (exitMaterial == CHAR_TEX_PLASTIC)
				combinedPenetrationModifier = 2.f;
		}

		//Calculate thickness of the wall by getting the length of the range of the trace and squaring
		thickness = (exitTrace.endpos - enterTrace.endpos).LengthSqr();
		modifier = fmaxf(1.f / combinedPenetrationModifier, 0.f);

		//This calculates how much damage we've lost depending on thickness of the wall, our penetration, damage, and the modifiers set earlier
		lostDamage = fmaxf(
			((modifier * thickness) / 24.f)
			+ ((currentDamage * finalDamageModifier)
				+ (fmaxf(3.75f / penetrationPower, 0.f) * 3.f * modifier)), 0.f);

		//Did we loose too much damage?
		if (lostDamage > currentDamage)
			return false;

		//We can't use any of the damage that we've lost
		if (lostDamage > 0.f)
			currentDamage -= lostDamage;

		//Do we still have enough damage to deal?
		if (currentDamage < 1.f)
			return false;

		eyePosition = exitTrace.endpos;
		--possibleHitsRemaining;

		return true;
	}
	else //Legacy penetration system
	{
		combinedPenetrationModifier = 1.f;

		if (isSolidSurf || isLightSurf)
			finalDamageModifier = 0.99f; //Good meme :^)
		else
		{
			finalDamageModifier = fminf(enterDamageModifier, exitDamageModifier);
			combinedPenetrationModifier = fminf(enterSurfPenetrationModifier, exitSurfPenetrationModifier);
		}

		if (enterMaterial == exitMaterial && (exitMaterial == CHAR_TEX_METAL || exitMaterial == CHAR_TEX_WOOD))
			combinedPenetrationModifier += combinedPenetrationModifier;

		thickness = (exitTrace.endpos - enterTrace.endpos).LengthSqr();

		if (sqrt(thickness) <= combinedPenetrationModifier * penetrationPower)
		{
			currentDamage *= finalDamageModifier;
			eyePosition = exitTrace.endpos;
			--possibleHitsRemaining;

			return true;
		}

		return false;
	}
}


float CAutowall::CanHit2(Vector &vecEyePos, Vector &point)
{
	C_BaseEntity* g_LocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	FireBulletData data;
	data.src = vecEyePos;
	data.filter.pSkip = g_LocalPlayer;

	Vector angles;
	Vector tmp = point - data.src;

	Math::VectorAngles(tmp, angles);
	Math::AngleVectors(angles, &data.direction);
	data.direction.NormalizeInPlace();

	if (FireBullet(g_LocalPlayer->GetWeapon(), data.direction, data.currentDamage))
		return data.currentDamage;
	return -1; //That wall is just a bit too thick buddy
}

bool CAutowall::PenetrateWall(C_BaseEntity* pBaseEntity, Vector& vecPoint, Vector& vecPoint2)
{
	float min_damage = 20.f;
	if (pBaseEntity->GetHealth() < min_damage)
		min_damage = static_cast<float>(pBaseEntity->GetHealth());

	if (CanHit2(vecPoint, vecPoint2) >= min_damage)
		return true;

	return false;
}


float CAutowall::enemycanhit2(C_BaseEntity * enemy, Vector &vecEyePos, Vector &point)
{
	C_BaseEntity* local = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	FireBulletData data;
	data.src = vecEyePos;
	data.filter.pSkip = enemy;
	Vector angles;
	Vector tmp = point - data.src;

	Math::VectorAngles(tmp, angles);
	Math::AngleVectors(angles, &data.direction);
	data.direction.NormalizeInPlace();

	if (EnemyFireBullet(enemy, enemy->GetWeapon(), data.direction,data.currentDamage))
		return data.currentDamage;
	return -1;
}