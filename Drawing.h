#pragma once

/*#include "DX9 SDK\Include\d3d9.h"
#include <memory>
#include "D3DFont.h"
#include "Color.h"
#include "Vec2.h"
#include <iostream>*/

#include "Main.h"
#include "D3DFont.h"
#include "Vec2.h"

#define GET_D3DCOLOR_ALPHA(x) (( x >> 24) & 255)
#define COL2DWORD(x) (D3DCOLOR_ARGB((x).a(), (x).r(), (x).g(), (x).b()))

struct Style
{
	bool useFill = false;
	Color fill = Color(0, 0, 0, 0);

	bool useStroke = false;
	Color stroke = Color(0, 0, 0, 0);
	int strokeWeight = 1;

	RECT clipRect = { 0, 0, 4096, 4096 };
};

class Drawing
{
public:
	static Drawing& GetInstance();

	void InitDeviceObjects(LPDIRECT3DDEVICE9 pDevice);
	void RestoreDeviceObjects(LPDIRECT3DDEVICE9 pDevice);
	void InvalidateDeviceObjects();
	void SetupRenderStates();

	void SaveState(IDirect3DDevice9* pDevice);
	void RestoreState(IDirect3DDevice9* pDevice);

	Color Fill();
	void Fill(Color col);
	bool UsingFill();
	void NoFill();

	Color Stroke();
	void Stroke(Color col);
	int StrokeWeight();
	void StrokeWeight(int weight);
	bool UsingStroke();
	void NoStroke();

	void Clip(Vec2 pos, Vec2 size);
	void Clip(RECT clip);
	RECT Clip();

	void PushStyle();
	void PopStyle();
	void ResetStyle();

	void Rect(Vec2 pos, Vec2 size);
	void Ellipse(Vec2 pos, Vec2 size);
	void Line(Vec2 a, Vec2 b);
	void Triangle(Vec2* vertices);
	void Poly(Vec2* vertices, int count);
	void Text(Vec2 pos, unsigned int font, unsigned long alignment, const char * msg, ...);
	void TextPlain(Vec2 pos, unsigned int font, unsigned long alignment, const char * msg);
	SIZE TextSize(unsigned int font, const char * msg, ...);
	SIZE TextSizePlain(unsigned int font, const char * msg);

	static RECT DEFAULT_CLIP;
private:
	Drawing();
	~Drawing();

	Drawing(const Drawing& drawing) = delete;
	Drawing& operator=(const Drawing& drawing) = delete;

	LPDIRECT3DDEVICE9 pDevice;
	D3DVIEWPORT9 pViewport;

	IDirect3DVertexDeclaration9* vertDec;
	IDirect3DVertexShader9* vertShader;
	DWORD dwOld_D3DRS_COLORWRITEENABLE;

	std::vector<std::unique_ptr<CD3DFont>> fonts;

	std::vector<Style> styleStack;

	Style style;
};
