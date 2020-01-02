#include "Main.h"

void __fastcall Hooks::g_hkBeginFrame(void* thisptr)
{

	beginFrame->GetOriginalMethod<BeginFrameFn>(9)(thisptr);
}