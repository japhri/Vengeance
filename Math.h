#pragma once
#include "Main.h"

#define PI 3.14159265358979323846f
#define PI_F	((float)(PI)) 
//#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
//#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )

namespace Math
{
	void NormalizeAngles(QAngle& angles);
	void NormalizeVector(Vector& vec);
	void CorrectMovement(QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);
	void VectorScale(const float* in, vec_t scale, float* out);
	void ClampAngles(QAngle& angles);
	void VectorTransform(const Vector& in1, const matrix3x4_t& in2, Vector& out);
	void AngleVectors(const QAngle &angles, Vector& forward);
	void AngleVectors(const QAngle &angles, Vector& forward, Vector& right, Vector& up);
	void VectorAngles(Vector forward, Vector &angles);
	Vector CrossProduct(const Vector &a, const Vector &b);
	void AngleVectors(Vector& angles, Vector *forward);
	void VectorAngles2(const Vector& forward, Vector& up, QAngle& angles);
	void cp(const float* v1, const float* v2, float* cross);
	void VectorAngles3(const Vector& forward, QAngle& angles);
	bool WorldToScreen(const Vector& in, Vector& out);
	bool screen_transform(const Vector& in, Vector& out);
	void SinCos(float a, float* s, float*c);
	void VectorMA(const Vector &start, float scale, const Vector &direction, Vector &dest);
	float GetFov(const QAngle &viewAngle, const QAngle &aimAngle);
	float GetDistance(Vector src, Vector dst);
	QAngle CalcAngle(Vector src, Vector dst);
	void SmoothAngle(QAngle src, QAngle &dst, float factor);
	float DotProduct(Vector &v1, const float* v2);
	Vector RotateVectorYaw(Vector origin, float angle, Vector point);
	void ClampMovement(float forward, float side);
	inline float ClampYaw(float yaw)
	{
		while (yaw > 180.f)
			yaw -= 360.f;
		while (yaw < -180.f)
			yaw += 360.f;
		return yaw;
	}

	inline bool InBox(int rx1, int ry1, int rx2, int ry2, int px, int py)
	{
		return px > rx1 && px < rx2 && py > ry1 && py < ry2;
	}
	//--------------------------------------------------------------------------------


	float __fastcall AngleDiff(float a1, float a2);
}