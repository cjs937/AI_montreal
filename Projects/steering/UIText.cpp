#include "UIText.h"
#include "Color.h"

UIText::UIText(int _ID, Vector2D _position, ALLEGRO_FONT* _font, Color* _color, int _textAlignmentFlag, std::string _currentText, bool _isActive): UIObject(_ID, _position, _isActive),

	mpFont(_font), mpTextColor(_color), mTextAlignment(_textAlignmentFlag), mCurrentText(_currentText)
{}

UIText::~UIText()
{
	if (mpFont != NULL)
	{
		al_destroy_font(mpFont);
		mpFont = NULL;
	}

	if (mpTextColor != NULL)
	{
		delete mpTextColor;
		mpTextColor = NULL;
	}
}

void UIText::displayText(std::string _text)
{
	mCurrentText = _text;
}


void UIText::update(float _dt)
{
	if (!mActive)
		return;

	al_draw_text(mpFont, mpTextColor->color, mPosition.getX(), mPosition.getY(), mTextAlignment, mCurrentText.c_str());
}