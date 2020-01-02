#include <Windows.h>
#include <math.h>
#include "Drawing.h"
#include "mrc.hpp"
#include "Variables.h"

void UIStyle::UpdateFont()
{
	/*this->titleFont = G_Surface->CreateFont_();
	this->textFont = G_Surface->CreateFont_();
	G_Surface->SetFontGlyphSet(this->titleFont, "Mont-HeavyDEMO", titleFontSize, 650, 0, 0, FONTFLAG_ANTIALIAS);
	G_Surface->SetFontGlyphSet(this->textFont, "Mont-HeavyDEMO", textFontSize, 650, 0, 0, FONTFLAG_ANTIALIAS);*/

	this->titleFont = 0;
	this->textFont = 1;
}

UIStyle g_UIStyle = UIStyle();

namespace UIDrawing
{
	Drawing& drawing = Drawing::GetInstance();

	void FillRGBA(Vec2 pos, Vec2 size, Color col)
	{
		drawing.PushStyle();
		drawing.NoStroke();
		drawing.Fill(col);
		drawing.Rect(pos, size);
		drawing.PopStyle();
		//G_Surface->DrawSetColor(col.r(), col.g(), col.b(), col.a());
		//G_Surface->DrawFilledRect(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(pos.x + size.x), static_cast<int>(pos.y + size.y));
	}

	void StrokeRGBA(Vec2 pos, Vec2 size, Color col)
	{
		drawing.PushStyle();
		drawing.Stroke(col);
		drawing.NoFill();
		drawing.Rect(pos, size);
		drawing.PopStyle();
		//G_Surface->DrawSetColor(col.r(), col.g(), col.b(), col.a());
		//G_Surface->DrawOutlinedRect(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(pos.x + size.x), static_cast<int>(pos.y + size.y));
	}

	void LineRGBA(Vec2 start, Vec2 end, Color col)
	{
		drawing.PushStyle();
		drawing.Stroke(col);
		drawing.NoFill();
		drawing.Line(start, end);
		drawing.PopStyle();
		//G_Surface->DrawSetColor(col.r(), col.g(), col.b(), col.a());
		//G_Surface->DrawLine(static_cast<int>(start.x), static_cast<int>(start.y), static_cast<int>(end.x), static_cast<int>(end.y));
	}

	void TextRGBA(Vec2 pos, Color col, unsigned int font, unsigned long alignment, const char * msg, ...)
	{
		va_list va_alist;
		char buf[1024];
		va_start(va_alist, msg);
		_vsnprintf(buf, sizeof(buf), msg, va_alist);
		va_end(va_alist);
		/*wchar_t wbuf[1024];
		MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

		int r = 255, g = 255, b = 255, a = 255;
		col.GetColor(r, g, b, a);

		int width, height;
		G_Surface->GetTextSize(font, wbuf, width, height);
		
		if (alignment & FONT_RIGHT)
			pos.x -= width;
		if (alignment & FONT_CENTER)
			pos.x -= width / 2;

		G_Surface->DrawSetTextFont(font);
		G_Surface->DrawSetTextColor(r, g, b, a);
		G_Surface->DrawSetTextPos(static_cast<int>(pos.x), static_cast<int>(pos.y - height / 2));
		G_Surface->DrawPrintText(wbuf, wcslen(wbuf));*/

		drawing.PushStyle();
		drawing.NoStroke();
		drawing.Fill(col);
		drawing.TextPlain(pos, font, alignment, buf);
		drawing.PopStyle();
	}

	void PolyRGBA(Vec2* vertices, int count, Color col)
	{
		/*static int texture_id = G_Surface->CreateNewTextureID(true);
		static unsigned char buf[4] = { 255, 255, 255, 255 };
		G_Surface->DrawSetTextureRGBA(texture_id, buf, 1, 1, false, false);
		G_Surface->DrawSetColor(col);
		G_Surface->DrawSetTexture(texture_id);
		G_Surface->DrawTexturedPolygon(vertexCount, vertices);*/

		drawing.PushStyle();
		drawing.NoStroke();
		drawing.Fill(col);
		drawing.Poly(vertices, count);
		drawing.PopStyle();
	}

	void TriangleRGBA(Vec2 center, Vec2 size, float rotation, Color color)
	{
		Vec2 vertices[] = {
			RotateVector(Vec2(-size.x /2, size.y / 2), rotation) + center,
			RotateVector(Vec2(-size.x / 2, -size.y / 2), rotation) + center,
			RotateVector(Vec2(size.x / 2, 0), rotation) + center
		};

		//PolyRGBA(vertices, 3, color);

		drawing.PushStyle();
		drawing.NoStroke();
		drawing.Fill(color);
		drawing.Triangle(vertices);
		drawing.PopStyle();
	}

	Vec2 CartesianToPolar(Vec2 in)
	{
		return Vec2(atan2(in.y, in.x), sqrt(in.x * in.x + in.y * in.y));
	}

	Vec2 PolarToCartesian(Vec2 in)
	{
		return Vec2(cos(in.x) * in.y, sin(in.x) * in.y);
	}

	Vec2 RotateVector(Vec2 in, float rotation)
	{
		Vec2 polar = CartesianToPolar(in);
		polar.x += rotation;
		return PolarToCartesian(polar);
	}

	/*Vector2D RotateVectorT(Vec2 in, float rotation)
	{
		Vec2 polar = CartesianToPolar(in);
		polar.x += rotation;
		Vec2 cartesian = PolarToCartesian(polar);
		return Vector2D(cartesian.x, cartesian.y);
	}*/

	Vec2 TextSize(const char* input, unsigned long font)
	{
		/*int iWide = 0;
		int iTall = 0;
		int iBufSize = MultiByteToWideChar(CP_UTF8, 0x0, input, -1, NULL, 0);

		wchar_t* pszUnicode = new wchar_t[iBufSize];

		MultiByteToWideChar(CP_UTF8, 0x0, input, -1, pszUnicode, iBufSize);

		G_Surface->GetTextSize(font, pszUnicode, iWide, iTall);

		delete[] pszUnicode;

		return Vec2(iWide, iTall);*/
		
		SIZE sz = drawing.TextSizePlain(font, input);
		return Vec2(sz.cx, sz.cy);
	}

	int TextWidth(const char* input, unsigned long font)
	{
		/*int iWide = 0;
		int iTall = 0;
		int iBufSize = MultiByteToWideChar(CP_UTF8, 0x0, input, -1, NULL, 0);

		wchar_t* pszUnicode = new wchar_t[iBufSize];

		MultiByteToWideChar(CP_UTF8, 0x0, input, -1, pszUnicode, iBufSize);

		G_Surface->GetTextSize(font, pszUnicode, iWide, iTall);

		delete[] pszUnicode;

		return iWide;*/

		SIZE sz = drawing.TextSizePlain(font, input);
		return sz.cx;
	}

	int TextHeight(const char* input, unsigned long font)
	{
		/*int iWide = 0;
		int iTall = 0;
		int iBufSize = MultiByteToWideChar(CP_UTF8, 0x0, input, -1, NULL, 0);

		wchar_t* pszUnicode = new wchar_t[iBufSize];

		MultiByteToWideChar(CP_UTF8, 0x0, input, -1, pszUnicode, iBufSize);

		G_Surface->GetTextSize(font, pszUnicode, iWide, iTall);

		delete[] pszUnicode;

		return iTall;*/

		SIZE sz = drawing.TextSizePlain(font, input);
		return sz.cy;
	}

	int CharWidth(char c, unsigned long font)
	{
		/*int iWide = 0;
		int iTall = 0;
		char input[2] = { c, '\0' };
		int iBufSize = MultiByteToWideChar(CP_UTF8, 0x0, input, -1, NULL, 0);

		wchar_t* pszUnicode = new wchar_t[iBufSize];

		MultiByteToWideChar(CP_UTF8, 0x0, input, -1, pszUnicode, iBufSize);

		G_Surface->GetTextSize(font, pszUnicode, iWide, iTall);

		delete[] pszUnicode;

		return iWide;*/

		char input[2] = { c, '\0' };
		SIZE sz = drawing.TextSizePlain(font, input);
		return sz.cx;
	}
}

/********************************

    UIElement

********************************/

UIElement::UIElement()
{
	this->pos = Vec2(0.0f, 0.0f);
	this->size = Vec2(0.0f, 0.0f);
	this->bottom = this->pos + Vec2(0, this->size.y + g_UIStyle.margin * 2);
	this->label = "";
	this->SetVisible(true);
}

UIElement::UIElement(Vec2 pos, Vec2 size)
{
	this->pos = pos;
	this->size = size;
	this->bottom = this->pos + Vec2(0, this->size.y + g_UIStyle.margin * 2);
	this->label = "";
	this->SetVisible(true);
}

UIElement::UIElement(Vec2 pos, Vec2 size, std::string label)
{
	this->pos = pos;
	this->size = size;
	this->bottom = this->pos + Vec2(0, this->size.y + g_UIStyle.margin * 2);
	this->label = label;
	this->SetVisible(true);
}

UIElement::~UIElement() {}

void UIElement::Draw(Vec2 mousePos, Vec2 offset) {}

void UIElement::SetLabel(std::string newLabel)
{
	this->label = newLabel;
}

void UIElement::SetVisible(bool visible) {
	this->visible = visible;
}

bool UIElement::OnClick(Vec2 mousePos, Vec2 offset) { return false;  }

void UIElement::OnKeyPress(unsigned char key) {}

/********************************

    UILabel

********************************/

UILabel::UILabel(Vec2 pos, std::string label)
{
	this->pos = pos;
	this->size = Vec2(g_UIStyle.margin * 2, g_UIStyle.textFontSize);
	this->bottom = this->pos + Vec2(0, this->size.y + g_UIStyle.margin * 2);
	this->label = label;
	this->SetVisible(true);
}

