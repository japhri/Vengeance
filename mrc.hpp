#pragma once

#include "Main.h"
#include "Vec2.h"


class UIStyle
{
public:
	int margin = 2;
	int edgeMargin = 10;
	int edgeWeight = 4;
	int dropdownTriangleSize = 10;
	Color backgroundColor = Color(32, 32, 32, 192);
	Color containerColor = Color(32, 32, 32, 192);
	Color titleBarColor = Color(64, 16, 16, 220);
	Color titleBarDraggingColor = Color(56, 14, 14, 220);
	Color edgeColor = Color(64, 64, 64, 192);
	Color titleColor = Color(255, 255, 255, 255);
	Color textColor = Color(220, 220, 220, 255);
	Color buttonColor = Color(64, 16, 16, 255);
	Color buttonHoverColor = Color(80, 20, 20, 255);
	Color buttonPressedColor = Color(48, 12, 12, 255);
	Color buttonSelectedColor = Color(56, 14, 14, 255);
	Color checkboxBackgroundColor = Color(56, 56, 56, 255);
	Color checkboxBackgroundHoverColor = Color(64, 64, 64, 255);
	Color checkboxBackgroundPressedColor = Color(48, 48, 48, 255);
	Color checkboxColor = Color(112, 28, 28, 255);
	Color checkboxHoverColor = Color(128, 32, 32, 255);
	Color checkboxPressedColor = Color(96, 24, 24, 255);
	/*Color dropdownColor = Color(56, 56, 56, 255);
	Color dropdownHoverColor = Color(64, 64, 64, 255);
	Color dropdownPressedColor = Color(48, 48, 48, 255);*/
	Color dropdownColor = Color(64, 64, 64, 255);
	Color dropdownHoverColor = Color(80, 80, 80, 255);
	Color dropdownPressedColor = Color(48, 48, 48, 255);
	Color dropdownSelectedColor = Color(56, 56, 56, 255);
	Color dropdownTriangleColor = Color(16, 16, 16, 255);
	Color dropdownTriangleHoverColor = Color(20, 20, 20, 255);
	Color dropdownTrianglePressedColor = Color(12, 12, 12, 255);
	Color dropdownTriangleSelectedColor = Color(14, 14, 14, 255);
	Color dropdownSpecialColor = Color(64, 16, 16, 255);
	Color dropdownSpecialHoverColor = Color(80, 20, 20, 255);
	Color dropdownSpecialPressedColor = Color(48, 12, 12, 255);
	Color dropdownSpecialSelectedColor = Color(56, 14, 14, 255);
	Color textboxColor = Color(56, 56, 56, 255);
	Color textboxHoverColor = Color(80, 80, 80, 255);
	Color textboxPressedColor = Color(48, 48, 48, 255);
	Color textboxSelectedColor = Color(64, 64, 64, 255);
	Color textboxHighlightColor = Color(64, 128, 255, 192);
	Color textboxUnfocusedHighlightColor = Color(128, 128, 128, 192);
	Color sliderBackgroundColor = Color(64, 64, 64, 255);
	Color sliderBackgroundHoverColor = Color(80, 80, 80, 255);
	Color sliderBackgroundPressedColor = Color(48, 48, 48, 255);
	Color sliderColor = Color(64, 16, 16, 255);
	Color sliderHoverColor = Color(80, 20, 20, 255);
	Color sliderPressedColor = Color(48, 12, 12, 255);

	unsigned long titleFont;
	unsigned long textFont;

	int titleFontSize = 24;
	int textFontSize = 18;

	void UIStyle::UpdateFont();
};

extern UIStyle g_UIStyle;

namespace UIDrawing
{
	void FillRGBA(Vec2 pos, Vec2 size, Color col);
	void StrokeRGBA(Vec2 pos, Vec2 size, Color col);
	void LineRGBA(Vec2 start, Vec2 end, Color col);
	void TextRGBA(Vec2 pos, Color col, unsigned int font, unsigned long alignment, const char * msg, ...);
	void PolyRGBA(Vec2* vertices, int count, Color col);
	void TriangleRGBA(Vec2 center, Vec2 size, float rotation, Color color);

	Vec2 CartesianToPolar(Vec2 in);
	Vec2 PolarToCartesian(Vec2 in);
	Vec2 RotateVector(Vec2 in, float rotation);
	/*Vector2D RotateVectorT(Vec2 in, float rotation);*/

	Vec2 TextSize(const char *text, unsigned long font);
	int TextWidth(const char *text, unsigned long font);
	int TextHeight(const char *text, unsigned long font);
	int CharWidth(char c, unsigned long font);
}

class UIElement
{
public:
	Vec2 pos;
	Vec2 size;
	Vec2 bottom;
	std::string label;

	bool visible = true;
	bool hovered = false;
	bool pressing = false;

	UIElement();
	UIElement(Vec2 pos, Vec2 size);
	UIElement(Vec2 pos, Vec2 size, std::string label);
	virtual ~UIElement();
	void Draw(Vec2 mousePos, Vec2 offset);
	void SetLabel(std::string newLabel);
	void SetVisible(bool visible);
	bool OnClick(Vec2 mousePos, Vec2 offset);
	void OnKeyPress(unsigned char key);
};

