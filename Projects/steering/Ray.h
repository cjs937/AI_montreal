#pragma once
#include "Vector2D.h"

struct Ray : public Trackable
{
private:
	 Vector2D mSourcePoint;
	 Vector2D mDirection;

public:
	Ray(Vector2D _source, float _length, Vector2D _direction) :mSourcePoint(_source)
	{
		mDirection = _direction;

		mDirection.normalize();

		mDirection *= _length;
	};

	~Ray()
	{};

	Vector2D getSourcePoint() { return mSourcePoint; };
	Vector2D getDirection() { return mDirection; };

	//R(t) = P + tD
	Vector2D getPointAlongRay(float _t) { return mSourcePoint + (Vector2D(_t * mDirection.getX(), _t * mDirection.getY())); };
};