UILabel::~UILabel()
{

}

void UILabel::Draw(Vec2 mousePos, Vec2 offset)
{
	this->size = UIDrawing::TextSize(label.c_str(), g_UIStyle.textFont) + Vec2(g_UIStyle.margin * 2, 0);
	UIDrawing::TextRGBA(offset + this->pos + Vec2(g_UIStyle.margin, this->size.y / 2), g_UIStyle.textColor, g_UIStyle.textFont, FONT_LEFT, "%s", this->label.c_str());
}

/********************************

    UICheckbox

********************************/

UICheckbox::UICheckbox() : UIElement() {}

UICheckbox::UICheckbox(Vec2 pos, std::string label, bool *value) : UIElement(pos, Vec2(20, 20), label)
{
	this->value = value;
}

UICheckbox::~UICheckbox() {}

void UICheckbox::Draw(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible || !this->value) return;

	int margin = 4;
	Vec2 marginVec = Vec2(margin, margin);

	int textWidth = UIDrawing::TextWidth(this->label.c_str(), g_UIStyle.textFont);

	bool hovered = g_Utils->InBox(offset + this->pos, this->size + Vec2(g_UIStyle.margin + textWidth, 0), mousePos);
	bool pressed = hovered && g_Utils->KeyDown(VK_LBUTTON);

	Color checkboxBackgroundCol = g_UIStyle.checkboxBackgroundColor;
	Color checkboxCol = g_UIStyle.checkboxColor;

	if (pressed)
	{
		checkboxBackgroundCol = g_UIStyle.checkboxBackgroundPressedColor;
		checkboxCol = g_UIStyle.checkboxPressedColor;
	}
	else if (hovered)
	{
		checkboxBackgroundCol = g_UIStyle.checkboxBackgroundHoverColor;
		checkboxCol = g_UIStyle.checkboxHoverColor;
	}

	UIDrawing::FillRGBA(offset + this->pos + marginVec, this->size - marginVec * 2, checkboxBackgroundCol);

	if (*(this->value))
		UIDrawing::FillRGBA(offset + this->pos + marginVec, this->size - marginVec * 2, checkboxCol);

	UIDrawing::TextRGBA(offset + this->pos + Vec2(this->size.x + margin, this->size.y / 2), g_UIStyle.textColor, g_UIStyle.textFont, FONT_LEFT, "%s", this->label.c_str());
}

bool UICheckbox::OnClick(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible || !this->value) return false;

	int textWidth = UIDrawing::TextWidth(this->label.c_str(), g_UIStyle.textFont);

	if (g_Utils->InBox(offset + this->pos, this->size + Vec2(g_UIStyle.margin + textWidth, 0), mousePos))
	{
		*(this->value) = !*(this->value);
		return true;
	}

	return false;
}

void UICheckbox::OnKeyPress(unsigned char key) {}

/********************************

    UISingleDropdown

********************************/

UISingleDropdown::UISingleDropdown() : UIElement::UIElement() {}

UISingleDropdown::UISingleDropdown(Vec2 pos, Vec2 size, std::string label, int *value, char **elementNames, int elementCount) : UIElement::UIElement(pos, size, label)
{
	this->value = value;
	this->elementNames = elementNames;
	this->elementCount = elementCount;
}

UISingleDropdown::~UISingleDropdown() {}

void UISingleDropdown::Draw(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible || !this->value) return;

	Drawing& drawing = Drawing::GetInstance();

	drawing.PushStyle();

	if (this->opened)
		drawing.Clip(Drawing::DEFAULT_CLIP);

	int margin = g_UIStyle.margin;
	Vec2 marginVec = Vec2(margin, margin);

	Vec2 halfHeight = Vec2(this->size.x, this->size.y / 2);

	int labelHeight = static_cast<int>(halfHeight.y);// UIDrawing::TextHeight(this->label.c_str(), g_UIStyle.textFont);

	bool mousePressed = g_Utils->KeyDown(VK_LBUTTON);

	bool hovered = g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y), halfHeight, mousePos);
	bool pressed = hovered && mousePressed;

	if (this->opened && !hovered && !g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y), halfHeight * Vec2(1, this->elementCount + 1), mousePos) && mousePressed && !this->wasMousePressed)
	{
		this->opened = false;
	}

	UIDrawing::TextRGBA(offset + this->pos + Vec2(margin * 2, labelHeight * 0.5f), g_UIStyle.textColor, g_UIStyle.textFont, FONT_LEFT, "%s", this->label.c_str());

	Color dropdownCol = g_UIStyle.dropdownSpecialColor;
	Color triangleCol = g_UIStyle.dropdownColor;

	if (pressed)
	{
		dropdownCol = g_UIStyle.dropdownSpecialPressedColor;
		triangleCol = g_UIStyle.dropdownPressedColor;
	}
	else if (this->opened)
	{
		dropdownCol = g_UIStyle.dropdownSpecialSelectedColor;
		triangleCol = g_UIStyle.dropdownSelectedColor;
	}
	else if (hovered)
	{
		dropdownCol = g_UIStyle.dropdownSpecialHoverColor;
		triangleCol = g_UIStyle.dropdownHoverColor;
	}

	UIDrawing::FillRGBA(offset + this->pos + Vec2(0, halfHeight.y), halfHeight, dropdownCol);

	UIDrawing::TextRGBA(offset + this->pos + Vec2(margin * 2, halfHeight.y * 1.5f), g_UIStyle.textColor, g_UIStyle.textFont, FONT_LEFT, "%s", this->elementNames[*(this->value)]);

	int triangleSize = g_UIStyle.dropdownTriangleSize;

	UIDrawing::TriangleRGBA(offset + this->pos + Vec2(this->size.x - labelHeight / 2, halfHeight.y + labelHeight / 2), Vec2(triangleSize, triangleSize), PI / 2.0f, triangleCol);

	if (this->opened)
	{
		UIDrawing::FillRGBA(offset + this->pos + Vec2(0, halfHeight.y * 2), Vec2(size.x, margin), g_UIStyle.edgeColor);

		for (int i = 0; i < this->elementCount; i++)
		{
			bool selected = *(this->value) == i;
			Color dropdownItemCol = selected ? g_UIStyle.dropdownSpecialColor : g_UIStyle.dropdownColor;

			bool itemHovered = g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y * (i + 2) + g_UIStyle.margin), halfHeight, mousePos);
			bool itemPressed = itemHovered && g_Utils->KeyDown(VK_LBUTTON);

			if (itemPressed)
				dropdownItemCol = selected ? g_UIStyle.dropdownSpecialPressedColor : g_UIStyle.dropdownPressedColor;
			else if (itemHovered)
				dropdownItemCol = selected ? g_UIStyle.dropdownSpecialHoverColor : g_UIStyle.dropdownHoverColor;

			UIDrawing::FillRGBA(offset + this->pos + Vec2(0, halfHeight.y * (i + 2) + margin), halfHeight, dropdownItemCol);

			UIDrawing::TextRGBA(offset + this->pos + Vec2(margin * 2, halfHeight.y * (i + 2.5f) + margin), g_UIStyle.textColor, g_UIStyle.textFont, FONT_LEFT, "%s", this->elementNames[i]);
		}
	}

	drawing.PopStyle();

	this->wasMousePressed = g_Utils->KeyDown(VK_LBUTTON);
}

bool UISingleDropdown::OnClick(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible || !this->value) return false;

	Vec2 halfHeight = Vec2(this->size.x, this->size.y / 2);

	bool onMainBox = g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y), halfHeight, mousePos);

	if (this->opened)
	{
		if (onMainBox || g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y), halfHeight * Vec2(1, this->elementCount + 2 + g_UIStyle.margin), mousePos))
		{
			this->opened = false;
			for (int i = 0; i < this->elementCount; i++)
			{
				if (g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y * (i + 2) + g_UIStyle.margin), halfHeight, mousePos))
				{
					*(this->value) = i;
				}
			}
			return true;
		}
	}
	else if (onMainBox)
	{
		this->opened = true;
		return true;
	}

	return false;
}

void UISingleDropdown::OnKeyPress(unsigned char key)
{
	if (!this->visible) return;

	if (this->opened && key == VK_ESCAPE)
	{
		this->opened = false;
	}
}

/********************************

    UIMultiDropdown

********************************/

UIMultiDropdown::UIMultiDropdown() : UIElement::UIElement() {}

UIMultiDropdown::UIMultiDropdown(Vec2 pos, Vec2 size, std::string label, bool *value, char **elementNames, int elementCount) : UIElement::UIElement(pos, size, label)
{
	this->values = value;
	this->elementNames = elementNames;
	this->elementCount = elementCount;
}

UIMultiDropdown::~UIMultiDropdown() {}