class UILabel : public UIElement
{
public:
	UILabel(Vec2 pos, std::string label);
	virtual ~UILabel();
	void Draw(Vec2 mousePos, Vec2 offset);
};

class UICheckbox : public UIElement
{
public:
	bool *value = 0;

	UICheckbox();
	UICheckbox(Vec2 pos, std::string label, bool *value);
	virtual ~UICheckbox();
	void Draw(Vec2 mousePos, Vec2 offset);
	bool OnClick(Vec2 mousePos, Vec2 offset);
	void OnKeyPress(unsigned char key);
};

class UISingleDropdown : public UIElement
{
public:
	bool opened = false;
	bool wasMousePressed = false;
	char **elementNames = 0;
	int elementCount = 0;
	int *value = 0;

	UISingleDropdown();
	UISingleDropdown(Vec2 pos, Vec2 size, std::string label, int *value, char **elementNames, int elementCount);
	virtual ~UISingleDropdown();
	void Draw(Vec2 mousePos, Vec2 offset);
	bool OnClick(Vec2 mousePos, Vec2 offset);
	void OnKeyPress(unsigned char key);
};

class UIMultiDropdown : public UIElement
{
public:
	bool opened = false;
	bool wasMousePressed = false;
	char **elementNames = 0;
	int elementCount = 0;
	bool *values = 0;

	UIMultiDropdown();
	UIMultiDropdown(Vec2 pos, Vec2 size, std::string label, bool *value, char **elementNames, int elementCount);
	virtual ~UIMultiDropdown();
	void Draw(Vec2 mousePos, Vec2 offset);
	bool OnClick(Vec2 mousePos, Vec2 offset);
	void OnKeyPress(unsigned char key);
};

class UITextBox : public UIElement
{
public:
	bool selected = false;
	bool dragging = false;
	unsigned caretStart = 0;
	unsigned caretEnd = 0;
	unsigned  textOffset = 0;
	bool wasMousePressed = false;
	char *str = NULL;
	unsigned maxStrLen = 0;

	UITextBox();
	UITextBox(Vec2 pos, Vec2 size, std::string label, char *str, unsigned maxStrLen);
	virtual ~UITextBox();
	void Draw(Vec2 mousePos, Vec2 offset);
	bool OnClick(Vec2 mousePos, Vec2 offset);
	void OnKeyPress(unsigned char key);
private:
	int OffsetFromPos(int pos, int offset);
	int OffsetFromPos(float pos, float offset);
};

class UISliderFloat : public UIElement
{
public:
	bool wasMousePressed = false;
	float *value = NULL;
	float min = 0.0f;
	float max = 0.0f;
	std::string format;
	bool dragging = false;
	float initialValue = 0.0f;

	UISliderFloat();
	UISliderFloat(Vec2 pos, Vec2 size, std::string label, float *value, float min, float max, std::string format = "%.2f");
	virtual ~UISliderFloat();
	void Draw(Vec2 mousePos, Vec2 offset);
	bool OnClick(Vec2 mousePos, Vec2 offset);
	void OnKeyPress(unsigned char key);
};

class UIContainer : public UIElement
{
public:
	Vec2 innerSize;
	bool hasEdge = false;
	std::vector<UIElement*> children;

	UIContainer();
	UIContainer(Vec2 pos, Vec2 size, std::string label, bool hasEdge = false);
	virtual ~UIContainer();
	void Draw(Vec2 mousePos, Vec2 offset);
	void SetVisible(bool visible);
	bool OnClick(Vec2 mousePos, Vec2 offset);
	void OnKeyPress(unsigned char key);

	void Add(UIElement* child);
	void Clear();
	Vec2 Bottom() const;
};

class UITabs : public UIElement
{
public:
	unsigned selected = 0;
	std::vector<std::string> tabNames;
	std::vector<UIContainer*> tabContainers;

	UITabs();
	UITabs(Vec2 pos, Vec2 size);
	virtual ~UITabs();
	void AddTab(std::string name, UIContainer *container);
	void Draw(Vec2 mousePos, Vec2 offset);
	void SetVisible(bool visible);
	bool OnClick(Vec2 mousePos, Vec2 offset);
	void OnKeyPress(unsigned char key);
};

class UIWindow : public UIElement
{
public:
	bool dragging = false;
	bool wasMousePressed = false;
	std::vector<UIElement*> children;

	UIWindow();
	UIWindow(Vec2 pos, Vec2 size, std::string label);
	virtual ~UIWindow();
	void Draw(Vec2 mousePos);
	void SetVisible(bool visible);
	bool OnClick(Vec2 mousePos);
	void OnKeyPress(unsigned char key);

	void Add(UIElement* child);
	void Clear();
	Vec2 Bottom() const;
};

class UISystem
{
public:
	UIWindow *mainWindow;

	UISystem();
	void UpdateInput();
	void Draw();
	void HandleDraw(UIElement *element, Vec2 mousePos, Vec2 offset);
	void HandleSetVisible(UIElement *element, bool visible);
	bool HandleOnClick(UIElement *element, Vec2 mousePos, Vec2 offset);
	void HandleOnKeyPress(UIElement *element, unsigned char key);
};

extern UISystem g_UISystem;