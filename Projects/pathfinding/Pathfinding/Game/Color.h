#pragma once
#include "Trackable.h"
#include "allegro5\allegro_color.h"

enum DefaultColor
{
	BLACK,
	WHITE,
	RED,
	GREEN,
	BLUE
};

struct Color : public Trackable
{
	ALLEGRO_COLOR color;

	Color(DefaultColor _color);
	Color(float _r, float _b, float _g, float _a);
};