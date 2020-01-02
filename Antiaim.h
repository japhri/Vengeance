#pragma once
#include "Main.h"
#include "Variables.h"

class antiaim
{
public:
	void doAntiAims(CUserCmd * cmd, bool * bSendPacket);
	float doPitch();
	int curtime_fixed_ticks(CUserCmd * ucmd);
	float buildYaw(AntiAimSetting * antiAim);
	bool TraceRayFreestanding(CUserCmd * cmd, float * out);
	bool AutoWallFreestanding(CUserCmd * cmd, float * out);

	void freestanding(CUserCmd * cmd);

	void doIt(CUserCmd* cmd, bool* bSendPacket);


	QAngle cameraViewAngles;
	float lastReal;
	float lastFake;
	float lastCameraYaw;
	float lastPitch;
	float lastFreestanding = 0.0f;
	bool freestandingUpdated = false;
	bool choke;

}; extern antiaim* G_Antiaim;