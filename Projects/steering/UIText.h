#pragma once
#include "UIObject.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_font.h"

struct Color;

class UIText : public UIObject
{
private:
	ALLEGRO_FONT* mpFont;
	Color* mpTextColor;
	std::string mCurrentText;
	int mTextAlignment;

protected:
	virtual void update(float _dt);

public:
	UIText(int _ID, Vector2D _position, ALLEGRO_FONT* _font, Color* _color, int _textAlignmentFlag, std::string _currentText = "", bool _isActive = true);
	~UIText();

	inline ALLEGRO_FONT* getFont() const { return mpFont; };
	void displayText(std::string _text);
};