void UIMultiDropdown::Draw(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible || !this->values) return;

	Drawing& drawing = Drawing::GetInstance();

	drawing.PushStyle();

	if (this->opened)
		drawing.Clip(Drawing::DEFAULT_CLIP);

	int margin = g_UIStyle.margin;
	Vec2 marginVec = Vec2(margin, margin);

	Vec2 halfHeight = Vec2(this->size.x, this->size.y / 2);

	int labelHeight = static_cast<int>(halfHeight.y);// UIDrawing::TextHeight(this->label.c_str(), g_UIStyle.textFont);

	bool mousePressed = g_Utils->KeyDown(VK_LBUTTON);

	bool hovered = g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y), halfHeight, mousePos);
	bool pressed = hovered && mousePressed;

	if (this->opened && !hovered && !g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y), halfHeight * Vec2(1, this->elementCount + 1), mousePos) && mousePressed && !this->wasMousePressed)
	{
		this->opened = false;
	}

	UIDrawing::TextRGBA(offset + this->pos + Vec2(margin * 2, labelHeight * 0.5f), g_UIStyle.textColor, g_UIStyle.textFont, FONT_LEFT, "%s", this->label.c_str());

	Color dropdownCol = g_UIStyle.dropdownSpecialColor;
	Color triangleCol = g_UIStyle.dropdownColor;

	if (pressed)
	{
		dropdownCol = g_UIStyle.dropdownSpecialPressedColor;
		triangleCol = g_UIStyle.dropdownPressedColor;
	}
	else if (this->opened)
	{
		dropdownCol = g_UIStyle.dropdownSpecialSelectedColor;
		triangleCol = g_UIStyle.dropdownSelectedColor;
	}
	else if (hovered)
	{
		dropdownCol = g_UIStyle.dropdownSpecialHoverColor;
		triangleCol = g_UIStyle.dropdownHoverColor;
	}

	UIDrawing::FillRGBA(offset + this->pos + Vec2(0, halfHeight.y), halfHeight, dropdownCol);

	int totalSelectedCount = 0;

	for (int i = 0; i < this->elementCount; i++)
	{
		if (this->values[i])
			++totalSelectedCount;
	}

	std::string selectedList = "";
	int selectedCount = 0;
	bool addToList = true;
	int extraSelectedCount = 0;

	int maxSize = static_cast<int>(this->size.x - margin * 4 - labelHeight);

	for (int i = 0; i < this->elementCount; i++)
	{
		if (this->values[i])
		{
			++selectedCount;
			std::string newSelectedList = selectedList;
			if (selectedCount > 1)
				newSelectedList += ", ";
			newSelectedList += this->elementNames[i];
			std::string testStr = newSelectedList;

			if (selectedCount < totalSelectedCount)
			{
				testStr += " + " + std::to_string(totalSelectedCount - selectedCount);
			}

			if (addToList && UIDrawing::TextWidth(testStr.c_str(), g_UIStyle.textFont) < maxSize)
				selectedList = newSelectedList;
			else
			{
				addToList = false;
				++extraSelectedCount;
			}
		}
	}

	if (extraSelectedCount > 0)
		UIDrawing::TextRGBA(offset + this->pos + Vec2(margin * 2, halfHeight.y * 1.5f), g_UIStyle.textColor, g_UIStyle.textFont, FONT_LEFT, "%s + %i", selectedList.c_str(), extraSelectedCount);
	else
		UIDrawing::TextRGBA(offset + this->pos + Vec2(margin * 2, halfHeight.y * 1.5f), g_UIStyle.textColor, g_UIStyle.textFont, FONT_LEFT, "%s", selectedList.c_str());

	int triangleSize = g_UIStyle.dropdownTriangleSize;

	UIDrawing::TriangleRGBA(offset + this->pos + Vec2(this->size.x - labelHeight / 2, halfHeight.y + labelHeight / 2), Vec2(triangleSize, triangleSize), PI / 2.0f, triangleCol);

	if (this->opened)
	{
		UIDrawing::FillRGBA(offset + this->pos + Vec2(0, halfHeight.y * 2), Vec2(size.x, margin), g_UIStyle.edgeColor);

		for (int i = 0; i < this->elementCount; i++)
		{
			bool selected = this->values[i];
			Color dropdownItemCol = selected ? g_UIStyle.dropdownSpecialColor : g_UIStyle.dropdownColor;

			bool itemHovered = g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y * (i + 2) + g_UIStyle.margin), halfHeight, mousePos);
			bool itemPressed = itemHovered && g_Utils->KeyDown(VK_LBUTTON);

			if (itemPressed)
				dropdownItemCol = selected ? g_UIStyle.dropdownSpecialPressedColor : g_UIStyle.dropdownPressedColor;
			else if (itemHovered)
				dropdownItemCol = selected ? g_UIStyle.dropdownSpecialHoverColor : g_UIStyle.dropdownHoverColor;

			UIDrawing::FillRGBA(offset + this->pos + Vec2(0, halfHeight.y * (i + 2) + margin), halfHeight, dropdownItemCol);

			UIDrawing::TextRGBA(offset + this->pos + Vec2(margin * 2, halfHeight.y * (i + 2.5f) + margin), g_UIStyle.textColor, g_UIStyle.textFont, FONT_LEFT, "%s", this->elementNames[i]);
		}
	}

	drawing.PopStyle();

	this->wasMousePressed = g_Utils->KeyDown(VK_LBUTTON);
}

bool UIMultiDropdown::OnClick(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible || !this->values) return false;

	Vec2 halfHeight = Vec2(this->size.x, this->size.y / 2);

	bool onMainBox = g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y + g_UIStyle.margin), halfHeight, mousePos);

	if (this->opened)
	{
		if (g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y * 2 + g_UIStyle.margin), halfHeight * Vec2(1, this->elementCount + 2 + g_UIStyle.margin), mousePos))
		{
			for (int i = 0; i < this->elementCount; i++)
			{
				if (g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y * (i + 2) + g_UIStyle.margin), halfHeight, mousePos))
				{
					*(this->values + i) = !this->values[i];
				}
			}
			return true;
		}
		else if (onMainBox)
		{
			this->opened = false;
			return true;
		}
	}
	else if (onMainBox)
	{
		this->opened = true;
		return true;
	}

	return false;
}

void UIMultiDropdown::OnKeyPress(unsigned char key) {
	if (!this->visible) return;
	
	if (this->opened && key == VK_ESCAPE)
	{
		this->opened = false;
	}
}

/********************************

    UITextBox

********************************/

UITextBox::UITextBox() : UIElement() {}

UITextBox::UITextBox(Vec2 pos, Vec2 size, std::string label, char *str, unsigned maxStrLen) : UIElement(pos, size, label)
{
	this->str = str;
	this->maxStrLen = maxStrLen;
}

UITextBox::~UITextBox()
{

}

void UITextBox::Draw(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible || !this->str || this->maxStrLen <= 0) return;

	int margin = g_UIStyle.margin;
	Vec2 marginVec = Vec2(margin, margin);

	Vec2 halfHeight = Vec2(this->size.x, this->size.y / 2);

	int labelHeight = static_cast<int>(halfHeight.y);

	bool mousePressed = g_Utils->KeyDown(VK_LBUTTON);

	bool hovered = g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y), halfHeight, mousePos);
	bool pressed = hovered && mousePressed;

	UIDrawing::TextRGBA(offset + this->pos + Vec2(margin * 2, labelHeight * 0.5f), g_UIStyle.textColor, g_UIStyle.textFont, FONT_LEFT, "%s", this->label.c_str());

	Color textboxCol = g_UIStyle.textboxColor;

	if (pressed)
	{
		textboxCol = g_UIStyle.textboxPressedColor;
	}
	else if (this->selected)
	{
		textboxCol = g_UIStyle.textboxSelectedColor;
	}
	else if (hovered)
	{
		textboxCol = g_UIStyle.textboxHoverColor;
	}

	UIDrawing::FillRGBA(offset + this->pos + Vec2(0, halfHeight.y), halfHeight, textboxCol);

	// Find how many characters need to be skipped to offset this->textOffset pixels
	char buf[257] = { 0 };
	int strOffset = 0;
	/*for (strOffset = 0; strOffset < 256; strOffset++)
	{
		if (!this->str[strOffset]) break;

		buf[strOffset] = this->str[strOffset];
		buf[strOffset + 1] = '\0';

		if (UIDrawing::TextWidth(buf, g_UIStyle.textFont) > this->textOffset)
		{
			strOffset--;
			break;
		}
	}*/

	if (this->selected && hovered && mousePressed && !this->wasMousePressed)
	{
		this->dragging = true;
		this->caretStart = this->OffsetFromPos(mousePos.x, offset.x);
	}

	if (this->dragging)
	{
		if (!mousePressed)
		{
			this->dragging = false;
		}
		else
		{
			this->caretEnd = this->OffsetFromPos(mousePos.x, offset.x);
		}
	}

	if (!this->dragging && this->selected && !hovered && mousePressed && !this->wasMousePressed)
	{
		this->selected = false;
	}

	if (this->caretStart == this->caretEnd)
	{
		if (this->selected && (g_Utils->CurrentTimeMillis() % 1000 < 500))
		{
			unsigned i;
			for (i = 0; i < this->caretStart; i++)
			{
				if (!this->str[i]) break;

				buf[i] = this->str[i];
			}
			buf[i] = '\0';

			int caretPos = UIDrawing::TextWidth(buf, g_UIStyle.textFont);

			UIDrawing::LineRGBA(offset + this->pos + Vec2(caretPos + margin * 2, halfHeight.y + margin * 2), offset + this->pos + Vec2(caretPos + margin * 2, this->size.y - margin * 2), g_UIStyle.textColor);
		}
	}
	else
	{
		unsigned i;
		for (i = 0; i < this->caretStart; i++)
		{
			if (!this->str[i]) break;

			buf[i] = this->str[i];
		}
		buf[i] = '\0';

		int caretStartPos = UIDrawing::TextWidth(buf, g_UIStyle.textFont);

		for (i = 0; i < this->caretEnd; i++)
		{
			if (!this->str[i]) break;

			buf[i] = this->str[i];
		}
		buf[i] = '\0';

		int caretEndPos = UIDrawing::TextWidth(buf, g_UIStyle.textFont);
		
		if (caretEndPos < caretStartPos)
		{
			int temp = caretStartPos;
			caretStartPos = caretEndPos;
			caretEndPos = temp;
		}

		UIDrawing::FillRGBA(offset + this->pos + Vec2(caretStartPos + margin * 2, halfHeight.y), Vec2(caretEndPos - caretStartPos, halfHeight.y), this->selected ? g_UIStyle.textboxHighlightColor : g_UIStyle.textboxUnfocusedHighlightColor);
	}

	UIDrawing::TextRGBA(offset + this->pos + Vec2(margin * 2, halfHeight.y * 1.5f), g_UIStyle.textColor, g_UIStyle.textFont, FONT_LEFT, "%s", this->str + strOffset);

	this->wasMousePressed = mousePressed;
}

