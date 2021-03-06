#include "Color.h"

Color::Color(DefaultColor _color)
{
	switch (_color)
	{
	case BLACK:
		color = al_map_rgba(0, 0, 0, 0);
		break;
	case WHITE:
		color = al_map_rgba(255, 255, 255, 0);
		break;
	case RED:
		color = al_map_rgba(255, 0, 0, 0);
		break;
	default:
		color = color = al_map_rgba(0, 0, 0, 0);
	}
}

Color::Color(float _r, float _b, float _g, float _a)
{
	color = al_map_rgba(_r, _b, _g, _a);
}