#pragma once
#include "Main.h"


CBaseCombatWeapon* C_BaseEntity::GetWeapon()
{
	ULONG WeaponUlong = *(PULONG)((DWORD)this + G_sets.m_hActiveWeapon); // hActiveWeapon
	return (CBaseCombatWeapon*)(G_EntList->GetClientEntityFromHandle(WeaponUlong));
}

DWORD GetCSWpnDataAddr;

bool C_BaseEntity::IsEnemy()
{
	return this->GetTeamNum() != (reinterpret_cast< C_BaseEntity* >(G_EntList->GetClientEntity(G_Engine->GetLocalPlayer())))->GetTeamNum();
}

void C_BaseEntity::CopyPoseParameters(float* dest)
{
	float* flPose = (float*)((DWORD)this + 0x2764);
	memcpy(dest, flPose, sizeof(float) * 24);

}

bool C_BaseEntity::ComputeHitboxSurroundingBox(Vector *pVecWorldMins, Vector *pVecWorldMaxs)
{
	typedef bool(__thiscall* SComputeHitboxSurroundingBox)(void*, Vector *, Vector *);
	static auto oComputeHitboxSurroundingBox = (SComputeHitboxSurroundingBox)(G_sets.dwComputeHitboxSurroundingBox);

	return oComputeHitboxSurroundingBox(this, pVecWorldMins, pVecWorldMaxs);
}

#pragma warning(disable:4244)
#pragma warning(disable:4056)
void C_BaseEntity::InvalidateBoneCache()
{
	static auto m_nForceBone = g_pNetVars->GetOffset("DT_BaseAnimating", "m_nForceBone");

	static DWORD InvalidateBoneCache = FindPattern(client_dll, (PBYTE)"\x80\x3D\x00\x00\x00\x00\x00\x74\x16\xA1", "xx????xxxx");
	static unsigned long g_iModelBoneCounter = (unsigned long)(InvalidateBoneCache + 10);
	*(int*)((DWORD)this + m_nForceBone + 0x20) = 0;
	
	*(unsigned int*)((DWORD)this + 0x2914) = -FLT_MAX; // bro what
	*(unsigned int*)((DWORD)this + 0x2680) = (g_iModelBoneCounter - 1);
}
void C_BaseEntity::SetCurrentCommand(CUserCmd *cmd)
{
	static int offset = g_pNetVars->GetOffset("DT_BasePlayer", "m_hConstraintEntity");
	*Member<CUserCmd**>(this, (offset - 0xC)) = cmd;
}


std::array<float, 24> &C_BaseEntity::m_flPoseParameter()
{
	static int _m_flPoseParameter = g_pNetVars->GetOffset("CBaseAnimating", "m_flPoseParameter");
	return *(std::array<float, 24>*)((uintptr_t)this + _m_flPoseParameter);
}

bool C_BaseEntity::IsValidRenderable() {
	C_BaseEntity* pLocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	if (!this || this == nullptr || pLocalPlayer == nullptr)
		return false;

	if (this == pLocalPlayer)
		return false;

	if (this->GetTeamNum() == pLocalPlayer->GetTeamNum())
		return false;

	if (this->IsDormant())
		return false;

	if (!this->isAlive())
		return false;

	return true;
}
void C_BaseEntity::UpdateClientSideAnimation()
{
	g_Utils->get_vfunc<void(__thiscall*)(void*)>(this, 218)(this);
}
void C_BaseEntity::SetAbsOrigin(const Vector &origin)
{
	using SetAbsOriginFn = void(__thiscall*)(void*, const Vector &origin);
	static SetAbsOriginFn SetAbsOrigin = (SetAbsOriginFn)g_Utils->FindPatternIDA(client_dll, "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8");
	SetAbsOrigin(this, origin);
}

bool C_BaseEntity::IsValidTarget() {
	C_BaseEntity* pLocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	if (!this || this == nullptr)
		return false;

	ClientClass* pClass = (ClientClass*)this->GetClientClass(); // Needed to check clientclass after nullptr check that was causing a crash

	if (this == pLocalPlayer)
		return false;

	if (pClass->m_ClassID != 35)
		return false;

	if (this->GetTeamNum() == pLocalPlayer->GetTeamNum())
		return false;

	if (this->IsDormant())
		return false;

	if (!this->isAlive())
		return false;

	if (this->IsProtected())
		return false;

	return true;
}