bool UITextBox::OnClick(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible || !this->str) return false;

	Vec2 halfHeight = Vec2(this->size.x, this->size.y / 2);

	bool onMainBox = g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y), halfHeight, mousePos);

	if (onMainBox)
	{
		this->caretEnd = this->OffsetFromPos(mousePos.x, offset.x);
		this->selected = true;

		return true;
	}

	return false;
}

void UITextBox::OnKeyPress(unsigned char key)
{
	if (!this->visible) return;

	if (this->selected)
	{
		unsigned lowestCaret = this->caretStart;
		unsigned highestCaret = this->caretEnd;

		if (this->caretEnd < this->caretStart)
		{
			lowestCaret = this->caretEnd;
			highestCaret = this->caretStart;
		}

		// LEFT ARROW
		if (key == VK_LEFT)
		{
			if (g_Utils->KeyDown(VK_SHIFT))
			{
				if (this->caretEnd > 0)
					this->caretEnd = this->caretEnd - 1;
				else
					this->caretEnd = 0;
			}
			else
			{
				if (this->caretStart != this->caretEnd)
					this->caretStart = this->caretEnd = lowestCaret;
				else if (lowestCaret > 0)
					this->caretStart = this->caretEnd = lowestCaret - 1;
				else
					this->caretStart = this->caretEnd = 0;
			}
			return;
		}

		// RIGHT ARROW
		if (key == VK_RIGHT)
		{
			if (g_Utils->KeyDown(VK_SHIFT))
			{
				if (this->caretEnd < this->maxStrLen)
					this->caretEnd = this->caretEnd + 1;
				else
					this->caretEnd = this->maxStrLen;
			}
			else
			{
				if (this->caretStart != this->caretEnd)
					this->caretStart = this->caretEnd = highestCaret;
				else if (highestCaret < this->maxStrLen)
					this->caretStart = this->caretEnd = highestCaret + 1;
				else
					this->caretStart = this->caretEnd = this->maxStrLen;
			}
			return;
		}

		// UP ARROW
		if (key == VK_UP)
		{
			this->caretStart = this->caretEnd = 0;
			return;
		}

		// DOWN ARROW
		if (key == VK_DOWN)
		{
			this->caretStart = this->caretEnd = strlen(this->str);
			return;
		}

		// CTRL+A
		if (key == 0x41 && g_Utils->KeyDown(VK_CONTROL))
		{
			this->caretStart = 0;
			this->caretEnd = strlen(this->str);
			return;
		}

		bool deleted = false;

		if (this->caretStart != this->caretEnd)
		{
			if ((key >= 32 && key <= 126) || key == VK_BACK || key == VK_DELETE)
			{
				for (unsigned i = 0; i < highestCaret - lowestCaret; i++)
				{
					for (unsigned j = lowestCaret; j < this->maxStrLen - 1; j++)
					{
						this->str[j] = this->str[j + 1];
					}
				}
				deleted = true;
				this->caretStart = this->caretEnd = lowestCaret;
			}
		}

		if (this->caretStart == this->caretEnd)
		{
			// BACKSPACE
			if (key == VK_BACK)
			{
				if (!deleted)
				{
					if (this->caretStart > 0)
					{
						unsigned i = this->caretStart;
						if (this->caretStart >= strlen(this->str))
							i = strlen(this->str) - 1;
						for (; i < this->maxStrLen - 1; i++)
						{
							this->str[i] = this->str[i + 1];
						}
						this->caretStart = --this->caretEnd;
					}
				}
				return;
			}

			// DEL
			if (key == VK_DELETE)
			{
				if (!deleted)
				{
					if (this->caretStart < this->maxStrLen - 1)
					{
						for (unsigned i = this->caretStart; i < this->maxStrLen - 1; i++)
						{
							this->str[i] = this->str[i + 1];
						}
					}
				}
				return;
			}

			if (this->caretStart < this->maxStrLen - 1)
			{
				if (key >= 32 && key <= 126 || key >= 0xBA && key <= 0xC0 || key >= 0xDB && key <= 0xDE)
				{
					for (unsigned i = this->maxStrLen - 1; i > this->caretStart; i--)
					{
						this->str[i] = this->str[i - 1];
					}

					bool caps = g_Utils->KeyDown(VK_SHIFT);
					if ((GetKeyState(VK_CAPITAL) & 0x1) == 0x1) caps = !caps;

					if (!caps)
					{
						if (key >= 65 && key <= 90) key = key - 'A' + 'a';
					}

					if (!g_Utils->KeyDown(VK_SHIFT))
					{
						switch (key)
						{
						case 0xBA:
							key = ';';
							break;
						case 0xBB:
							key = '=';
							break;
						case 0xBC:
							key = ',';
							break;
						case 0xBD:
							key = '-';
							break;
						case 0xBE:
							key = '.';
							break;
						case 0xBF:
							key = '/';
							break;
						case 0xC0:
							key = '`';
							break;
						case 0xDB:
							key = '[';
							break;
						case 0xDC:
							key = '\\';
							break;
						case 0xDD:
							key = ']';
							break;
						case 0xDE:
							key = '\'';
							break;
						}
					}
					else
					{
						switch (key)
						{
						case 0x30:
							key = ')';
							break;
						case 0x31:
							key = '!';
							break;
						case 0x32:
							key = '@';
							break;
						case 0x33:
							key = '#';
							break;
						case 0x34:
							key = '$';
							break;
						case 0x35:
							key = '%';
							break;
						case 0x36:
							key = '^';
							break;
						case 0x37:
							key = '&';
							break;
						case 0x38:
							key = '*';
							break;
						case 0x39:
							key = '(';
							break;
						case 0xBA:
							key = ':';
							break;
						case 0xBB:
							key = '+';
							break;
						case 0xBC:
							key = '<';
							break;
						case 0xBD:
							key = '_';
							break;
						case 0xBE:
							key = '>';
							break;
						case 0xBF:
							key = '?';
							break;
						case 0xC0:
							key = '~';
							break;
						case 0xDB:
							key = '{';
							break;
						case 0xDC:
							key = '|';
							break;
						case 0xDD:
							key = '}';
							break;
						case 0xDE:
							key = '"';
							break;
						}
					}

					this->str[this->caretStart] = key; 
					this->caretEnd = ++this->caretStart;
				}
			}
		}
	}
}

int UITextBox::OffsetFromPos(int pos, int offset)
{
	char buf[257];
	int i;
	for (i = 0; i < 256; i++)
	{
		if (!this->str[i]) break;

		buf[i] = this->str[i];
		buf[i + 1] = '\0';

		int widCutoff;
		int mousePosRelative = static_cast<int>(pos - this->pos.x - offset - g_UIStyle.margin * 2);

		if (!i)
		{
			widCutoff = UIDrawing::CharWidth(this->str[i], g_UIStyle.textFont) / 2;
		}
		else
		{
			widCutoff = UIDrawing::TextWidth(buf, g_UIStyle.textFont) - UIDrawing::CharWidth(this->str[i - 1], g_UIStyle.textFont) / 2;
		}

		//g_CVar->ConsolePrintf("TextWidth: %i, Mouse: %i, Offset: %i, Buf: %s\n", widCutoff, mousePosRelative, i, buf);
		if (widCutoff > mousePosRelative) break;
	}
	return i;
}

int UITextBox::OffsetFromPos(float pos, float offset)
{
	return OffsetFromPos(static_cast<int>(pos), static_cast<int>(offset));
}

/********************************

    UISliderFloat

********************************/

UISliderFloat::UISliderFloat() : UIElement() {}

UISliderFloat::UISliderFloat(Vec2 pos, Vec2 size, std::string label, float *value, float min, float max, std::string format) : UIElement(pos, size, label), dragging(false)
{
	this->value = value;
	this->min = min;
	this->max = max;
	this->format = format;
	this->initialValue = *value;
}

UISliderFloat::~UISliderFloat() {}

void UISliderFloat::Draw(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible || !this->value) return;

	int margin = g_UIStyle.margin;
	Vec2 marginVec = Vec2(margin, margin);

	Vec2 halfHeight = Vec2(this->size.x, this->size.y / 2);

	int labelHeight = static_cast<int>(halfHeight.y);// UIDrawing::TextHeight(this->label.c_str(), g_UIStyle.textFont);

	bool mousePressed = g_Utils->KeyDown(VK_LBUTTON);

	bool hovered = g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y), halfHeight, mousePos);
	bool pressed = hovered && mousePressed;

	if (hovered && g_Utils->KeyDown(VK_RBUTTON))
	{
		*value = initialValue;
	}

	if (!this->wasMousePressed && pressed && !dragging)
		dragging = true;

	if (!mousePressed && dragging)
		dragging = false;

	UIDrawing::TextRGBA(offset + this->pos + Vec2(margin * 2, labelHeight * 0.5f), g_UIStyle.textColor, g_UIStyle.textFont, FONT_LEFT, "%s", this->label.c_str());

	Color backgroundCol = g_UIStyle.sliderBackgroundColor;
	Color col = g_UIStyle.sliderColor;

	if (dragging || (hovered && g_Utils->KeyDown(VK_RBUTTON)))
	{
		backgroundCol = g_UIStyle.sliderBackgroundPressedColor;
		col = g_UIStyle.sliderPressedColor;
	}
	else if (hovered)
	{
		backgroundCol = g_UIStyle.sliderBackgroundHoverColor;
		col = g_UIStyle.sliderHoverColor;
	}

	if (dragging)
	{
		float x = max(0.0f, min(1.0f, (mousePos.x - offset.x) / size.x));
		*value = min + x * (max - min);
	}

	UIDrawing::FillRGBA(offset + this->pos + Vec2(0, halfHeight.y), halfHeight, backgroundCol);
	UIDrawing::FillRGBA(offset + this->pos + Vec2(0, halfHeight.y), Vec2(halfHeight.x * (*value - min) / (max - min), halfHeight.y), col);

	int textWidth = UIDrawing::TextWidth(this->label.c_str(), g_UIStyle.textFont);

	UIDrawing::TextRGBA(offset + this->pos + Vec2(size.x / 2.0f, halfHeight.y * 1.5f), g_UIStyle.textColor, g_UIStyle.textFont, FONT_CENTER, this->format.c_str(), *(this->value));

	this->wasMousePressed = mousePressed;
}

