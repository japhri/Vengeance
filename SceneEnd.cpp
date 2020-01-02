#include "Main.h"
#include "BackTrack.h"
IMaterial* CoveredLit;
IMaterial* OpenLit;
IMaterial* CoveredFlat;
IMaterial* OpenFlat;
IMaterial* backtrack;
IMaterial* materialMetall = nullptr;
IMaterial* materialMetallnZ = nullptr;
#include "ChamsUtils.h"
void CreateMaterialChams()
{
	CoveredLit = G_MatHelper->CreateMaterial(true);
	OpenLit = G_MatHelper->CreateMaterial(false);
	CoveredFlat = G_MatHelper->CreateMaterial(true, false);
	backtrack = G_MatHelper->CreateMaterial(true, false);
	OpenFlat = G_MatHelper->CreateMaterial(false, false);

	std::ofstream("csgo\\materials\\simple_ignorez_reflective.vmt") << R"#("VertexLitGeneric"
{

  "$basetexture" "vgui/white_additive"
  "$ignorez"      "1"
  "$envmap"       "env_cubemap"
  "$normalmapalphaenvmapmask"  "1"
  "$envmapcontrast"             "1"
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";

	std::ofstream("csgo\\materials\\simple_regular_reflective.vmt") << R"#("VertexLitGeneric"
{

  "$basetexture" "vgui/white_additive"
  "$ignorez"      "0"
  "$envmap"       "env_cubemap"
  "$normalmapalphaenvmapmask"  "1"
  "$envmapcontrast"             "1"
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";

	materialMetall = G_MaterialSystem->FindMaterial("simple_ignorez_reflective", TEXTURE_GROUP_MODEL);
	materialMetallnZ = G_MaterialSystem->FindMaterial("simple_regular_reflective", TEXTURE_GROUP_MODEL);
}

#include "Variables.h"

void __fastcall Hooks::scene_end(void* thisptr, void* edx) {

	static auto scene_end_o = renderviewVMT->GetOriginalMethod< decltype(&scene_end) >(9);
	scene_end_o(thisptr, edx);
	static bool init = false;
	if (!init)
	{
		CreateMaterialChams();
		init = true;
	}
	static IMaterial *covered;
	static IMaterial *open;
	float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	IMaterial *friendlyChamsMat = ChamsUtils::GetChamsMaterial(g_Options.chamsFriendlyMaterial);
	IMaterial *enemyChamsMat = ChamsUtils::GetChamsMaterial(g_Options.chamsEnemyMaterial);
	IMaterial *localChamsMat = ChamsUtils::GetChamsMaterial(g_Options.chamsLocalMaterial);
	IMaterial *friendlyXQZChamsMat = ChamsUtils::GetXQZChamsMaterial(g_Options.chamsFriendlyXQZMaterial);
	IMaterial *enemyXQZChamsMat = ChamsUtils::GetXQZChamsMaterial(g_Options.chamsEnemyXQZMaterial);
	bool doChams = false;
	bool doXQZChams = false;
	IMaterial *chamsMat = 0;
	IMaterial *xqzChamsMat = 0;
	float *chamsCol = 0;
	float *xqzChamsCol = 0;
	float ChamsHistory[3] = { 1.f, 1.f, 1.f };
}

void __fastcall Hooks::DrawModelExecute(void* ecx, void* edx, void* * ctx, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{

	C_BaseEntity* pLocalPlayer = G_EntList->GetClientEntity(G_Engine->GetLocalPlayer());

	if (!pLocalPlayer)
	{
		modelrenderVMT->GetOriginalMethod<DrawModelExecuteFn>(21)(ecx, ctx, state, pInfo, pCustomBoneToWorld);
		return;
	}


	modelrenderVMT->GetOriginalMethod<DrawModelExecuteFn>(21)(ecx, ctx, state, pInfo, pCustomBoneToWorld);
	G_ModelRender->ForcedMaterialOverride(NULL);
}