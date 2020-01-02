#include "Main.h"

void __fastcall Hooks::OverrideView(void* _this, void* _edx, CViewSetup* setup)
{
	clientmodeVMT->GetOriginalMethod<OverrideViewFn>(18)(_this, setup);
	C_BaseEntity* local = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());
	if (G_Engine->IsConnected() && local->isAlive())
	{
		G_Input->m_fCameraInThirdPerson = true;
	}


}