bool UISliderFloat::OnClick(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible || !this->value) return false;

	Vec2 halfHeight = Vec2(this->size.x, this->size.y / 2);

	bool onMainBox = g_Utils->InBox(offset + this->pos + Vec2(0, halfHeight.y), halfHeight, mousePos);

	if (onMainBox)
	{
		float x = max(0.0f, min(1.0f, (mousePos.x - offset.x) / size.x));
		*value = min + x * (max - min);
		return true;
	}

	return false;
}

void UISliderFloat::OnKeyPress(unsigned char key) {}

/********************************

     UIContainer

********************************/

UIContainer::UIContainer() : UIElement::UIElement()
{
	if (this->hasEdge)
		this->innerSize = Vec2(this->size.x - g_UIStyle.edgeMargin * 4 - g_UIStyle.edgeWeight * 2, this->size.y - g_UIStyle.edgeMargin * 4 - g_UIStyle.edgeWeight * 2);
	else
		this->innerSize = Vec2(this->size.x - g_UIStyle.margin * 2, this->size.y - g_UIStyle.margin * 2);
}

UIContainer::UIContainer(Vec2 pos, Vec2 size, std::string label, bool hasEdge) : UIElement::UIElement(pos, size, label)
{
	this->hasEdge = hasEdge;
	if (this->hasEdge)
		this->innerSize = Vec2(this->size.x - g_UIStyle.edgeMargin * 4 - g_UIStyle.edgeWeight * 2, this->size.y - g_UIStyle.edgeMargin * 4 - g_UIStyle.edgeWeight * 2);
	else
		this->innerSize = Vec2(this->size.x - g_UIStyle.margin * 2, this->size.y - g_UIStyle.margin * 2);
}

UIContainer::~UIContainer()
{
	for (UIElement *element : this->children)
	{
		delete element;
	}
}

void UIContainer::Draw(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible) return;

	int edgeMargin = g_UIStyle.edgeMargin;
	int margin = g_UIStyle.margin;
	int edgeWeight = g_UIStyle.edgeWeight;
	int textWidth = UIDrawing::TextWidth(this->label.c_str(), g_UIStyle.textFont);
	int textHeight = UIDrawing::TextHeight(this->label.c_str(), g_UIStyle.textFont);
	int textSpace = 8;
	int topLeftEdge = 16;

	if (this->hasEdge)
		this->innerSize = Vec2(this->size.x - edgeMargin * 4 - edgeWeight * 2, this->size.y - edgeMargin * 4 - edgeWeight * 2);
	else
		this->innerSize = Vec2(this->size.x - margin * 2, this->size.y - margin * 2);

	UIDrawing::FillRGBA(offset + this->pos, this->size, g_UIStyle.containerColor);

	if (this->hasEdge)
	{
		UIDrawing::FillRGBA(offset + this->pos + Vec2(edgeMargin, edgeMargin + edgeWeight), Vec2(edgeWeight, this->size.y - edgeMargin * 2 - edgeWeight), g_UIStyle.edgeColor);
		UIDrawing::FillRGBA(offset + this->pos + Vec2(this->size.x - edgeMargin - edgeWeight, edgeMargin + edgeWeight), Vec2(edgeWeight, this->size.y - edgeMargin * 2 - edgeWeight), g_UIStyle.edgeColor);

		UIDrawing::FillRGBA(offset + this->pos + Vec2(edgeMargin, edgeMargin), Vec2(topLeftEdge, edgeWeight), g_UIStyle.edgeColor);
		UIDrawing::FillRGBA(offset + this->pos + Vec2(edgeMargin + margin * 2 + topLeftEdge + textSpace * 2 + textWidth, edgeMargin), Vec2(this->size.x - (edgeMargin * 2 + margin * 2 + topLeftEdge + textSpace * 2 + textWidth), edgeWeight), g_UIStyle.edgeColor);
		UIDrawing::FillRGBA(offset + this->pos + Vec2(edgeMargin, this->size.y - edgeMargin - edgeWeight), Vec2(this->size.x - edgeMargin * 2, edgeWeight), g_UIStyle.edgeColor);

		UIDrawing::TextRGBA(offset + this->pos + Vec2(edgeMargin + margin + topLeftEdge + textSpace, (textHeight + edgeMargin) / 2 - 2), g_UIStyle.textColor, g_UIStyle.textFont, FONT_LEFT, this->label.c_str());
	}

	Drawing& drawing = Drawing::GetInstance();

	drawing.PushStyle();

	if (this->hasEdge)
		drawing.Clip(offset + this->pos + Vec2(edgeMargin * 2 + edgeWeight, edgeMargin * 2 + edgeWeight), this->innerSize);
	else
		drawing.Clip(offset + this->pos + Vec2(margin, margin), this->innerSize);

	for (unsigned i = this->children.size(); i-- > 0;)
	{
		UIElement *element = this->children[i];
		if (this->hasEdge)
			g_UISystem.HandleDraw(element, mousePos, offset + this->pos + Vec2(edgeMargin * 2 + edgeWeight, edgeMargin * 2 + edgeWeight));
		else
			g_UISystem.HandleDraw(element, mousePos, offset + this->pos + Vec2(margin, margin));
	}

	drawing.PopStyle();
}

void UIContainer::SetVisible(bool visible)
{
	this->visible = visible;

	for (UIElement *element : this->children)
	{
		g_UISystem.HandleSetVisible(element, visible);
	}
}

bool UIContainer::OnClick(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible) return false;

	for (UIElement *element : this->children)
	{
		Vec2 newOffset = offset + this->pos;
		if (this->hasEdge)
			newOffset += Vec2(g_UIStyle.edgeMargin * 2 + g_UIStyle.edgeWeight, g_UIStyle.edgeMargin * 2 + g_UIStyle.edgeWeight);
		else
			newOffset += Vec2(g_UIStyle.margin, g_UIStyle.margin);

		if (g_UISystem.HandleOnClick(element, mousePos, newOffset))
			return true;
	}

	return false;
}

void UIContainer::OnKeyPress(unsigned char key)
{
	if (!this->visible) return;

	for (UIElement *element : this->children)
	{
		g_UISystem.HandleOnKeyPress(element, key);
	}
}

void UIContainer::Add(UIElement* child)
{
	children.push_back(child);
}

void UIContainer::Clear()
{
	children.clear();
}

Vec2 UIContainer::Bottom() const
{
	if (children.size() == 0)
		return pos;
	return children.back()->bottom;
}

/********************************

    UITabs

********************************/

UITabs::UITabs() : UIElement::UIElement() {}

UITabs::UITabs(Vec2 pos, Vec2 size) : UIElement::UIElement(pos, size) {}

UITabs::~UITabs()
{
	for (UIContainer *container : this->tabContainers)
	{
		delete container;
	}
}

void UITabs::AddTab(std::string name, UIContainer *container)
{
	this->tabNames.push_back(name);
	this->tabContainers.push_back(container);
}

void UITabs::Draw(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible) return;

	for (unsigned i = 0; i < this->tabNames.size(); i++)
	{
		float startPercent = (float) i / (float) this->tabNames.size();
		float endPercent = (float) (i + 1) / (float) this->tabNames.size();
		Vec2 buttonPos = Vec2(this->size.x * startPercent, 0);
		Vec2 buttonSize = Vec2(this->size.x * endPercent, this->size.y) - buttonPos;
		Color buttonCol = g_UIStyle.buttonColor;

		if (i == this->selected)
			buttonCol = g_UIStyle.buttonSelectedColor;

		if (g_Utils->InBox(offset + this->pos + buttonPos, buttonSize, mousePos))
		{
			if (g_Utils->KeyDown(VK_LBUTTON))
				buttonCol = g_UIStyle.buttonPressedColor;
			else if (i != this->selected)
				buttonCol = g_UIStyle.buttonHoverColor;
		}
		UIDrawing::FillRGBA(offset + this->pos + buttonPos, buttonSize, buttonCol);
		UIDrawing::TextRGBA(offset + this->pos + buttonPos + Vec2(buttonSize.x / 2, buttonSize.y / 2), g_UIStyle.textColor, g_UIStyle.textFont, FONT_CENTER, "%s", this->tabNames[i].c_str());
	}

	if (this->selected < this->tabContainers.size())
		this->tabContainers[this->selected]->Draw(mousePos, offset + this->pos + Vec2(0, this->size.y));
}

void UITabs::SetVisible(bool visible)
{
	this->visible = visible;

	for (UIContainer *container : this->tabContainers)
	{
		container->SetVisible(false);
	}

	if (this->selected < this->tabContainers.size())
	{
		this->tabContainers[this->selected]->SetVisible(visible);
	}
}

