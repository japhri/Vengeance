#include "Drawing.h"
#include <Windows.h>
#include "mrc.hpp"

struct Vertex
{
	float x, y, z, rhw;
	DWORD color;

	Vertex() : x(0.0f), y(0.0f), z(1.0f), rhw(1.0f), color(0) {}
	Vertex(float x_, float y_, float z_, float rhw_, DWORD color_) : x(x_), y(y_), z(z_), rhw(rhw_), color(color_) {}
	Vertex(Vec2 pos, float rhw_, DWORD color_) : x(pos.x), y(pos.y), z(1.0f), rhw(rhw_), color(color_) {}
};

RECT Drawing::DEFAULT_CLIP = { LONG_MIN, LONG_MIN, LONG_MAX, LONG_MAX };

Drawing::Drawing() : pDevice(nullptr) {}

Drawing::~Drawing() {};

Drawing& Drawing::GetInstance()
{
	static Drawing drawing;
	return drawing;
}

void Drawing::InitDeviceObjects(LPDIRECT3DDEVICE9 pDevice)
{
	this->pDevice = pDevice;
	this->pDevice->GetViewport(&(this->pViewport));

	this->fonts.push_back(std::make_unique<CD3DFont>(TEXT("Mont-HeavyDEMO"), g_UIStyle.titleFontSize / 2, 650));
	this->fonts.push_back(std::make_unique<CD3DFont>(TEXT("Mont-HeavyDEMO"), g_UIStyle.textFontSize / 2, 650));
	//this->fonts.push_back(std::make_unique<CD3DFont>(TEXT("Tahoma"), g_UIStyle.titleFontSize, FW_MEDIUM));
	//this->fonts.push_back(std::make_unique<CD3DFont>(TEXT("Tahoma"), g_UIStyle.textFontSize, FW_MEDIUM));

	for (unsigned i = 0; i < this->fonts.size(); i++)
	{
		std::unique_ptr<CD3DFont>& font = this->fonts[i];
		font->InitDeviceObjects(pDevice);
		font->RestoreDeviceObjects();
	}
}

void Drawing::RestoreDeviceObjects(LPDIRECT3DDEVICE9 pDevice)
{
	this->pDevice = pDevice;
	this->pDevice->GetViewport(&(this->pViewport));

	for (unsigned i = 0; i < this->fonts.size(); i++)
	{
		std::unique_ptr<CD3DFont>& font = this->fonts[i];
		font->InitDeviceObjects(pDevice);
		font->RestoreDeviceObjects();
	}
}

void Drawing::InvalidateDeviceObjects()
{
	this->pDevice = nullptr;

	for (unsigned i = 0; i < this->fonts.size(); i++)
	{
		std::unique_ptr<CD3DFont>& font = this->fonts[i];
		font->InvalidateDeviceObjects();
	}
}

void Drawing::SetupRenderStates()
{
	this->pDevice->SetVertexShader(nullptr);
	this->pDevice->SetPixelShader(nullptr);
	this->pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	this->pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	this->pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	this->pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	this->pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	this->pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	this->pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	this->pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	this->pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	this->pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

	this->pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	this->pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	this->pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	this->pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	this->pDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
	this->pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	this->pDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

	this->pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);
	this->pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN |
		D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
}

void Drawing::SaveState(IDirect3DDevice9* pDevice)
{
	pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
	pDevice->GetVertexDeclaration(&vertDec);
	pDevice->GetVertexShader(&vertShader);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_SRGBTEXTURE, NULL);
}

void Drawing::RestoreState(IDirect3DDevice9* pDevice) // not restoring everything. Because it's not needed.
{
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, true);
	pDevice->SetVertexDeclaration(vertDec);
	pDevice->SetVertexShader(vertShader);
}

Color Drawing::Fill()
{
	return this->style.fill;
}

void Drawing::Fill(Color col)
{
	this->style.useFill = true;
	this->style.fill = col;
}

bool Drawing::UsingFill()
{
	return this->style.useFill;
}

void Drawing::NoFill()
{
	this->style.useFill = false;
}

