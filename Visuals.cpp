#include "Visuals.h"
#include "Variables.h"

void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b)
{
	if (s == 0.0f)
	{
		// gray
		out_r = out_g = out_b = v;
		return;
	}

	h = fmodf(h, 1.0f) / (60.0f / 360.0f);
	int   i = (int)h;
	float f = h - (float)i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));

	switch (i)
	{
	case 0: out_r = v; out_g = t; out_b = p; break;
	case 1: out_r = q; out_g = v; out_b = p; break;
	case 2: out_r = p; out_g = v; out_b = t; break;
	case 3: out_r = p; out_g = q; out_b = v; break;
	case 4: out_r = t; out_g = p; out_b = v; break;
	case 5: default: out_r = v; out_g = p; out_b = q; break;
	}
}

Color ColorConvertHSVtoRGB(float h, float s, float v)
{
	float r, g, b;
	ColorConvertHSVtoRGB(h, s, v, r, g, b);
	return Color(static_cast<int>(r * 255), static_cast<int>(g * 255), static_cast<int>(b * 255));
}


bool WorldToScreen(const Vector& in, Vector& position)
{
	static uintptr_t clientDll = 0;
	while (!clientDll)
	{
		clientDll = (uintptr_t)GetModuleHandle((client_dll));
		Sleep(100);
	}

	float w = g_Globals->viewMatrix[3][0] * in.x + g_Globals->viewMatrix[3][1] * in.y + g_Globals->viewMatrix[3][2] * in.z + g_Globals->viewMatrix[3][3];

	float ScreenWidth = (float)g_Globals->Screen.width;
	float ScreenHeight = (float)g_Globals->Screen.height;

	if (w > 0.01)
	{
		float inverseWidth = 1 / w;
		position.x = (float)((ScreenWidth / 2) + (0.5 * ((g_Globals->viewMatrix[0][0] * in.x + g_Globals->viewMatrix[0][1] * in.y + g_Globals->viewMatrix[0][2] * in.z + g_Globals->viewMatrix[0][3]) * inverseWidth) * ScreenWidth + 0.5));
		position.y = (float)((ScreenHeight / 2) - (0.5 * ((g_Globals->viewMatrix[1][0] * in.x + g_Globals->viewMatrix[1][1] * in.y + g_Globals->viewMatrix[1][2] * in.z + g_Globals->viewMatrix[1][3]) * inverseWidth) * ScreenHeight + 0.5));
		return true;
	}

	return false;
}

namespace
{
	Vector VectorKernel(const Vector* vectorList, const int vectorListSize, const int offset, const float* kernel, const int kernelSize)
	{
		Vector sum = Vector(0, 0, 0);
		for (int i = 0; i < kernelSize; i++)
		{
			int index = (offset - kernelSize / 2 + i) % vectorListSize;
			while (index < 0) index += vectorListSize;
			sum += vectorList[index] * kernel[i];
		}
		return sum;
	}
}

void ESP::DrawTaserDistance()
{
	C_BaseEntity* local = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	Vector Prev_Screen, screen_pos;
	CBaseCombatWeapon* Weapon = local->GetWeapon();
	if (Weapon == nullptr || Weapon->GetItemDefinitionIndex() != WEAPON_TASER)
		return;

	static const int steps = 128;
	static const int updateGroups = 4;
	static int currentUpdateGroup = 0;
	static const float mix = 0.5f;

	// http://dev.theomader.com/gaussian-kernel-calculator/
	// Sigma: 2, Kernel Size: 7
	// https://regexr.com/
	// Expression: (\S+)\s*
	// List: $1f, 
	static const float gaussianKernel[] = { 0.071303f, 0.131514f, 0.189879f, 0.214607f, 0.189879f, 0.131514f, 0.071303f };
	static const int gaussianKernelSize = 7;

	float time = ((float)g_Utils->CurrentTimeMillis()) / 1000.0f;

	static float lastTime = time;
	static float timeSinceTickChange = 0.0f;
	static int lastTick = 0;

	if (lastTick != g_Globals->usercmd->tick_count)
	{
		lastTick = g_Globals->usercmd->tick_count;
		lastTime = time;
		timeSinceTickChange = 0.0f;
	}
	else
	{
		timeSinceTickChange = time - lastTime;
	}

	Vector eyePos = local->GetEyePosition3();
	Vector velocity = local->GetVelocity();
	eyePos += velocity * timeSinceTickChange;

	const float distance = 187.f;

	static Vector positions[steps];
	static bool arrayInitialized = false;

	if (!arrayInitialized)
	{
		for (int step = 0; step < steps; step++)
		{
			positions[step] = Vector(0, 0, 0);
		}
		arrayInitialized = true;
	}
	
	for (int step = currentUpdateGroup++ % updateGroups; step < steps; step += updateGroups)
	{
		float a = static_cast<float>(step) / static_cast<float>(steps) *  static_cast<float>(M_PI) * 2.0f;
		Vector dir = Vector(cos(a), sin(a), 0.0f);
		Ray_t ray;
		trace_t trace;
		CTraceFilter filter;
		filter.pSkip = local;
		ray.Init(eyePos, eyePos + dir * distance);
		G_EngineTrace->TraceRay(ray, MASK_SHOT_BRUSHONLY, &filter, &trace);

		// Lerp to new pos
		positions[step] = positions[step] * (1.0f - mix) + (trace.endpos - eyePos) * mix;
	}

	for (int i = 0; i < steps; i++)
	{
		Vector screenPosition;
		Vector screenPositionNext;

		Vector position = VectorKernel(positions, steps, i, gaussianKernel, gaussianKernelSize);
		Vector positionNext = VectorKernel(positions, steps, (i + 1) % steps, gaussianKernel, gaussianKernelSize);

		if (WorldToScreen(eyePos + position, screenPosition) && WorldToScreen(eyePos + positionNext, screenPositionNext))
		{
			float hue = static_cast<float>(i) / steps + time * 0.25f;
			Color color = ColorConvertHSVtoRGB(hue, 1.0f, 1.0f);
			G_Surface->DrawSetColor(color);
			G_Surface->DrawLine(static_cast<int>(screenPosition.x), static_cast<int>(screenPosition.y), static_cast<int>(screenPositionNext.x), static_cast<int>(screenPositionNext.y));
		}
	}
}

void ESP::BombTimer()
{
	C_BaseEntity* local = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	if (local->isAlive())
	{
		CBomb* bomb;
		if (!bomb)
			return;
		float defusetimer = bomb->DefuseTimer() - G_Globals->curtime;
		G_Cvar->ConsolePrintf("Timer : %f\n", defusetimer);
	}
}