bool UITabs::OnClick(Vec2 mousePos, Vec2 offset)
{
	if (!this->visible) return false;

	for (unsigned i = 0; i < this->tabNames.size(); i++)
	{
		float startPercent = (float)i / (float)this->tabNames.size();
		float endPercent = (float)(i + 1) / (float)this->tabNames.size();
		Vec2 buttonPos = Vec2(this->size.x * startPercent, 0);
		Vec2 buttonSize = Vec2(this->size.x * endPercent, this->size.y) - buttonPos;
		if (g_Utils->InBox(offset + this->pos + buttonPos, buttonSize, mousePos))
		{
			this->selected = i;
			this->SetVisible(this->visible);
			return true;
		}
	}

	for (UIContainer *container : this->tabContainers)
	{
		if (container->OnClick(mousePos, offset + this->pos + Vec2(0, this->size.y)))
			return true;
	}

	return false;
}

void UITabs::OnKeyPress(unsigned char key)
{
	if (!this->visible) return;

	for (UIContainer *container : this->tabContainers)
	{
		container->OnKeyPress(key);
	}
}

/********************************

    UIWindow

********************************/

UIWindow::UIWindow() : UIElement::UIElement() {}

UIWindow::UIWindow(Vec2 pos, Vec2 size, std::string label) : UIElement::UIElement(pos, size, label) {}

UIWindow::~UIWindow()
{
	for (UIElement *element : this->children)
	{
		delete element;
	}
}

void UIWindow::Draw(Vec2 mousePos)
{
	if (!this->visible) return;

	static Vec2 lastMousePos = Vec2(0.0f, 0.0f);

	Vec2 titleBarSize = Vec2(0, g_UIStyle.titleFontSize + g_UIStyle.margin * 2);

	if (!this->dragging && g_Utils->KeyDown(VK_LBUTTON) && !this->wasMousePressed && g_Utils->InBox(pos - titleBarSize, Vec2(size.x, titleBarSize.y), mousePos))
		dragging = true;

	if (this->dragging && !g_Utils->KeyDown(VK_LBUTTON))
		this->dragging = false;

	if (this->dragging)
	{
		this->pos.x += mousePos.x - lastMousePos.x;
		this->pos.y += mousePos.y - lastMousePos.y;
	}

	UIDrawing::FillRGBA(this->pos, this->size, g_UIStyle.backgroundColor);

	if (this->dragging)
		UIDrawing::FillRGBA(this->pos - titleBarSize, Vec2(this->size.x, titleBarSize.y), g_UIStyle.titleBarDraggingColor);
	else
		UIDrawing::FillRGBA(this->pos - titleBarSize, Vec2(this->size.x, titleBarSize.y), g_UIStyle.titleBarColor);

	UIDrawing::TextRGBA(this->pos + Vec2(this->size.x / 2, -g_UIStyle.titleFontSize / 2 - g_UIStyle.margin), g_UIStyle.titleColor, g_UIStyle.titleFont, FONT_CENTER, this->label.c_str());

	for (unsigned i = this->children.size(); i-- > 0;)
	{
		UIElement *element = this->children[i];
		g_UISystem.HandleDraw(element, mousePos, this->pos);
	}

	lastMousePos = mousePos;
	this->wasMousePressed = g_Utils->KeyDown(VK_LBUTTON);
}

void UIWindow::SetVisible(bool visible)
{
	this->visible = visible;

	for (UIElement *element : this->children)
	{
		g_UISystem.HandleSetVisible(element, visible);
	}
}

bool UIWindow::OnClick(Vec2 mousePos)
{
	if (!this->visible) return false;

	for (UIElement *element : this->children)
	{
		if (g_UISystem.HandleOnClick(element, mousePos, this->pos))
			return true;
	}

	return false;
}

void UIWindow::OnKeyPress(unsigned char key)
{
	if (!this->visible) return;

	for (UIElement *element : this->children)
	{
		g_UISystem.HandleOnKeyPress(element, key);
	}
}

void UIWindow::Add(UIElement* child)
{
	children.push_back(child);
}

void UIWindow::Clear()
{
	children.clear();
}

Vec2 UIWindow::Bottom() const
{
	if (children.size() == 0)
		return pos;
	return children.back()->bottom;
}

/********************************

    UISystem

********************************/