Color Drawing::Stroke()
{
	return this->style.stroke;
}

void Drawing::Stroke(Color col)
{
	this->style.useStroke = true;
	this->style.stroke = col;
}

int Drawing::StrokeWeight()
{
	return this->style.strokeWeight;
}

void Drawing::StrokeWeight(int weight)
{
	this->style.strokeWeight = weight;
}

bool Drawing::UsingStroke()
{
	return this->style.useStroke;
}

void Drawing::NoStroke()
{
	this->style.useStroke = false;
}

void Drawing::Clip(Vec2 pos, Vec2 size)
{
	this->style.clipRect = { static_cast<LONG>(pos.x), static_cast<LONG>(pos.y), static_cast<LONG>(pos.x + size.x), static_cast<LONG>(pos.y + size.y) };
}

void Drawing::Clip(RECT clip)
{
	this->style.clipRect = clip;
}

RECT Drawing::Clip()
{
	return this->style.clipRect;
}

void Drawing::PushStyle()
{
	this->styleStack.push_back(this->style);
}

void Drawing::PopStyle()
{
	if (this->styleStack.size() <= 0)
	{
		this->ResetStyle();
		return;
	}

	this->style = this->styleStack.back();
	this->styleStack.pop_back();
}

void Drawing::ResetStyle()
{
	this->style.useFill = false;
	this->style.fill = Color(0, 0, 0, 0);

	this->style.useStroke = false;
	this->style.stroke = Color(0, 0, 0, 0);
	this->style.strokeWeight = 1;

	this->style.clipRect = { LONG_MIN, LONG_MIN, LONG_MAX, LONG_MAX };

	this->styleStack.clear();
}

void Drawing::Rect(Vec2 pos, Vec2 size)
{
	DWORD wasAntiAliased = 0;
	this->pDevice->GetRenderState(D3DRS_ANTIALIASEDLINEENABLE, &wasAntiAliased);
	RECT oldClip;
	this->pDevice->GetScissorRect(&oldClip);
	this->pDevice->SetScissorRect(&this->style.clipRect);

	if (this->style.useFill)
	{
		D3DCOLOR dwFillColor = COL2DWORD(this->style.fill);
		Vertex vert[4] =
		{
			{ pos.x, pos.y, 0.0f, 1.0f, dwFillColor },
			{ pos.x + size.x, pos.y, 0.0f, 1.0f, dwFillColor },
			{ pos.x, pos.y + size.y, 0.0f, 1.0f, dwFillColor },
			{ pos.x + size.x, pos.y + size.y, 0.0f, 1.0f, dwFillColor }
		};

		this->pDevice->SetTexture(0, nullptr);
		this->pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vert, sizeof(Vertex));
	}

	if (this->style.useStroke)
	{
		D3DCOLOR dwStrokeColor = COL2DWORD(this->style.stroke);
		Vertex vert[5] =
		{
			{ pos.x, pos.y, 1.0f, 1.0f, dwStrokeColor },
			{ pos.x + size.x, pos.y, 1.0f, 1.0f, dwStrokeColor },
			{ pos.x + size.x, pos.y + size.y, 1.0f, 1.0f, dwStrokeColor },
			{ pos.x, pos.y + size.y, 1.0f, 1.0f, dwStrokeColor },
			{ pos.x, pos.y, 1.0f, 1.0f, dwStrokeColor }
		};

		this->pDevice->SetTexture(0, nullptr);
		this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
		this->pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &vert, sizeof(Vertex));
	}

	this->pDevice->SetScissorRect(&oldClip);
	this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, wasAntiAliased);
}

