#include "Main.h"

 IBaseClientDLL* G_Client;
 IVEngineClient* G_Engine;
 IClientEntityList* G_EntList;
 IGlobalVars* G_Globals;
 IClientMode* G_ClientMode;
 ISurface* G_Surface;
 CInput* G_Input;
 CModelInfo* G_ModelInfo;
 CInputSystem* G_InputSystem;
 CPanel* G_Panel;
 IStudioRender* G_StudioRender;
 IEngineTrace* G_EngineTrace;
 ICvar* G_Cvar;
 CRenderView* G_RenderView;
 CModelRender* G_ModelRender;
 CMaterialSystem* G_MaterialSystem;
 CGameMovement* G_Movement;
 CPrediction* G_Prediction;
 IGameEventManager* G_Events;
 CDebugOverlay* DebugOverlay;
 IPhysicsSurfaceProps* G_PhysicProps;
 IMoveHelper* G_MoveHelper;
 IEngineSound* G_Sound;
 IViewRenderBeams* G_Beams;
 CInterfaces Interfaces;

 IsBreakableEntityFn IsBreakableEntity = nullptr;
 std::uint8_t* _ClipTraceToPlayers = nullptr;

 namespace Global
 {
	  bool ispano = strstr(GetCommandLineA(), "-legacyscaleformui");
	  bool init;
 };

 uint64_t FindPatternIDA(const char* szModule, const char* szSignature)
 {

#define INRANGE(x,a,b)  (x >= a && x <= b) 
//#define getBits( x )    (INRANGE((x&(~0x20)),XorStr('A'),XorStr('F')) ? ((x&(~0x20)) - XorStr('A') + 0xa) : (INRANGE(x,XorStr('0'),XorStr('9')) ? x - XorStr('0') : 0))
//#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

	 MODULEINFO modInfo;
	 GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &modInfo, sizeof(MODULEINFO));
	 DWORD startAddress = (DWORD)modInfo.lpBaseOfDll;
	 DWORD endAddress = startAddress + modInfo.SizeOfImage;
	 const char* pat = szSignature;
	 DWORD firstMatch = 0;
	 for (DWORD pCur = startAddress; pCur < endAddress; pCur++) {
		 if (!*pat) return firstMatch;
		 if (*(PBYTE)pat == XorStr('\?') || *(BYTE*)pCur == getByte(pat)) {
			 if (!firstMatch) firstMatch = pCur;
			 if (!pat[2]) return firstMatch;
			 if (*(PWORD)pat == XorStr('\?\?') || *(PBYTE)pat != XorStr('\?')) pat += 3;
			 else pat += 2;    //one ?
		 }
		 else {
			 pat = szSignature;
			 firstMatch = 0;
		 }
	 }
	 return NULL;
 }

 std::uint8_t *PatternScan(void* module, const char* signature)
 {


	 static auto pattern_to_byte = [](const char* pattern) {
		 auto bytes = std::vector<int>{};
		 auto start = const_cast<char*>(pattern);
		 auto end = const_cast<char*>(pattern) + strlen(pattern);

		 for (auto current = start; current < end; ++current) {
			 if (*current == '?') {
				 ++current;
				 if (*current == '?')
					 ++current;
				 bytes.push_back(-1);
			 }
			 else {
				 bytes.push_back(strtoul(current, &current, 16));
			 }
		 }
		 return bytes;
	 };

	 auto dosHeader = (PIMAGE_DOS_HEADER)module;
	 auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

	 auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	 auto patternBytes = pattern_to_byte(signature);
	 auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

	 auto s = patternBytes.size();
	 auto d = patternBytes.data();

	 for (auto i = 0ul; i < sizeOfImage - s; ++i) {
		 bool found = true;
		 for (auto j = 0ul; j < s; ++j) {
			 if (scanBytes[i + j] != d[j] && d[j] != -1) {
				 found = false;
				 break;
			 }
		 }
		 if (found) {
			 return &scanBytes[i];
		 }
	 }


	 return nullptr;
 }


