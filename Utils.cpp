#include "Main.h"
#include "Resources.h"
#include "Variables.h"

VMT* panelVMT;
VMT* beginFrame;
VMT* clientmodeVMT;
VMT* enginevguiVMT;
VMT* modelrenderVMT;
VMT* clientVMT;
VMT* HNetchan;
VMT* firebulletVMT;
VMT* d3d9VMT;
VMT* netChan;
VMT* enginetraceVMT;
VMT* renderviewVMT;
VMT* surfaceVMT;
VMT* EngineSound;
CVMTHookManager* g_pD3D = nullptr;
CVMTHookManager* G_SurfaceHook = nullptr;
CVMTHookManager* g_pClientModeHook = nullptr;
CVMTHookManager* tracehk = nullptr;

void Utils::InitHooks()
{
	G_MatHelper = new CMaterialHelper();
	panelVMT = new VMT(G_Panel);
	panelVMT->HookVM((void*)Hooks::PaintTraverse, 41);
	panelVMT->ApplyVMT();

	clientmodeVMT = new VMT(G_ClientMode);
	clientmodeVMT->HookVM((void*)Hooks::CreateMove, 24);
	clientmodeVMT->HookVM((void*)Hooks::OverrideView, 18);
	clientmodeVMT->ApplyVMT();

	renderviewVMT = new VMT(G_RenderView);
	renderviewVMT->HookVM((void*)Hooks::scene_end, 9);
	renderviewVMT->ApplyVMT();

	modelrenderVMT = new VMT(G_ModelRender);
	modelrenderVMT->HookVM((void*)Hooks::DrawModelExecute, 21);
	modelrenderVMT->ApplyVMT();

	clientVMT = new VMT(G_Client);
	clientVMT->HookVM((void*)Hooks::FrameStageNotify, 37);
	clientVMT->ApplyVMT();

	beginFrame = new VMT(G_StudioRender);
	beginFrame->HookVM((void*)Hooks::g_hkBeginFrame, 9);
	beginFrame->ApplyVMT();
	//EngineSound = new VMT(G_Sound);
	//EngineSound->HookVM((void*)Hooks::EmitSounds, 5);
    //EngineSound->ApplyVMT();

	auto dwDevice = **(uint32_t**)(FindPatternIDA(XorStr("shaderapidx9.dll"), XorStr("A1 ? ? ? ? 50 8B 08 FF 51 0C")) + 1);

	d3d9VMT = new VMT((void*)dwDevice);
	d3d9VMT->HookVM((void*)Hooks::D3D9_EndScene, 42);
	d3d9VMT->ApplyVMT();

	g_pD3D = new CVMTHookManager(reinterpret_cast<DWORD**>(dwDevice));
	oResetScene = reinterpret_cast<tReset>(g_pD3D->HookMethod(reinterpret_cast<DWORD>(Hooks::hkdReset), 16));

	G_SurfaceHook = new CVMTHookManager(reinterpret_cast<DWORD**>(G_Surface));
	oLockCursor = reinterpret_cast<LockCursor_t>(G_SurfaceHook->HookMethod(reinterpret_cast<DWORD>(Hooks::hk_lockcursor), 67));

	Hooks::g_pOldWindowProc = (WNDPROC)SetWindowLongPtr(g_Globals->CSGOWindow, GWLP_WNDPROC, (LONG_PTR)Hooks::WndProc);


}
DWORD Utils::WaitOnModuleHandle(std::string moduleName)
{
	DWORD ModuleHandle = NULL;
	while (!ModuleHandle)
	{
		ModuleHandle = (DWORD)GetModuleHandle(moduleName.c_str());
		if (!ModuleHandle)
			Sleep(50);
	}
	return ModuleHandle;
}

bool bCompare(const BYTE* Data, const BYTE* Mask, const char* szMask)
{
	for (; *szMask; ++szMask, ++Mask, ++Data)
	{
		if (*szMask == 'x' && *Mask != *Data)
		{
			return false;
		}
	}
	return (*szMask) == 0;
}

