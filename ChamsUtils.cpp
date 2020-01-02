#include "ChamsUtils.h"
#include "Resources.h"

#include "Variables.h"
IMaterial *ChamsUtils::materialList[14] = { 0 };
IMaterial *ChamsUtils::xqzMaterialList[14] = { 0 };
IMaterial *ChamsUtils::shineMaterialList[3] = { 0 };
bool ChamsUtils::createdChams = false;


namespace ChamsUtils
{


	bool ChamsUtils::CanDoChamsInSceneEnd(int matIndex, float alpha)
	{
		// Use DME chams if alpha is < 255 or it's the ghost material
		return alpha >= 1.0f && matIndex != 8;
	}



	void ChamsUtils::WriteMaterialFile(char *name, char *bytes, int size)
	{
		std::ofstream fout;
		std::string path = "csgo\\materials\\vengeance\\" + std::string(name);
		fout.open(path.c_str(), std::ios::binary | std::ios::out);

		char* text = (char*)malloc(size + 1);
		memcpy(text, bytes, size);
		text[size] = 0;

		fout.write(bytes, size);
		fout.close();

	}



	void ChamsUtils::LoadAndWriteFile(char *type, WORD resID, char *name)
	{
		HGLOBAL     res_handle = NULL;
		HRSRC       res;
		char *      res_data;
		DWORD       res_size;

		// NOTE: providing g_hInstance is important, NULL might not work
		res = FindResourceEx(g_Globals->hmDll, type, MAKEINTRESOURCE(resID), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));//FindResource(Global::hmDll, MAKEINTRESOURCE(IDR_VMT_CHAMS_DEFAULT), RT_RCDATA);
		if (!res)
			return;
		res_handle = LoadResource(g_Globals->hmDll, res);
		if (!res_handle)
			return;
		res_data = (char*)LockResource(res_handle);
		res_size = SizeofResource(g_Globals->hmDll, res);
		/* you can now use the resource data */
		ChamsUtils::WriteMaterialFile(name, res_data, res_size);
	}



	void ChamsUtils::CreateChamsMaterials()
	{
		char materialFoldPathAbs[1024];

		GetModuleFileName(NULL, materialFoldPathAbs, 1024);

		int i = strlen(materialFoldPathAbs);
		while (materialFoldPathAbs[i] != '\\') materialFoldPathAbs[i--] = '\0';

		strcat_s(materialFoldPathAbs, 1024, "csgo\\materials\\vengeance");

		G_Cvar->ConsolePrintf("%s\n", materialFoldPathAbs);

		if (CreateDirectory(materialFoldPathAbs, NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
		{
			/******************************** VTFs ********************************/

			// Clown texture
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_CLOWN_TEXTURE, "clown_texture.vtf");

			// Slime albedo
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_SLIME_ALBEDO, "slime_albedo.vtf");

			// Lava albedo
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_LAVA_ALBEDO, "lava_albedo.vtf");

			// Ice albedo
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_ICE_ALBEDO, "ice_albedo.vtf");

			// Normal up
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_NORMAL_UP, "normal_up.vtf");

			// Tin foil normal
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_TIN_FOIL_NORMAL, "tin_foil_normal.vtf");

			// Slime normal
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_SLIME_NORMAL, "slime_normal.vtf");

			// Lava normal
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_SLIME_NORMAL, "slime_normal.vtf");

			// Ice normal
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_ICE_NORMAL, "ice_normal.vtf");

			// Slime phong exponent map
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_SLIME_EXPONENT, "slime_exponent.vtf");

			// Lava phong exponent map
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_LAVA_EXPONENT, "lava_exponent.vtf");

			// Ice phong exponent map
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_ICE_EXPONENT, "ice_exponent.vtf");

			// Lava selfillum mask
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_LAVA_EMISSIVE_MASK, "lava_emissive_mask.vtf");

			// Posterize lightwarp
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_POSTERIZE_LIGHTWARP, "posterize_lightwarp.vtf");

			// Super dark posterize lightwarp
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_SUPER_DARK_POSTERIZE_LIGHTWARP, "super_dark_posterize_lightwarp.vtf");

			// Dark lightwarp
			ChamsUtils::LoadAndWriteFile("VTF", IDR_VTF_DARK_LIGHTWARP, "dark_lightwarp.vtf");

			/******************************** VMTs ********************************/

			// Default chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_DEFAULT, "chams_default.vmt");
			materialList[0] = G_MaterialSystem->FindMaterial("vengeance/chams_default", TEXTURE_GROUP_MODEL, false, "");

			// Default XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_DEFAULT_XQZ, "chams_default_xqz.vmt");
			xqzMaterialList[0] = G_MaterialSystem->FindMaterial("vengeance/chams_default_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Flat chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_FLAT, "chams_flat.vmt");
			materialList[1] = G_MaterialSystem->FindMaterial("vengeance/chams_flat", TEXTURE_GROUP_MODEL, false, "");

			// Flat XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_FLAT_XQZ, "chams_flat_xqz.vmt");
			xqzMaterialList[1] = G_MaterialSystem->FindMaterial("vengeance/chams_flat_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Cartoon chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_CARTOON, "chams_cartoon.vmt");
			materialList[2] = G_MaterialSystem->FindMaterial("vengeance/chams_cartoon", TEXTURE_GROUP_MODEL, false, "");

			// Cartoon XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_CARTOON_XQZ, "chams_cartoon_xqz.vmt");
			xqzMaterialList[2] = G_MaterialSystem->FindMaterial("vengeance/chams_cartoon_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Clown chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_CLOWN, "chams_clown.vmt");
			materialList[3] = G_MaterialSystem->FindMaterial("vengeance/chams_clown", TEXTURE_GROUP_MODEL, false, "");

			// Clown XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_CLOWN_XQZ, "chams_clown_xqz.vmt");
			xqzMaterialList[3] = G_MaterialSystem->FindMaterial("vengeance/chams_clown_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Ferrofluid chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_FERROFLUID, "chams_ferrofluid.vmt");
			materialList[4] = G_MaterialSystem->FindMaterial("vengeance/chams_ferrofluid", TEXTURE_GROUP_MODEL, false, "");

			// Ferrofluid XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_FERROFLUID_XQZ, "chams_ferrofluid_xqz.vmt");
			xqzMaterialList[4] = G_MaterialSystem->FindMaterial("vengeance/chams_ferrofluid_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Plastic chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_PLASTIC, "chams_plastic.vmt");
			materialList[5] = G_MaterialSystem->FindMaterial("vengeance/chams_plastic", TEXTURE_GROUP_MODEL, false, "");

			// Plastic XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_PLASTIC_XQZ, "chams_plastic_xqz.vmt");
			xqzMaterialList[5] = G_MaterialSystem->FindMaterial("vengeance/chams_plastic_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Aluminum chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_ALUMINUM, "chams_aluminum.vmt");
			materialList[6] = G_MaterialSystem->FindMaterial("vengeance/chams_aluminum", TEXTURE_GROUP_MODEL, false, "");

			// Aluminum XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_ALUMINUM_XQZ, "chams_aluminum_xqz.vmt");
			xqzMaterialList[6] = G_MaterialSystem->FindMaterial("vengeance/chams_aluminum_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Gold chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_GOLD, "chams_gold.vmt");
			materialList[7] = G_MaterialSystem->FindMaterial("vengeance/chams_gold", TEXTURE_GROUP_MODEL, false, "");

			// Gold XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_GOLD_XQZ, "chams_gold_xqz.vmt");
			xqzMaterialList[7] = G_MaterialSystem->FindMaterial("vengeance/chams_gold_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Ghost chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_GHOST, "chams_ghost.vmt");
			materialList[8] = G_MaterialSystem->FindMaterial("vengeance/chams_ghost", TEXTURE_GROUP_MODEL, false, "");

			// Ghost XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_GHOST_XQZ, "chams_ghost_xqz.vmt");
			xqzMaterialList[8] = G_MaterialSystem->FindMaterial("vengeance/chams_ghost_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Tin foil chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_TIN_FOIL, "chams_tin_foil.vmt");
			materialList[9] = G_MaterialSystem->FindMaterial("vengeance/chams_tin_foil", TEXTURE_GROUP_MODEL, false, "");

			// Tin foil XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_TIN_FOIL_XQZ, "chams_tin_foil_xqz.vmt");
			xqzMaterialList[9] = G_MaterialSystem->FindMaterial("vengeance/chams_tin_foil_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Slime chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_SLIME, "chams_slime.vmt");
			materialList[10] = G_MaterialSystem->FindMaterial("vengeance/chams_slime", TEXTURE_GROUP_MODEL, false, "");

			// Slime XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_SLIME_XQZ, "chams_slime_xqz.vmt");
			xqzMaterialList[10] = G_MaterialSystem->FindMaterial("vengeance/chams_slime_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Lava chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_LAVA, "chams_lava.vmt");
			materialList[11] = G_MaterialSystem->FindMaterial("vengeance/chams_lava", TEXTURE_GROUP_MODEL, false, "");

			// Lava XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_LAVA_XQZ, "chams_lava_xqz.vmt");
			xqzMaterialList[11] = G_MaterialSystem->FindMaterial("vengeance/chams_lava_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Ice chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_ICE, "chams_ice.vmt");
			materialList[12] = G_MaterialSystem->FindMaterial("vengeance/chams_ice", TEXTURE_GROUP_MODEL, false, "");

			// Ice XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_ICE_XQZ, "chams_ice_xqz.vmt");
			xqzMaterialList[12] = G_MaterialSystem->FindMaterial("vengeance/chams_ice_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Dark chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_DARK, "chams_dark.vmt");
			materialList[13] = G_MaterialSystem->FindMaterial("vengeance/chams_dark", TEXTURE_GROUP_MODEL, false, "");

			// Dark XQZ chams
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_CHAMS_DARK_XQZ, "chams_dark_xqz.vmt");
			xqzMaterialList[13] = G_MaterialSystem->FindMaterial("vengeance/chams_dark_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Custom chams
			materialList[chamsMaterialListCount - 1] = G_MaterialSystem->FindMaterial("vengeance/chams_custom", TEXTURE_GROUP_MODEL, false, "");

			// Custom XQZ chams
			xqzMaterialList[chamsMaterialListCount - 1] = G_MaterialSystem->FindMaterial("vengeance/chams_custom_xqz", TEXTURE_GROUP_MODEL, false, "");

			// Highlight shine
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_SHINE_HIGHLIGHT, "shine_highlight.vmt");
			shineMaterialList[0] = G_MaterialSystem->FindMaterial("vengeance/shine_highlight", TEXTURE_GROUP_MODEL, false, "");

			// Rimlight shine
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_SHINE_RIMLIGHT, "shine_rimlight.vmt");
			shineMaterialList[1] = G_MaterialSystem->FindMaterial("vengeance/shine_rimlight", TEXTURE_GROUP_MODEL, false, "");

			// Cartoon shine
			ChamsUtils::LoadAndWriteFile("VMT", IDR_VMT_SHINE_CARTOON, "shine_cartoon.vmt");
			shineMaterialList[2] = G_MaterialSystem->FindMaterial("vengeance/shine_cartoon", TEXTURE_GROUP_MODEL, false, "");

			createdChams = true;
		}
	}



	IMaterial *ChamsUtils::GetChamsMaterial(int index)
	{
		if (!createdChams) ChamsUtils::CreateChamsMaterials();

		return materialList[index];
	}



	IMaterial* ChamsUtils::GetXQZChamsMaterial(int index)
	{
		if (!createdChams) ChamsUtils::CreateChamsMaterials();

		return xqzMaterialList[index];
	}



	IMaterial *ChamsUtils::GetShineMaterial(int index)
	{
		if (!createdChams) ChamsUtils::CreateChamsMaterials();

		if (index >= 0)
			return shineMaterialList[index];
		else
			return nullptr;
	}
}