void C_BaseEntity::SetAngle2(Vector wantedang)
{
	typedef void(__thiscall* SetAngleFn)(void*, const Vector &);
	static SetAngleFn SetAngle = (SetAngleFn)((DWORD)g_Utils->FindPatternIDA(client_dll, "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1"));
	SetAngle(this, wantedang);
}

bool C_BaseEntity::SetupBones2(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	static DWORD m_nWritableBones = g_pNetVars->GetOffset("DT_BaseAnimating", "m_nForceBone");
	static DWORD m_dwOcclusionArray = *(uintptr_t*)(FindPattern(client_dll, (PBYTE) "\xA1\x00\x00\x00\x00\x8B\xB7\x00\x00\x00\x00\x89\x75\xF8", "x????xx????xxx") + 0x1); //"A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8"
	static DWORD m_bDidCheckForOcclusion = *(uintptr_t*)(FindPattern(client_dll, (PBYTE) "\xA1\x00\x00\x00\x00\x8B\xB7\x00\x00\x00\x00\x89\x75\xF8", "x????xx????xxx") + 0x7); //"A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8"

	*(int*)((uintptr_t)this + m_nWritableBones) = 0;
	*(int*)((uintptr_t)this + m_bDidCheckForOcclusion) = reinterpret_cast< int* >(m_dwOcclusionArray)[1];

	__asm
	{
		mov edi, this
		lea ecx, dword ptr ds : [edi + 0x4]
		mov edx, dword ptr ds : [ecx]
		push currentTime
		push boneMask
		push nMaxBones
		push pBoneToWorldOut
		call dword ptr ds : [edx + 0x34]
	}

	//typedef bool(__thiscall* oSetupBones)(PVOID, matrix3x4*, int, int, float);
	//return getvfunc< oSetupBones>(this, 13)(this, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
}

bool C_BaseEntity::SetupBones(VMatrix *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	//void *pRenderable = (void*)(this + 0x4);
	//typedef bool(__thiscall* OriginalFn)(PVOID, VMatrix*, int, int, float);
	//return CallVFunction<OriginalFn>(pRenderable, 13)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);

	__asm
	{
		mov edi, this
		lea ecx, dword ptr ds : [edi + 0x4]
		mov edx, dword ptr ds : [ecx]
		push currentTime
		push boneMask
		push nMaxBones
		push pBoneToWorldOut
		call dword ptr ds : [edx + 0x34]
	}
}


Vector C_BaseEntity::GetBonePos(int i)
{
	VMatrix boneMatrix[128];
	if (this->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, G_Globals->curtime))
	{
		return Vector(boneMatrix[i][0][3], boneMatrix[i][1][3], boneMatrix[i][2][3]);
	}
	return Vector(0, 0, 0);
}



Vector C_BaseEntity::GetBonePos(int i, matrix3x4_t* matrix)
{
	return Vector(matrix[i][0][3], matrix[i][1][3], matrix[i][2][3]);
}

Vector C_BaseEntity::GetHedPos()
{
	return this->GetBonePos(6);

}

CSWeaponInfo* CBaseCombatWeapon::GetCSWeaponData()
{
	return g_Utils->get_vfunc<CSWeaponInfo*(__thiscall*)(CBaseCombatWeapon*)>(this, 444)(this);
}
bool C_BaseEntity::Sanity_Checks(C_BaseEntity* Entity)
{


	C_BaseEntity* local = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	if (!Entity
		|| Entity == local
		|| Entity->IsDormant()
		|| !Entity->isAlive()
		|| Entity->IsProtected()
		|| !Entity->IsPlayer()
		|| Entity->GetTeamNum() == local->GetTeamNum())
		return false;

	return true;
}

#define TIME_TO_TICKS( dt )	( ( int )( 0.5f + ( float )( dt ) / G_Globals->intervalPerTick ) )
int C_BaseEntity::GetChockedPackets()
{
	if (GetSimulationTime() > GetOldSimulationTime())
		return TIME_TO_TICKS(fabs(GetSimulationTime() - GetOldSimulationTime()));
	return 0;
}
Vector& C_BaseEntity::m_vecNetworkOrigin()
{

	static int offset = g_pNetVars->GetOffset("DT_CSPlayer", "m_flFriction") - sizeof(Vector);
	return *(Vector*)((DWORD)this + offset);
}

