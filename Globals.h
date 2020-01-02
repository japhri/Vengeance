#pragma once


class CScreen
{
public:
	int width, height;
};
class Globals
{
public:
	HWND CSGOWindow;
	bool isPanorama;
	bool RenderInit;
	C_BaseEntity* local = nullptr;
	CUserCmd* usercmd;
	HMODULE hmDll = nullptr;
	QAngle RealAngle = QAngle();
	QAngle FakeAngle = QAngle();
	vec_t PitchAngle = vec_t();
	bool antiaiming = false;
	bool sendpacket;
	bool SendPackets = true;
	int ChokedPackets = 0;
	int chokedTicks;
	bool bShouldChoke = false;
	int nChokedTicks = 0;
	float viewMatrix[4][4] = { 0 };
	bool pano = strstr(GetCommandLineA(), "-legacyscaleformui");

	CScreen Screen = CScreen();

private:
}; extern Globals* g_Globals;



class DEBUG
{
public:

	Vector Aimbot_Pos;
	float Damage;

}; extern DEBUG* g_DEBUG;