#pragma once
#include "Vector2D.h"
#include "Vec2.h"
/* macros */
#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))



class Utils {
public:
	template<typename FuncType>
	inline FuncType get_vfunc(void* ppClass, DWORD index) {
		PDWORD pVTable = *(PDWORD*)ppClass;
		DWORD dwAddress = pVTable[index];
		return (FuncType)(dwAddress);
	}
	template<typename T>
	__forceinline static T vfunc(void *base, int index)
	{
		DWORD *vTabella = *(DWORD**)base;
		return (T)vTabella[index];
	}
	void InitHooks();
	DWORD WaitOnModuleHandle(std::string moduleName);
	DWORD FindPattern(std::string moduleName, BYTE * Mask, char * szMask);
	DWORD FindPatternIDA(std::string moduleName, std::string pattern);
	void OpenConsole(std::string Title);
	bool WorldToScreen(const Vector &origin, Vector &screen);
	bool KeyDown(int key);
	bool InBox(Vector2D boxPos, Vector2D boxSize, Vector2D testPos);
	bool InBox(Vec2 boxPos, Vec2 boxSize, Vec2 testPos);
	long long CurrentTimeMillis();
	Vec2 CursorPos();

	float FindYawOffset(float YawA, float YawB)
	{
		float offset = 0.0f;
		while (abs((YawA + 360.0f) - YawB) + offset < abs(YawA - YawB)) offset += 360.0f;
		if (abs((YawA - 360.0f) - YawB) + offset < abs(YawA - YawB)) offset -= 360.0f;
		return offset;
	}

private:
}; extern Utils* g_Utils;




