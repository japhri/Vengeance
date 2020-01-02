#pragma once
#include "Main.h"


namespace ChamsUtils
{
	extern IMaterial *materialList[];
	extern IMaterial *xqzMaterialList[];
	extern IMaterial *shineMaterialList[];
	extern bool createdChams;
	bool CanDoChamsInSceneEnd(int matIndex, float alpha);
	void WriteMaterialFile(char *name, char *bytes, int size);
	void LoadAndWriteFile(char *type, WORD res, char *name);
	void CreateChamsMaterials();
	IMaterial *GetChamsMaterial(int index);
	IMaterial *GetXQZChamsMaterial(int index);
	IMaterial *GetShineMaterial(int index);
}