UISystem::UISystem()
{
	mainWindow = new UIWindow(Vec2(100, 100), Vec2(875, 575), "V E N G E A N C E");
	int tabHeight = 30;
	int dropdownHeight = g_UIStyle.textFontSize * 2 + g_UIStyle.margin * 4;
	UITabs *tabs = new UITabs(Vec2(0, 0), Vec2(mainWindow->size.x, tabHeight));
	UIContainer *rageTab = new UIContainer(Vec2(0, 0), Vec2(mainWindow->size.x, mainWindow->size.y - tabHeight), "Rage");
	tabs->AddTab("Rage", rageTab);
	
	UIContainer *legitTab = new UIContainer(Vec2(0, 0), Vec2(mainWindow->size.x, mainWindow->size.y - tabHeight), "Legit");
	tabs->AddTab("Legit", legitTab);

	static bool testValues[6] = { false, false, false };

	static const char *testNames[6] = { "Test A", "Test B", "Test C", "Test D", "Test E", "Test F" };
	static const int testNamesCount = 6;
	static char testStr[256] = "Test String";
	static const int testStrLen = 256;

	UIContainer *visualsTab = new UIContainer(Vec2(0, 0), Vec2(mainWindow->size.x, mainWindow->size.y - tabHeight), "Visuals");
	{
		UITabs *visualsTabs = new UITabs(Vec2(0, 0), Vec2(visualsTab->innerSize.x, tabHeight));
		{
			UIContainer *visualsEspContainer = new UIContainer(Vec2(0, 0), Vec2(visualsTab->innerSize.x, visualsTab->innerSize.y - tabHeight), "ESP");
			{
				visualsEspContainer->Add(new UICheckbox(Vec2(0, 0), "ESP", &g_Options.espEnable));

				Vec2 containerStart = visualsEspContainer->Bottom();

				/*UIContainer *visualsEspPlayersContainer = new UIContainer(containerStart, Vec2(visualsEspContainer->innerSize.x / 2, visualsEspContainer->innerSize.y - containerStart.y), "Players", true);
				{
					visualsEspPlayersContainer->Add(new UILabel(Vec2(0, 0), "Friendly"));
					visualsEspPlayersContainer->Add(new UICheckbox(visualsEspPlayersContainer->Bottom(), "Box", &g_Options.espFriendlyBox));
					visualsEspPlayersContainer->Add(new UILabel(Vec2(visualsEspPlayersContainer->innerSize.x / 2, 0), "Enemy"));
					visualsEspPlayersContainer->Add(new UICheckbox(visualsEspPlayersContainer->Bottom(), "Box", &g_Options.espEnemyBox));
				}
				visualsEspContainer->Add(visualsEspPlayersContainer);*/

				UIContainer *visualsEspFriendlyContainer = new UIContainer(containerStart, Vec2(visualsEspContainer->innerSize.x / 4, visualsEspContainer->innerSize.y - containerStart.y), "Friendly", true);
				{
					visualsEspFriendlyContainer->Add(new UICheckbox(Vec2(0, 0), "Box", &g_Options.espFriendlyBox));
					visualsEspFriendlyContainer->Add(new UICheckbox(visualsEspFriendlyContainer->Bottom(), "Name", &g_Options.espFriendlyName));
					visualsEspFriendlyContainer->Add(new UICheckbox(visualsEspFriendlyContainer->Bottom(), "Health", &g_Options.espFriendlyHealth));
					visualsEspFriendlyContainer->Add(new UICheckbox(visualsEspFriendlyContainer->Bottom(), "Lines", &g_Options.espFriendlyLines));
					visualsEspFriendlyContainer->Add(new UICheckbox(visualsEspFriendlyContainer->Bottom(), "Weapon", &g_Options.espFriendlyWeapon));
					visualsEspFriendlyContainer->Add(new UICheckbox(visualsEspFriendlyContainer->Bottom(), "Indicators", &g_Options.espFriendlyIndicators));
					visualsEspFriendlyContainer->Add(new UICheckbox(visualsEspFriendlyContainer->Bottom(), "Glow", &g_Options.espFriendlyGlow));
					visualsEspFriendlyContainer->Add(new UISingleDropdown(visualsEspFriendlyContainer->Bottom(), Vec2(visualsEspFriendlyContainer->innerSize.x, dropdownHeight), "Glow Style", &g_Options.espFriendlyGlowStyle, (char**)glowStyleList, glowStyleListCount));
					visualsEspFriendlyContainer->Add(new UICheckbox(visualsEspFriendlyContainer->Bottom(), "Chams", &g_Options.chamsFriendlyEnable));
					visualsEspFriendlyContainer->Add(new UISingleDropdown(visualsEspFriendlyContainer->Bottom(), Vec2(visualsEspFriendlyContainer->innerSize.x, dropdownHeight), "Chams Material", &g_Options.chamsFriendlyMaterial, (char**)chamsMaterialList, chamsMaterialListCount));
					visualsEspFriendlyContainer->Add(new UICheckbox(visualsEspFriendlyContainer->Bottom(), "Chams XQZ", &g_Options.chamsFriendlyXQZEnable));
					visualsEspFriendlyContainer->Add(new UISingleDropdown(visualsEspFriendlyContainer->Bottom(), Vec2(visualsEspFriendlyContainer->innerSize.x, dropdownHeight), "XQZ Chams Material", &g_Options.chamsFriendlyXQZMaterial, (char**)chamsMaterialList, chamsMaterialListCount));
					visualsEspFriendlyContainer->Add(new UICheckbox(visualsEspFriendlyContainer->Bottom(), "Shine", &g_Options.espFriendlyShine));
					visualsEspFriendlyContainer->Add(new UISingleDropdown(visualsEspFriendlyContainer->Bottom(), Vec2(visualsEspFriendlyContainer->innerSize.x, dropdownHeight), "Shine Material", &g_Options.espFriendlyShineMaterial, (char**)shineMaterialList, shineMaterialListCount));
				}
				visualsEspContainer->Add(visualsEspFriendlyContainer);

				UIContainer *visualsEspEnemyContainer = new UIContainer(containerStart + Vec2(visualsEspContainer->innerSize.x / 4, 0), Vec2(visualsEspContainer->innerSize.x / 4, visualsEspContainer->innerSize.y - containerStart.y), "Enemy", true);
				{
					visualsEspEnemyContainer->Add(new UICheckbox(Vec2(0, 0), "Box", &g_Options.espEnemyBox));
					visualsEspEnemyContainer->Add(new UICheckbox(visualsEspEnemyContainer->Bottom(), "Name", &g_Options.espEnemyName));
					visualsEspEnemyContainer->Add(new UICheckbox(visualsEspEnemyContainer->Bottom(), "Health", &g_Options.espEnemyHealth));
					visualsEspEnemyContainer->Add(new UICheckbox(visualsEspEnemyContainer->Bottom(), "Lines", &g_Options.espEnemyLines));
					visualsEspEnemyContainer->Add(new UICheckbox(visualsEspEnemyContainer->Bottom(), "Weapon", &g_Options.espEnemyWeapon));
					visualsEspEnemyContainer->Add(new UICheckbox(visualsEspEnemyContainer->Bottom(), "Indicators", &g_Options.espEnemyIndicators));
					visualsEspEnemyContainer->Add(new UICheckbox(visualsEspEnemyContainer->Bottom(), "Glow", &g_Options.espEnemyGlow));
					visualsEspEnemyContainer->Add(new UISingleDropdown(visualsEspEnemyContainer->Bottom(), Vec2(visualsEspEnemyContainer->innerSize.x, dropdownHeight), "Glow Style", &g_Options.espEnemyGlowStyle, (char**)glowStyleList, glowStyleListCount));
					visualsEspEnemyContainer->Add(new UICheckbox(visualsEspEnemyContainer->Bottom(), "Chams", &g_Options.chamsEnemyEnable));
					visualsEspEnemyContainer->Add(new UISingleDropdown(visualsEspEnemyContainer->Bottom(), Vec2(visualsEspEnemyContainer->innerSize.x, dropdownHeight), "Chams Material", &g_Options.chamsEnemyMaterial, (char**)chamsMaterialList, chamsMaterialListCount));
					visualsEspEnemyContainer->Add(new UICheckbox(visualsEspEnemyContainer->Bottom(), "Chams XQZ", &g_Options.chamsEnemyXQZEnable));
					visualsEspEnemyContainer->Add(new UISingleDropdown(visualsEspEnemyContainer->Bottom(), Vec2(visualsEspEnemyContainer->innerSize.x, dropdownHeight), "XQZ Chams Material", &g_Options.chamsEnemyXQZMaterial, (char**)chamsMaterialList, chamsMaterialListCount));
					visualsEspEnemyContainer->Add(new UICheckbox(visualsEspEnemyContainer->Bottom(), "Shine", &g_Options.espEnemyShine));
					visualsEspEnemyContainer->Add(new UISingleDropdown(visualsEspEnemyContainer->Bottom(), Vec2(visualsEspEnemyContainer->innerSize.x, dropdownHeight), "Shine Material", &g_Options.espEnemyShineMaterial, (char**)shineMaterialList, shineMaterialListCount));
				}
				visualsEspContainer->Add(visualsEspEnemyContainer);

				UIContainer *visualsEspLocalPlayerContainer = new UIContainer(containerStart + Vec2(visualsEspContainer->innerSize.x / 2, 0), Vec2(visualsEspContainer->innerSize.x / 4, visualsEspContainer->innerSize.y - containerStart.y), "Local Player", true);
				{
					visualsEspLocalPlayerContainer->Add(new UICheckbox(Vec2(0, 0), "Glow", &g_Options.espLocalGlow));
					visualsEspLocalPlayerContainer->Add(new UISingleDropdown(visualsEspLocalPlayerContainer->Bottom(), Vec2(visualsEspLocalPlayerContainer->innerSize.x, dropdownHeight), "Glow Style", &g_Options.espLocalGlowStyle, (char**)glowStyleList, glowStyleListCount));
					visualsEspLocalPlayerContainer->Add(new UICheckbox(visualsEspLocalPlayerContainer->Bottom(), "Shine", &g_Options.espLocalShine));
					visualsEspLocalPlayerContainer->Add(new UISingleDropdown(visualsEspLocalPlayerContainer->Bottom(), Vec2(visualsEspLocalPlayerContainer->innerSize.x, dropdownHeight), "Shine Material", &g_Options.espLocalShineMaterial, (char**)shineMaterialList, shineMaterialListCount));
					visualsEspLocalPlayerContainer->Add(new UICheckbox(visualsEspLocalPlayerContainer->Bottom(), "AA Lines", &g_Options.antiAimLines));
					visualsEspLocalPlayerContainer->Add(new UICheckbox(visualsEspLocalPlayerContainer->Bottom(), "First Person AA Lines", &g_Options.antiAimLinesFirstPerson));
					visualsEspLocalPlayerContainer->Add(new UICheckbox(visualsEspLocalPlayerContainer->Bottom(), "AA Info", &g_Options.antiAimInfo));
					visualsEspLocalPlayerContainer->Add(new UISingleDropdown(visualsEspLocalPlayerContainer->Bottom(), Vec2(visualsEspLocalPlayerContainer->innerSize.x, dropdownHeight), "Spread Crosshair", &g_Options.spreadCrosshair, (char**)spreadCrosshairList, spreadCrosshairListCount));
					visualsEspLocalPlayerContainer->Add(new UICheckbox(visualsEspLocalPlayerContainer->Bottom(), "Bullet Tracers", &g_Options.bulletTracersEnable));
					visualsEspLocalPlayerContainer->Add(new UISingleDropdown(visualsEspLocalPlayerContainer->Bottom(), Vec2(visualsEspLocalPlayerContainer->innerSize.x, dropdownHeight), "Bullet Tracer Material", &g_Options.bulletTracersMaterial, (char**)bulletTracersMaterialList, bulletTracersMaterialListCount));
				}
				visualsEspContainer->Add(visualsEspLocalPlayerContainer);

				UIContainer *visualsEspWeaponContainer = new UIContainer(containerStart + Vec2(visualsEspContainer->innerSize.x / 4 * 3, 0), Vec2(visualsEspContainer->innerSize.x / 4, (visualsEspContainer->innerSize.y - containerStart.y) / 3), "Weapon", true);
				{
					visualsEspWeaponContainer->Add(new UICheckbox(Vec2(0, 0), "Glow", &g_Options.espEnemyGlow));
					visualsEspWeaponContainer->Add(new UISingleDropdown(visualsEspWeaponContainer->Bottom(), Vec2(visualsEspWeaponContainer->innerSize.x, dropdownHeight), "Glow Style", &g_Options.espWeaponGlowStyle, (char**)glowStyleList, glowStyleListCount));
				}
				visualsEspContainer->Add(visualsEspWeaponContainer);

				UIContainer *visualsEspGrenadeContainer = new UIContainer(containerStart + Vec2(visualsEspContainer->innerSize.x / 4 * 3, (visualsEspContainer->innerSize.y - containerStart.y) / 3), Vec2(visualsEspContainer->innerSize.x / 4, (visualsEspContainer->innerSize.y - containerStart.y) / 3), "Grenade", true);
				{

				}
				visualsEspContainer->Add(visualsEspGrenadeContainer);

				UIContainer *visualsEspBombContainer = new UIContainer(containerStart + Vec2(visualsEspContainer->innerSize.x / 4 * 3, (visualsEspContainer->innerSize.y - containerStart.y) * 2 / 3), Vec2(visualsEspContainer->innerSize.x / 4, (visualsEspContainer->innerSize.y - containerStart.y) / 3), "Bomb", true);
				{
					visualsEspBombContainer->Add(new UIMultiDropdown(Vec2(0, 0), Vec2(visualsEspWeaponContainer->innerSize.x, dropdownHeight), "Test", testValues, (char**)testNames, testNamesCount));
					visualsEspBombContainer->Add(new UITextBox(visualsEspBombContainer->Bottom(), Vec2(visualsEspWeaponContainer->innerSize.x, dropdownHeight), "Text Label", testStr, testStrLen));
				}
				visualsEspContainer->Add(visualsEspBombContainer);
			}
			visualsTabs->AddTab("ESP", visualsEspContainer);

			UIContainer *visualsOtherContainer = new UIContainer(Vec2(0, 0), Vec2(visualsTab->innerSize.x, visualsTab->innerSize.y - tabHeight), "Other");
			{
				Vec2 containerStart = visualsOtherContainer->Bottom();

				UIContainer *visualsEspLocalContainer = new UIContainer(containerStart, Vec2(visualsOtherContainer->innerSize.x / 4, visualsOtherContainer->innerSize.y - containerStart.y), "Local", true);
				{
					visualsEspLocalContainer->Add(new UISliderFloat(visualsEspLocalContainer->Bottom(), Vec2(visualsEspLocalContainer->innerSize.x, dropdownHeight), "Scan", &g_Options.SCAN, 0.0000f, 5.0000f, "%.5f"));
					if (g_Options.fovRelative)
						visualsEspLocalContainer->Add(new UISliderFloat(visualsEspLocalContainer->Bottom(), Vec2(visualsEspLocalContainer->innerSize.x, dropdownHeight), "FOV", &g_Options.fov, -89.0f, 89.0f, "%.2f"));
					else
						visualsEspLocalContainer->Add(new UISliderFloat(visualsEspLocalContainer->Bottom(), Vec2(visualsEspLocalContainer->innerSize.x, dropdownHeight), "FOV", &g_Options.fov, 1.0f, 179.0f, "%.2f"));
				}
				visualsOtherContainer->Add(visualsEspLocalContainer);
			}
			visualsTabs->AddTab("Other", visualsOtherContainer);

			UIContainer *visualsStyleContainer = new UIContainer(Vec2(0, 0), Vec2(visualsTab->innerSize.x, visualsTab->innerSize.y - tabHeight), "Style");
			{
				
			}
			visualsTabs->AddTab("Style", visualsStyleContainer);
		}
		visualsTab->Add(visualsTabs);
	}
	tabs->AddTab("Visuals", visualsTab);

	UIContainer *miscTab = new UIContainer(Vec2(0, 0), Vec2(mainWindow->size.x, mainWindow->size.y - tabHeight), "Misc");
	tabs->AddTab("Misc", miscTab);
	UIContainer *colorsTab = new UIContainer(Vec2(0, 0), Vec2(mainWindow->size.x, mainWindow->size.y - tabHeight), "Colors");
	tabs->AddTab("Colors", colorsTab);
	mainWindow->Add(tabs);
	//mainWindow.containers.push_back(UIContainer(Vec2(0, 0), Vec2(400, 200), "Container A"));
	//mainWindow.containers.push_back(UIContainer(Vec2(400, 0), Vec2(200, 200), "Container B"));
	//mainWindow.containers.push_back(UIContainer(Vec2(600, 0), Vec2(200, 400), "Container C"));
	//mainWindow.containers.push_back(UIContainer(Vec2(0, 200), Vec2(600, 200), "Container D"));
}