void Drawing::Ellipse(Vec2 pos, Vec2 size)
{
	static const int steps = 50;
	static Vec2 points[steps];
	static bool initialized = false;

	DWORD wasAntiAliased = 0;
	this->pDevice->GetRenderState(D3DRS_ANTIALIASEDLINEENABLE, &wasAntiAliased);
	RECT oldClip;
	this->pDevice->GetScissorRect(&oldClip);
	this->pDevice->SetScissorRect(&this->style.clipRect);

	if (!initialized)
	{
		for (int i = 0; i < steps; i++)
		{
			float a = static_cast<float>(i) / static_cast<float>(steps) * 2.0f * static_cast<float>(M_PI);
			points[i] = Vec2(cos(a), sin(a));
		}

		initialized = true;
	}

	if (this->style.useFill)
	{
		D3DCOLOR dwFillColor = COL2DWORD(this->style.fill);
		Vertex vert[steps];

		for (int i = 0; i < steps; i++)
		{
			vert[i] = Vertex(points[i].x * size.x / 2.0f + pos.x, points[i].y * size.y / 2.0f + pos.y, 1.0f, 1.0f, dwFillColor);
		}

		this->pDevice->SetTexture(0, nullptr);
		this->pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, steps - 2, &vert, sizeof(Vertex));
	}

	if (this->style.useStroke)
	{
		D3DCOLOR dwStrokeColor = COL2DWORD(this->style.stroke);
		Vertex vert[steps];

		for (int i = 0; i < steps; i++)
		{
			vert[i] = Vertex(points[i].x * size.x / 2.0f + pos.x, points[i].y * size.y / 2.0f + pos.y, 1.0f, 1.0f, dwStrokeColor);
		}

		this->pDevice->SetTexture(0, nullptr);
		this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
		this->pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, steps - 1, &vert, sizeof(Vertex));
	}

	this->pDevice->SetScissorRect(&oldClip);
	this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, wasAntiAliased);
}

void Drawing::Line(Vec2 a, Vec2 b)
{
	DWORD wasAntiAliased = 0;
	this->pDevice->GetRenderState(D3DRS_ANTIALIASEDLINEENABLE, &wasAntiAliased);
	RECT oldClip;
	this->pDevice->GetScissorRect(&oldClip);
	this->pDevice->SetScissorRect(&this->style.clipRect);

	if (this->style.useStroke)
	{
		D3DCOLOR dwStrokeColor = COL2DWORD(this->style.stroke);
		Vertex vert[5] =
		{
			{ a.x, a.y, 1.0f, 1.0f, dwStrokeColor },
			{ b.x, b.y, 1.0f, 1.0f, dwStrokeColor },
		};

		this->pDevice->SetTexture(0, nullptr);
		this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
		this->pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 2, &vert, sizeof(Vertex));
	}

	this->pDevice->SetScissorRect(&oldClip);
	this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, wasAntiAliased);
}

void Drawing::Triangle(Vec2* vertices)
{
	DWORD wasAntiAliased = 0;
	this->pDevice->GetRenderState(D3DRS_ANTIALIASEDLINEENABLE, &wasAntiAliased);
	RECT oldClip;
	this->pDevice->GetScissorRect(&oldClip);
	this->pDevice->SetScissorRect(&this->style.clipRect);

	if (this->style.useFill)
	{
		D3DCOLOR dwFillColor = COL2DWORD(this->style.fill);
		Vertex vert[3] = 
		{
			Vertex(vertices[0].x, vertices[0].y, 1.0f, 1.0f, dwFillColor),
			Vertex(vertices[1].x, vertices[1].y, 1.0f, 1.0f, dwFillColor),
			Vertex(vertices[2].x, vertices[2].y, 1.0f, 1.0f, dwFillColor)
		};

		this->pDevice->SetTexture(0, nullptr);
		this->pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, &vert, sizeof(Vertex));
	}

	if (this->style.useStroke)
	{
		D3DCOLOR dwStrokeColor = COL2DWORD(this->style.stroke);
		
		Vertex vert[4] =
		{
			Vertex(vertices[0].x, vertices[0].y, 1.0f, 1.0f, dwStrokeColor),
			Vertex(vertices[1].x, vertices[1].y, 1.0f, 1.0f, dwStrokeColor),
			Vertex(vertices[2].x, vertices[2].y, 1.0f, 1.0f, dwStrokeColor),
			Vertex(vertices[0].x, vertices[0].y, 1.0f, 1.0f, dwStrokeColor)
		};

		this->pDevice->SetTexture(0, nullptr);
		this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
		this->pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 3, &vert, sizeof(Vertex));
	}

	this->pDevice->SetScissorRect(&oldClip);
	this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, wasAntiAliased);
}

