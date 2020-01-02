#include "Main.h"



struct FireBulletData
{




	Vector          src;
	CGameTrace      enterTrace;
	Vector          direction;
	CTraceFilter    filter;
	float           traceLength;
	float           traceLengthRemaining;
	float           currentDamage;
	int             penetrateCount;
};



class CAutowall
{
public:

	bool DidHitNonWorldEntity(C_BaseEntity* m_pEnt);
	bool IsWorldEntity(C_BaseEntity* m_pEnt);
	bool isBreakableEntity(C_BaseEntity* pEntity);
	void TraceLine(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, C_BaseEntity* ignore, CGameTrace* ptr);
	bool IsArmored(C_BaseEntity* Entity, int ArmorValue, HitGroups Hitgroup);
	bool TraceToExit(CGameTrace* enterTrace, Vector vecStartPosition, Vector vecDir, CGameTrace* exitTrace);
	bool HandleBulletPenetration(CSWeaponInfo* wpn_data, FireBulletData& data);
	//bool HandleBulletPenetration(CCSWeaponInfo* weaponData, FireBulletData& data, CGameTrace* enterTrace, Vector vecStartPosition, Vector vecDir, CGameTrace* exitTrace, surfacedata_t* enterSurfaceData);
	bool SimulateFireBullet(CBaseCombatWeapon* pWeapon, FireBulletData& data, bool runOnce);
	bool EnemySimulateFireBullet(C_BaseEntity* enemy, CBaseCombatWeapon* pWeapon, FireBulletData& data, bool runOnce, Vector stop);
	float CanHit(Vector& vecEyePos, Vector& point);
	float EnemyCanHit(C_BaseEntity* enemy, Vector& vecEyePos, Vector& point);
	float GetWallDamage(Vector& vecEyePos, QAngle angles);
	void GetBulletTypeParameters(float & maxRange, float & maxDistance, char * bulletType, bool sv_penetration_type);
	bool FireBullet(CBaseCombatWeapon* pWeapon, Vector& direction, float& currentDamage);
	bool EnemyFireBullet(C_BaseEntity * enemy, CBaseCombatWeapon* pWeapon, Vector& direction, float& currentDamage);
	void ScaleDamage2(trace_t & enterTrace, CSWeaponInfo * weaponData, float & currentDamage);
	bool TraceToExit2(trace_t & enterTrace, trace_t & exitTrace, Vector startPosition, Vector direction);
	bool HandleBulletPenetration2(CSWeaponInfo * weaponData, trace_t & enterTrace, Vector & eyePosition, Vector direction, int & possibleHitsRemaining, float & currentDamage, float penetrationPower, bool sv_penetration_type, float ff_damage_reduction_bullets, float ff_damage_bullet_penetration);
	float CanHit2(Vector &vecEyePos, Vector &point);
	bool PenetrateWall(C_BaseEntity * pBaseEntity, Vector & vecPoint, Vector & vecPoint2);
	float enemycanhit2(C_BaseEntity * enemy, Vector & vecEyePos, Vector & point);
	void ClipTraceToPlayers(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, CGameTrace* tr);
}; extern CAutowall* G_Autowall;