void UISystem::UpdateInput()
{
	static bool wasMousePressed = false;
	static char oldKeyboard[256] = { 0 };
	static int keyboardRepeatCooldown[256] = { 0 };
	static long long lastTime = g_Utils->CurrentTimeMillis();
	long long curTime = g_Utils->CurrentTimeMillis();
	long long deltaTime = curTime - lastTime;
	
	if (GetForegroundWindow() != g_Globals->CSGOWindow)
		return;

	bool mousePressed = g_Utils->KeyDown(VK_LBUTTON);
	char keyboard[256] = { 0 };
	GetKeyboardState((PBYTE) keyboard);

	if (mousePressed && !wasMousePressed)
	{
		//int mousePosX, mousePosY;
		//G_Surface->SurfaceGetCursorPos(mousePosX, mousePosY);
		/*POINT mousePos;
		bool ret = ScreenToClient(g_Globals->CSGOWindow, &mousePos);
		printf("STC: %i: %i, %i\n", ret, mousePos.x, mousePos.y);
		ret = GetCursorPos(&mousePos);
		printf("GCP: %i: %i, %i\n", ret, mousePos.x, mousePos.y);*/
		mainWindow->OnClick(g_Utils->CursorPos());
	}

	for (int key = 0; key < 256; key++) {
		keyboardRepeatCooldown[key] = keyboardRepeatCooldown[key] - (int) deltaTime;
		if (keyboardRepeatCooldown[key] < 0)
			keyboardRepeatCooldown[key] = 0;
		if ((keyboard[key] & 0x80) != 0x0)
		{
			//g_CVar->ConsolePrintf("key %c (%hhx) pressed\n", key, key);
			if (((oldKeyboard[key]) & 0x80) == 0x0)
			{
				mainWindow->OnKeyPress((unsigned char) key);
				keyboardRepeatCooldown[key] = 375;
			}

			if (keyboardRepeatCooldown[key] <= 0)
			{
				mainWindow->OnKeyPress((unsigned char) key);
				keyboardRepeatCooldown[key] = 50;
			}
		}
	}

	wasMousePressed = mousePressed;
	GetKeyboardState((PBYTE) oldKeyboard);

	lastTime = curTime;
}

void UISystem::Draw()
{
	if (!g_UIStyle.titleFont || !g_UIStyle.textFont)
	{
		g_UIStyle.UpdateFont();
	}

	mainWindow->Draw(g_Utils->CursorPos());

	/*Drawing& drawing = Drawing::GetInstance();
	drawing.PushStyle();
	drawing.NoStroke();
	drawing.Fill(Color(0, 0, 255));
	drawing.Ellipse(Vec2(500, 500), Vec2(200, 200));
	drawing.PopStyle();*/
}

void UISystem::HandleDraw(UIElement *element, Vec2 mousePos, Vec2 offset)
{
	UILabel *label = dynamic_cast<UILabel*>(element);
	UICheckbox *checkbox = dynamic_cast<UICheckbox*>(element);
	UISingleDropdown *singleDropdown = dynamic_cast<UISingleDropdown*>(element);
	UIMultiDropdown *multiDropdown = dynamic_cast<UIMultiDropdown*>(element);
	UITextBox *textBox = dynamic_cast<UITextBox*>(element);
	UISliderFloat *sliderFloat = dynamic_cast<UISliderFloat*>(element);
	UIContainer *container = dynamic_cast<UIContainer*>(element);
	UITabs *tabs = dynamic_cast<UITabs*>(element);
	if (label)
		label->Draw(mousePos, offset);
	if (checkbox)
		checkbox->Draw(mousePos, offset);
	if (singleDropdown)
		singleDropdown->Draw(mousePos, offset);
	if (multiDropdown)
		multiDropdown->Draw(mousePos, offset);
	if (textBox)
		textBox->Draw(mousePos, offset);
	if (sliderFloat)
		sliderFloat->Draw(mousePos, offset);
	if (container)
		container->Draw(mousePos, offset);
	if (tabs)
		tabs->Draw(mousePos, offset);
}

void UISystem::HandleSetVisible(UIElement *element, bool visible)
{
	UILabel *label = dynamic_cast<UILabel*>(element);
	UICheckbox *checkbox = dynamic_cast<UICheckbox*>(element);
	UISingleDropdown *singleDropdown = dynamic_cast<UISingleDropdown*>(element);
	UIMultiDropdown *multiDropdown = dynamic_cast<UIMultiDropdown*>(element);
	UITextBox *textBox = dynamic_cast<UITextBox*>(element);
	UISliderFloat *sliderFloat = dynamic_cast<UISliderFloat*>(element);
	UIContainer *container = dynamic_cast<UIContainer*>(element);
	UITabs *tabs = dynamic_cast<UITabs*>(element);
	if (label)
		label->SetVisible(visible);
	if (checkbox)
		checkbox->SetVisible(visible);
	if (singleDropdown)
		singleDropdown->SetVisible(visible);
	if (multiDropdown)
		multiDropdown->SetVisible(visible);
	if (textBox)
		textBox->SetVisible(visible);
	if (sliderFloat)
		sliderFloat->SetVisible(visible);
	if (container)
		container->SetVisible(visible);
	if (tabs)
		tabs->SetVisible(visible);
}

bool UISystem::HandleOnClick(UIElement *element, Vec2 mousePos, Vec2 offset)
{
	UILabel *label = dynamic_cast<UILabel*>(element);
	UICheckbox *checkbox = dynamic_cast<UICheckbox*>(element);
	UISingleDropdown *singleDropdown = dynamic_cast<UISingleDropdown*>(element);
	UIMultiDropdown *multiDropdown = dynamic_cast<UIMultiDropdown*>(element);
	UITextBox *textBox = dynamic_cast<UITextBox*>(element);
	UISliderFloat *sliderFloat = dynamic_cast<UISliderFloat*>(element);
	UIContainer *container = dynamic_cast<UIContainer*>(element);
	UITabs *tabs = dynamic_cast<UITabs*>(element);
	if (label)
		return label->OnClick(mousePos, offset);
	if (checkbox)
		return checkbox->OnClick(mousePos, offset);
	if (singleDropdown)
		return singleDropdown->OnClick(mousePos, offset);
	if (multiDropdown)
		return multiDropdown->OnClick(mousePos, offset);
	if (textBox)
		return textBox->OnClick(mousePos, offset);
	if (sliderFloat)
		return sliderFloat->OnClick(mousePos, offset);
	if (container)
		return container->OnClick(mousePos, offset);
	if (tabs)
		return tabs->OnClick(mousePos, offset);
	return false;
}

void UISystem::HandleOnKeyPress(UIElement *element, unsigned char key)
{
	UILabel *label = dynamic_cast<UILabel*>(element);
	UICheckbox *checkbox = dynamic_cast<UICheckbox*>(element);
	UISingleDropdown *singleDropdown = dynamic_cast<UISingleDropdown*>(element);
	UIMultiDropdown *multiDropdown = dynamic_cast<UIMultiDropdown*>(element);
	UITextBox *textBox = dynamic_cast<UITextBox*>(element);
	UISliderFloat *sliderFloat = dynamic_cast<UISliderFloat*>(element);
	UIContainer *container = dynamic_cast<UIContainer*>(element);
	UITabs *tabs = dynamic_cast<UITabs*>(element);
	if (label)
		label->OnKeyPress(key);
	if (checkbox)
		checkbox->OnKeyPress(key);
	if (singleDropdown)
		singleDropdown->OnKeyPress(key);
	if (multiDropdown)
		multiDropdown->OnKeyPress(key);
	if (textBox)
		textBox->OnKeyPress(key);
	if (sliderFloat)
		sliderFloat->OnKeyPress(key);
	if (container)
		container->OnKeyPress(key);
	if (tabs)
		tabs->OnKeyPress(key);
}

UISystem g_UISystem = UISystem();