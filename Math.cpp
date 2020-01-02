#include "Math.h"

namespace Math
{
	void NormalizeAngles(QAngle& angles)
	{
		for (auto i = 0; i < 3; i++) {
			while (angles[i] < -180.0f) angles[i] += 360.0f;
			while (angles[i] >  180.0f) angles[i] -= 360.0f;
		}
	}

	void NormalizeVector(Vector& vec)
	{
		for (auto i = 0; i < 3; i++) {
			while (vec[i] < -180.0f) vec[i] += 360.0f;
			while (vec[i] >  180.0f) vec[i] -= 360.0f;
		}
		vec[2] = 0.f;
	}

	template<class T, class U>
	static T clamp(T in, U low, U high)
	{
		if (in <= low)
			return low;

		if (in >= high)
			return high;

		return in;
	}

	void CorrectMovement(QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove)
	{
		// side/forward move correction
		/*float deltaView;
		float f1;
		float f2;

		if (vOldAngles.yaw < 0.f)
		f1 = 360.0f + vOldAngles.yaw;
		else
		f1 = vOldAngles.yaw;

		if (pCmd->viewangles.yaw < 0.0f)
		f2 = 360.0f + pCmd->viewangles.yaw;
		else
		f2 = pCmd->viewangles.yaw;

		if (f2 < f1)
		deltaView = abs(f2 - f1);
		else
		deltaView = 360.0f - abs(f1 - f2);

		deltaView = 360.0f - deltaView;

		pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
		if ((pCmd->viewangles.pitch > 90 && pCmd->viewangles.pitch < 270) || (pCmd->viewangles.pitch < -90 && pCmd->viewangles.pitch > -270))
		pCmd->forwardmove *= -1;
		pCmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;*/

		float theta = (pCmd->viewangles.y - vOldAngles.y) / 180.0f * static_cast<float>(M_PI);

		/*

		R(θ) = [cos(θ) - sin(θ)]
		[sin(θ) + cos(θ)]

		*/

		float st = sin(theta);
		float ct = cos(theta);

		pCmd->forwardmove = ct * fOldForward - st * fOldSidemove;
		pCmd->sidemove = st * fOldForward + ct * fOldSidemove;

		float pitch = pCmd->viewangles.x;
		while (pitch >= 360.0f)
			pitch -= 360.0f;
		while (pitch < 0.0f)
			pitch += 360.0f;

		if (pitch > 90.0f && pitch < 270.0f)
			pCmd->forwardmove *= -1.0f;

		pCmd->forwardmove = clamp(pCmd->forwardmove, -450.0f, 450.0f);
		pCmd->sidemove = clamp(pCmd->sidemove, -450.0f, 450.0f);

		if (pCmd->forwardmove < -450.0f || pCmd->forwardmove > 450.0f)
			pCmd->forwardmove = 0.0f;

		if (pCmd->sidemove < -450.0f || pCmd->sidemove > 450.0f)
			pCmd->sidemove = 0.0f;
	}

	Vector RotateVectorYaw(Vector origin, float angle, Vector point)
	{
		float s;
		float c;
		SinCos(DEG2RAD(angle), &s, &c);

		// translate point back to origin:
		point.x -= origin.x;
		point.y -= origin.y;

		// rotate point
		float xnew = point.x * c - point.y * s;
		float ynew = point.x * s + point.y * c;

		// translate point back:
		point.x = xnew + origin.x;
		point.y = ynew + origin.y;
		return point;
	}

	//--------------------------------------------------------------------------------
	void ClampAngles(QAngle& angles)
	{
		if (angles.x > 89.0f) angles.x = 89.0f;
		else if (angles.x < -89.0f) angles.x = -89.0f;

		if (angles.y > 180.0f) angles.y = 180.0f;
		else if (angles.y < -180.0f) angles.y = -180.0f;

		angles.z = 0;
	}

	void VectorScale(const float* in, vec_t scale, float* out)
	{
		out[0] = in[0] * scale;
		out[1] = in[1] * scale;
		out[2] = in[2] * scale;
	}

	void ClampMovement(float forward, float side)
	{
		if (forward > 450.0f)
			forward = 450.0f;
		else if (forward < -450.0f)
			forward = -450.0f;

		if (side > 450.0f)
			side = 450.0f;
		else if (side < -450.0f)
			side = -450.0f;
	}

	//--------------------------------------------------------------------------------
	void VectorTransform(const Vector& in1, const matrix3x4_t& in2, Vector& out)
	{
		out[0] = in1.Dot(in2[0]) + in2[0][3];
		out[1] = in1.Dot(in2[1]) + in2[1][3];
		out[2] = in1.Dot(in2[2]) + in2[2][3];
	}
	//--------------------------------------------------------------------------------
	void AngleVectors(const QAngle &angles, Vector& forward)
	{
		float	sp, sy, cp, cy;

		SinCos(DEG2RAD(angles[1]), &sy, &cy);
		SinCos(DEG2RAD(angles[0]), &sp, &cp);

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
	}

