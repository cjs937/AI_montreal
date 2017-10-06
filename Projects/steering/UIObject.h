#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class UIObject : public Trackable
{
	friend class UIManager;

protected:
	int mID;
	Vector2D mPosition;
	bool mActive;

	virtual void update(float _dt) = 0;

public:
	inline int getID() { return mID; };
	inline Vector2D getPosition() { return mPosition; };
	inline bool isActive() { return mActive; };
	inline void setActive(bool _isActive) { mActive = _isActive; };

	UIObject(int _ID, Vector2D _position, bool _isActive = true) :mID(_ID), mPosition(_position), mActive(_isActive) {};
	~UIObject() {};
};