void Drawing::Poly(Vec2* vertices, int count)
{
	DWORD wasAntiAliased = 0;
	this->pDevice->GetRenderState(D3DRS_ANTIALIASEDLINEENABLE, &wasAntiAliased);
	RECT oldClip;
	this->pDevice->GetScissorRect(&oldClip);
	this->pDevice->SetScissorRect(&this->style.clipRect);

	if (this->style.useFill)
	{
		D3DCOLOR dwFillColor = COL2DWORD(this->style.fill);
		Vertex* vert = new Vertex[count];

		for (int i = 0; i < count; i++)
		{
			vert[i] = Vertex(vertices[i].x, vertices[i].y, 1.0f, 1.0f, dwFillColor);
		}

		this->pDevice->SetTexture(0, nullptr);
		this->pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, count / 3, &vert, sizeof(Vertex));

		delete[] vert;
	}

	if (this->style.useStroke)
	{
		D3DCOLOR dwStrokeColor = COL2DWORD(this->style.stroke);
		Vertex* vert = new Vertex[count];

		for (int i = 0; i < count; i++)
		{
			vert[i] = Vertex(vertices[i].x, vertices[i].y, 1.0f, 1.0f, dwStrokeColor);
		}

		this->pDevice->SetTexture(0, nullptr);
		this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
		this->pDevice->DrawPrimitiveUP(D3DPT_LINELIST, count / 2, &vert, sizeof(Vertex));

		delete[] vert;
	}

	this->pDevice->SetScissorRect(&oldClip);
	this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, wasAntiAliased);
}

void Drawing::Text(Vec2 pos, unsigned int font, unsigned long alignment, const char * msg, ...)
{
	RECT oldClip;
	this->pDevice->GetScissorRect(&oldClip);
	this->pDevice->SetScissorRect(&this->style.clipRect);

	if (this->style.useFill)
	{
		va_list va_alist;
		char buf[1024];
		va_start(va_alist, msg);
		_vsnprintf(buf, sizeof(buf), msg, va_alist);
		va_end(va_alist);

		SIZE sz;
		this->fonts[font]->GetTextExtent(buf, &sz);

		if (alignment & FONT_RIGHT)
			pos.x -= static_cast<float>(sz.cx);
		if (alignment & FONT_CENTER)
			pos.x -= static_cast<float>(sz.cx / 2);

		pos.y -= static_cast<float>(sz.cy / 2 - 1);

		this->fonts[font]->DrawString(pos.x, pos.y, COL2DWORD(this->style.fill), buf, CD3DFONT_FILTERED);
	}

	this->pDevice->SetScissorRect(&oldClip);
}

void Drawing::TextPlain(Vec2 pos, unsigned int font, unsigned long alignment, const char * msg)
{
	RECT oldClip;
	this->pDevice->GetScissorRect(&oldClip);
	this->pDevice->SetScissorRect(&this->style.clipRect);

	if (this->style.useFill)
	{
		SIZE sz;
		this->fonts[font]->GetTextExtent(msg, &sz);

		if (alignment & FONT_RIGHT)
			pos.x -= static_cast<float>(sz.cx);
		if (alignment & FONT_CENTER)
			pos.x -= static_cast<float>(sz.cx / 2);

		pos.y -= static_cast<float>(sz.cy / 2 - 1);

		this->fonts[font]->DrawString(pos.x, pos.y, COL2DWORD(this->style.fill), msg, CD3DFONT_FILTERED);
	}

	this->pDevice->SetScissorRect(&oldClip);
}

SIZE Drawing::TextSize(unsigned int font, const char * msg, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);

	SIZE sz;
	this->fonts[font]->GetTextExtent(buf, &sz);
	return sz;
}

SIZE Drawing::TextSizePlain(unsigned int font, const char * msg)
{
	SIZE sz;
	this->fonts[font]->GetTextExtent(msg, &sz);
	return sz;
}
