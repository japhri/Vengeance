#pragma once
extern VMT* panelVMT;
extern VMT* beginFrame;
extern VMT* clientmodeVMT;
extern VMT* enginevguiVMT;
extern VMT* modelrenderVMT;
extern VMT* clientVMT;
extern VMT* HNetchan;
extern VMT* firebulletVMT;
extern VMT* enginetraceVMT;
extern VMT* d3d9VMT;
extern VMT* netChan;
extern VMT* renderviewVMT;
extern VMT* engineVMT;
extern VMT* surfaceVMT;
extern VMT* EngineSound;
extern CVMTHookManager* g_pClientModeHook;
extern CVMTHookManager* G_SurfaceHook;
extern CVMTHookManager* tracehk;
typedef long(__stdcall* tReset)(IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* pp);
extern tReset oResetScene;


using LockCursor_t = void(__thiscall*)(ISurface*);
extern LockCursor_t oLockCursor;
typedef void(__thiscall *BeginFrameFn) (void*);

typedef void(__stdcall *FrameStageNotifyFn) (ClientFrameStage_t);
using SendDatagramFn = int(__thiscall*)(void*, void *);
typedef void(__thiscall *PaintTraverseFn) (void*, unsigned int, bool, bool);
typedef void(__thiscall *DrawModelExecuteFn) (void*, void*, void*, const ModelRenderInfo_t&, matrix3x4_t*);
typedef bool(__thiscall *CreateMoveFn) (void*, float, CUserCmd*);
typedef long(__stdcall* EndSceneFn)(IDirect3DDevice9* device);
typedef long(__stdcall* hkdResetFn)(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresParam);
//typedef void(__thiscall* TE_FireBullets_PostDataUpdateFn)(C_TEFireBullets*, DataUpdateType_t);
//typedef void(__thiscall *TraceRayFn)(void*, const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace);
//typedef void(__stdcall *PaintFn) (PaintMode_t);
typedef void(*RenderSmokePostViewmodelFn) (void*);
typedef void(__thiscall *OverrideViewFn) (void*, CViewSetup*);
typedef float(*GetViewModelFOVFn) (void*);
typedef void(__fastcall * Emitsoundfn) (void* thisptr,void *filter, int entity_index, int channel, const char *sound_entry, uint32_t sound_entry_hash, const char *sample, float volume, float attenuation, int seed, int flag, int pitch, const Vector *origin, const Vector *direction, void *utl_origins, bool update_positions, float sound_time, int speaker_entity, int unknown);
typedef int(__stdcall* IsBoxVisibleFn)(const Vector&, const Vector&);
typedef float(__stdcall *oGetViewModelFOV)();

typedef HRESULT(__stdcall* PresentFn)(IDirect3DDevice9*, RECT*, RECT*, HWND, RGNDATA*);
extern PresentFn oPresent;

using SendDatagramFn = int(__thiscall*)(void*, void *);
extern SendDatagramFn oSendDatagram;

using tEndScene = long(__stdcall*)(IDirect3DDevice9* device);
extern tEndScene oEndScene;
//using TraceRayFn = void(__thiscall*)(void*, const Ray_t&, unsigned int, ITraceFilter*, trace_t*);
//extern TraceRayFn oTraceRay;
typedef float(__stdcall *oGetViewModelFOV)();
float __stdcall GGetViewModelFOV();


namespace Hooks
{
	//void __fastcall Hooked_EmitSound(IEngineSound* thisptr, int edx, IRecipientFilter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, CUtlVector<Vector>* pUtlVecOrigins, bool bUpdatePositions, int flSoundTime, int iSpeakerEntity);
	void __fastcall PaintTraverse(void* ecx, void* edx, unsigned int vgui_panel, bool force_repaint, bool allow_force);
	void __stdcall hk_lockcursor();
	void __stdcall FrameStageNotify(ClientFrameStage_t stage);
	void __fastcall DrawModelExecute(void* ecx, void* edx, void* * ctx, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
	bool __fastcall CreateMove(void* thisptr, void*, float SampleTime, CUserCmd* pCmd);
	void __fastcall scene_end(void* thisptr, void* edx);
	void __fastcall OverrideView(void* _this, void* _edx, CViewSetup* setup);
	//void __fastcall TraceRay(void *thisptr, void*, const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace);
	extern int __fastcall SendDatagram(void* netchan, void*, void *datagram);
	void __fastcall g_hkBeginFrame(void* thisptr);
	void __fastcall EmitSounds(void* thisptr, void *filter, int entity_index, int channel, const char *sound_entry, uint32_t sound_entry_hash, const char *sample, float volume, float attenuation, int seed, int flag, int pitch, const Vector *origin, const Vector *direction, void *utl_origins, bool update_positions, float sound_time, int speaker_entity, int unknown);
	HRESULT __stdcall D3D9_EndScene(IDirect3DDevice9* pDevice);

	HRESULT __stdcall hkdReset(IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresParam);

	extern WNDPROC                            g_pOldWindowProc; //Old WNDPROC pointer
	LRESULT   __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}