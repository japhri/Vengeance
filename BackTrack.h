#pragma once
#include "Main.h"

struct tick_record
{
	Vector m_vecOrigin;//0 //4 // 8
	bool bLowerBodyYawUpdated;

	bool bFakelagging;
	float m_flSimulationTime; 
	float m_flAnimTime;
	int32_t m_nFlags;
	int m_nSequence;
	float m_flCycle; 
	Vector m_angEyeAngles;
	Vector m_absangles;
	Vector m_vecMins;
	Vector m_vecMax;			 
	float m_flUpdateTime;
	Vector m_vecVelocity;
	std::array<float, 24> ragpos;
	float m_flPoseParameter[24];
	float backtrack_time;
	Vector m_vecAbsOrigin;
	bool needs_extrapolation = false;
	VMatrix boneMatrix[128];
};
struct player_record
{

	std::deque<tick_record> records;

	Vector EyeAngles;
	float LowerBodyYawTarget;
	int Flags;
	float unknown;
};

struct target
{
	Vector TargetPos;
	int health;
	float distance;
	bool in_air;
	C_BaseEntity* Entity = nullptr;
	tick_record current_record;
};

struct target_list
{
	std::deque<target> target_deque;
};

class LagCompensation
{
public:
	player_record PlayerRecord[64];
	target_list target_iter[64];
	float GetLerpTime();
	void Save_Record(C_BaseEntity * Entity, tick_record record);
	void UpdateBacktrackRecords(C_BaseEntity* pPlayer);
	bool IsTickValid(tick_record record);
	void ValidCmd(CUserCmd* cmd, tick_record record);
	void Rage_Backtrack();
	void Start_Adjustment(C_BaseEntity* Entity, tick_record record);
	void End_Adjustment(C_BaseEntity* Entity);
}; extern LagCompensation* LagComp;

