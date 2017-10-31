#pragma once
#include "GameMessage.h"
#include "Vector2D.h"

class AddBoidsMessage : public GameMessage
{
public:
	AddBoidsMessage(int _numBoids, Vector2D _offset);
	~AddBoidsMessage();

	void process();

private:
	int mNumBoids;
	Vector2D mOffset;
};