DWORD Utils::FindPattern(std::string moduleName, BYTE* Mask, char* szMask)
{
	DWORD Address = WaitOnModuleHandle(moduleName.c_str());
	MODULEINFO ModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)Address, &ModInfo, sizeof(MODULEINFO));
	DWORD Length = ModInfo.SizeOfImage;
	for (DWORD c = 0; c < Length; c += 1)
	{
		if (bCompare((BYTE*)(Address + c), Mask, szMask))
		{
			return DWORD(Address + c);
		}
	}
	return 0;
}

bool Utils::KeyDown(int key)
{
	return (GetKeyState(key) & 0x8000) != 0;
}

bool Utils::InBox(Vector2D boxPos, Vector2D boxSize, Vector2D testPos)
{
	return abs((boxPos.x + boxSize.x / 2) - testPos.x) <= boxSize.x / 2 && abs((boxPos.y + boxSize.y / 2) - testPos.y) <= boxSize.y / 2;
}

bool Utils::InBox(Vec2 boxPos, Vec2 boxSize, Vec2 testPos)
{
	return abs((boxPos.x + boxSize.x / 2) - testPos.x) <= boxSize.x / 2 && abs((boxPos.y + boxSize.y / 2) - testPos.y) <= boxSize.y / 2;
}

long long Utils::CurrentTimeMillis()
{
	static long long start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	return std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count() - start;
}

Vec2 Utils::CursorPos()
{
	POINT screenPos;
	if (!GetCursorPos(&screenPos))
		return Vec2::ZERO;
	MapWindowPoints(HWND_DESKTOP, g_Globals->CSGOWindow, &screenPos, 1);

	return Vec2(screenPos.x, screenPos.y);
}

DWORD Utils::FindPatternIDA(std::string moduleName, std::string pattern)
{
	const char* pat = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo;
	K32GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;
		}
		else
		{
			pat = pattern.c_str();
			firstMatch = 0;
		}
	}

	return NULL;
}


std::string console_title;
void Utils::OpenConsole(std::string Title)
{
	AllocConsole();
	FILE *conin, *conout;

	freopen_s(&conin, XorStr("conin$"), XorStr("r"), stdin);
	freopen_s(&conout, XorStr("conout$"), XorStr("w"), stderr);
	freopen_s(&conout, XorStr("conout$"), XorStr("w"), stdout);

	if (Title.length() > 0)
	{
		SetConsoleTitleA(Title.c_str());
		console_title = Title;
	}
}





Vector2D::Vector2D(void)
{
}

Vector2D::Vector2D(vec_t X, vec_t Y)
{
	x = X; y = Y;
}