	void AngleVectors(Vector& angles, Vector *forward)
	{
		float	sp, sy, cp, cy;


		SinCos(DEG2RAD(angles[1]), &sy, &cy);
		SinCos(DEG2RAD(angles[0]), &sp, &cp);

		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}
	//--------------------------------------------------------------------------------
	void AngleVectors(const QAngle &angles, Vector& forward, Vector& right, Vector& up)
	{
		float sr, sp, sy, cr, cp, cy;

		SinCos(DEG2RAD(angles[1]), &sy, &cy);
		SinCos(DEG2RAD(angles[0]), &sp, &cp);
		SinCos(DEG2RAD(angles[2]), &sr, &cr);

		forward.x = (cp * cy);
		forward.y = (cp * sy);
		forward.z = (-sp);
		right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right.y = (-1 * sr * sp * sy + -1 * cr *  cy);
		right.z = (-1 * sr * cp);
		up.x = (cr * sp * cy + -sr * -sy);
		up.y = (cr * sp * sy + -sr * cy);
		up.z = (cr * cp);
	}

	void VectorMA(const Vector &start, float scale, const Vector &direction, Vector &dest)
	{
		dest.x = start.x + scale * direction.x;
		dest.y = start.y + scale * direction.y;
		dest.z = start.z + scale * direction.z;
	}

	float DotProduct(Vector &v1, const float* v2)
	{
		return v1.x*v2[0] + v1.y*v2[1] + v1.z*v2[2];
	}
	//--------------------------------------------------------------------------------
	void VectorAngles(Vector forward, Vector &angles)
	{
		float yaw, pitch;

		if (forward.y == 0 && forward.x == 0)
		{
			yaw = 0;
			pitch = float((forward.z > 0) ? 270 : 90);
		}
		else
		{
			yaw = RAD2DEG(atan2(forward.y, forward.x));

			if (yaw < 0) yaw += 360;

			pitch = RAD2DEG(atan2(-forward.z, forward.Length2D()));

			if (pitch < 0) pitch += 360;
		}

		angles.x = pitch;
		angles.y = yaw;
		angles.z = 0;
	}

	Vector CrossProduct(const Vector &a, const Vector &b)
	{
		return Vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
	}

	void cp(const float* v1, const float* v2, float* cross)
	{
		cross[0] = v1[1] * v2[2] - v1[2] * v2[1];
		cross[1] = v1[2] * v2[0] - v1[0] * v2[2];
		cross[2] = v1[0] * v2[1] - v1[1] * v2[0];
	}

	void VectorAngles2(const Vector& forward, Vector& up, QAngle& angles)
	{
		Vector left = Math::CrossProduct(up, forward);
		left.NormalizeInPlace();

		float forwardDist = forward.Length2D();

		if (forwardDist > 0.001f)
		{
			angles.x = atan2f(-forward.z, forwardDist) * 180 / PI_F;
			angles.y = atan2f(forward.y, forward.x) * 180 / PI_F;

			float upZ = (left.y * forward.x) - (left.x * forward.y);
			angles.z = atan2f(left.z, upZ) * 180 / PI_F;
		}
		else
		{
			angles.x = atan2f(-forward.z, forwardDist) * 180 / PI_F;
			angles.y = atan2f(-left.x, left.y) * 180 / PI_F;
			angles.z = 0;
		}
	}



	void VectorAngles3(const Vector& forward, QAngle& angles)
	{
		float	tmp, yaw, pitch;

		if (forward[1] == 0 && forward[0] == 0) {
			yaw = 0;
			if (forward[2] > 0)
				pitch = 270;
			else
				pitch = 90;
		}
		else {
			yaw = (atan2(forward[1], forward[0]) * 180 / static_cast<float>(M_PI));
			if (yaw < 0)
				yaw += 360;

			tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
			pitch = (atan2(-forward[2], tmp) * 180 / static_cast<float>(M_PI));
			if (pitch < 0)
				pitch += 360;
		}

		angles[0] = pitch;
		angles[1] = yaw;
		angles[2] = 0;
	}
	//--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	
	//--------------------------------------------------------------------------------
	void SinCos(float a, float* s, float*c)
	{
		*s = sin(a);
		*c = cos(a);
	}

	float GetFov(const QAngle &viewAngle, const QAngle &aimAngle)
	{
		Vector ang, aim;

		AngleVectors(viewAngle, aim);
		AngleVectors(aimAngle, ang);

		return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
	}

	float GetDistance(Vector src, Vector dst)
	{
		return sqrtf(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2) + pow(src.z - dst.z, 2));
	}

	QAngle CalcAngle(Vector src, Vector dst)
	{
		QAngle angles;
		Vector delta = dst - src;
		Math::VectorAngles3(delta, angles);
		return angles;
	}

	void SmoothAngle(QAngle src, QAngle &dst, float factor)
	{
		QAngle delta = dst - src;

		NormalizeAngles(delta);

		dst = src + delta / factor;
	}

	float __fastcall AngleDiff(float a1, float a2)
	{
		float val = fmodf(a1 - a2, 360.0);

		while (val < -180.0f) val += 360.0f;
		while (val >  180.0f) val -= 360.0f;

		return val;
	}
}