float C_BaseEntity::GetOldSimulationTime()
{

	static uintptr_t offset = g_pNetVars->GetOffset("DT_CSPlayer", "m_flSimulationTimen") + 0x4;
	return *(float*)((DWORD)this + offset);
}

bool C_BaseEntity::IsPlayer()
{
	ClientClass* pClass = (ClientClass*)this->GetClientClass();
	return pClass->m_ClassID == 35;
}

bool CBaseCombatWeapon::IsReloadingVisually() {
	static int m_bReloadVisuallyComplete = g_pNetVars->GetOffset(XorStr("DT_WeaponCSBase"), XorStr("m_bReloadVisuallyComplete"));
	return !GetFieldValue<bool>(m_bReloadVisuallyComplete);
}

AnimationLayer *C_BaseEntity::GetAnimOverlays()
{
	// to find offset: use 9/12/17 dll
	// sig: 55 8B EC 51 53 8B 5D 08 33 C0
	return *(AnimationLayer**)((DWORD)this + 0x2970);
}

AnimationLayer *C_BaseEntity::GetAnimOverlay(int i)
{
	if (i < 15)
		return &GetAnimOverlays()[i];
}
AnimationLayer& C_BaseEntity::GetAnimOverlay2(int Index)
{
	return (*(AnimationLayer**)((DWORD)this + 0x2970))[Index];
}
int C_BaseEntity::GetSequenceActivity(int sequence)
{
	auto hdr = G_ModelInfo->GetStudioModel(this->GetModel());

	if (hdr == nullptr)
		return -1;

	if (!hdr)
		return -1;

	// sig for stuidohdr_t version: 53 56 8B F1 8B DA 85 F6 74 55
	// sig for C_BaseAnimating version: 55 8B EC 83 7D 08 FF 56 8B F1 74 3D
	// c_csplayer vfunc 242, follow calls to find the function.

	static auto get_sequence_activity = reinterpret_cast<int(__fastcall*)(void*, studiohdr_t*, int)>(G_sets.getSequenceActivity);

	return get_sequence_activity(this, hdr, sequence);
}


CBasePlayerAnimState* C_BaseEntity::GetBasePlayerAnimState()
{
	static int basePlayerAnimStateOffset = 0x3884;
	return *(CBasePlayerAnimState**)((DWORD)this + basePlayerAnimStateOffset);
}

CCSPlayerAnimState *C_BaseEntity::GetPlayerAnimState()
{
	return *(CCSPlayerAnimState**)((DWORD)this + 0x3884);
}

#pragma warning(disable:4409)
void C_BaseEntity::UpdateAnimationState(CCSGOPlayerAnimState *state, QAngle angle)
{
	static auto UpdateAnimState = FindPatternIDA((client_dll), "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 F3 0F 11 54 24");
	if (!UpdateAnimState)
		return;

	__asm
	{
		mov ecx, state

		movss xmm1, dword ptr[angle + 4]
		movss xmm2, dword ptr[angle]

		call UpdateAnimState
	} // illegal instruction size
}

void C_BaseEntity::ResetAnimationState(CCSGOPlayerAnimState *state)
{
	using ResetAnimState_t = void(__thiscall*)(CCSGOPlayerAnimState*);
	static auto ResetAnimState = (ResetAnimState_t)FindPatternIDA((client_dll), "56 6A 01 68 ? ? ? ? 8B F1");
	if (!ResetAnimState)
		return;

	ResetAnimState(state);
}

void C_BaseEntity::CreateAnimationState(CCSGOPlayerAnimState *state)
{
	using CreateAnimState_t = void(__thiscall*)(CCSGOPlayerAnimState*, C_BaseEntity*);
	static auto CreateAnimState = (CreateAnimState_t)FindPatternIDA(client_dll, "55 8B EC 56 8B F1 B9 ? ? ? ? C7 46");
	if (!CreateAnimState)
		return;

	CreateAnimState(state, this);
}