Vector2D::Vector2D(vec_t* clr)
{
	x = clr[0]; y = clr[1];
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

void Vector2D::Init(vec_t ix, vec_t iy)
{
	x = ix; y = iy;
}

void Vector2D::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

void Vector2DClear(Vector2D& a)
{
	a.x = a.y = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

Vector2D& Vector2D::operator=(const Vector2D &vOther)
{
	x = vOther.x; y = vOther.y;
	return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

vec_t& Vector2D::operator[](int i)
{
	return ((vec_t*)this)[i];
}

vec_t Vector2D::operator[](int i) const
{
	return ((vec_t*)this)[i];
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

vec_t* Vector2D::Base()
{
	return (vec_t*)this;
}

vec_t const* Vector2D::Base() const
{
	return (vec_t const*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

bool Vector2D::IsValid() const
{
	return !isinf(x) && !isinf(y);
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

bool Vector2D::operator==(const Vector2D& src) const
{
	return (src.x == x) && (src.y == y);
}

bool Vector2D::operator!=(const Vector2D& src) const
{
	return (src.x != x) || (src.y != y);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

void Vector2DCopy(const Vector2D& src, Vector2D& dst)
{
	dst.x = src.x;
	dst.y = src.y;
}

void Vector2D::CopyToArray(float* rgfl) const
{
	rgfl[0] = x; rgfl[1] = y;
}

//-----------------------------------------------------------------------------
// standard Math operations
//-----------------------------------------------------------------------------

void Vector2D::Negate()
{
	x = -x; y = -y;
}

void Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

void Vector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

void Vector2DMultiply(const Vector2D& a, vec_t b, Vector2D& c)
{
	c.x = a.x * b;
	c.y = a.y * b;
}

void Vector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}


void Vector2DDivide(const Vector2D& a, vec_t b, Vector2D& c)
{
	vec_t oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
}

void Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

void Vector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result)
{
	result.x = start.x + s * dir.x;
	result.y = start.y + s * dir.y;
}

// FIXME: Remove
// For backwards compatability
void Vector2D::MulAdd(const Vector2D& a, const Vector2D& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

void Vector2DLerp(const Vector2D& src1, const Vector2D& src2, vec_t t, Vector2D& dest)
{
	dest[0] = src1[0] + (src2[0] - src1[0]) * t;
	dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
vec_t DotProduct2D(const Vector2D& a, const Vector2D& b)
{
	return(a.x*b.x + a.y*b.y);
}

// for backwards compatability
vec_t Vector2D::Dot(const Vector2D& vOther) const
{
	return DotProduct2D(*this, vOther);
}

vec_t Vector2DNormalize(Vector2D& v)
{
	vec_t l = v.Length();
	if (l != 0.0f) {
		v /= l;
	}
	else {
		v.x = v.y = 0.0f;
	}
	return l;
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
vec_t Vector2DLength(const Vector2D& v)
{
	return (vec_t)sqrt(v.x*v.x + v.y*v.y);
}

vec_t Vector2D::NormalizeInPlace()
{
	return Vector2DNormalize(*this);
}

bool Vector2D::IsLengthGreaterThan(float val) const
{
	return LengthSqr() > val*val;
}

bool Vector2D::IsLengthLessThan(float val) const
{
	return LengthSqr() < val*val;
}

vec_t Vector2D::Length(void) const
{
	return Vector2DLength(*this);
}


void Vector2DMin(const Vector2D &a, const Vector2D &b, Vector2D &result)
{
	result.x = (a.x < b.x) ? a.x : b.x;
	result.y = (a.y < b.y) ? a.y : b.y;
}


void Vector2DMax(const Vector2D &a, const Vector2D &b, Vector2D &result)
{
	result.x = (a.x > b.x) ? a.x : b.x;
	result.y = (a.y > b.y) ? a.y : b.y;
}

//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
void ComputeClosestPoint2D(const Vector2D& vecStart, float flMaxDist, const Vector2D& vecTarget, Vector2D *pResult)
{
	Vector2D vecDelta;
	Vector2DSubtract(vecTarget, vecStart, vecDelta);
	float flDistSqr = vecDelta.LengthSqr();
	if (flDistSqr <= flMaxDist * flMaxDist) {
		*pResult = vecTarget;
	}
	else {
		vecDelta /= sqrt(flDistSqr);
		Vector2DMA(vecStart, flMaxDist, vecDelta, *pResult);
	}
}

//-----------------------------------------------------------------------------
// Returns a Vector2D with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------

Vector2D Vector2D::Min(const Vector2D &vOther) const
{
	return Vector2D(x < vOther.x ? x : vOther.x, y < vOther.y ? y : vOther.y);
}

Vector2D Vector2D::Max(const Vector2D &vOther) const
{
	return Vector2D(x > vOther.x ? x : vOther.x, y > vOther.y ? y : vOther.y);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

Vector2D Vector2D::operator-(void) const
{
	return Vector2D(-x, -y);
}

Vector2D Vector2D::operator+(const Vector2D& v) const
{
	Vector2D res;
	Vector2DAdd(*this, v, res);
	return res;
}

Vector2D Vector2D::operator-(const Vector2D& v) const
{
	Vector2D res;
	Vector2DSubtract(*this, v, res);
	return res;
}

Vector2D Vector2D::operator*(float fl) const
{
	Vector2D res;
	Vector2DMultiply(*this, fl, res);
	return res;
}

Vector2D Vector2D::operator*(const Vector2D& v) const
{
	Vector2D res;
	Vector2DMultiply(*this, v, res);
	return res;
}

Vector2D Vector2D::operator/(float fl) const
{
	Vector2D res;
	Vector2DDivide(*this, fl, res);
	return res;
}

Vector2D Vector2D::operator/(const Vector2D& v) const
{
	Vector2D res;
	Vector2DDivide(*this, v, res);
	return res;
}

Vector2D operator*(float fl, const Vector2D& v)
{
	return v * fl;
}

















