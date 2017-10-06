#pragma once
#include "Trackable.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_font.h"
#include <map>
#include <stack>

enum UIType
{
	TEXT
};

class UIObject;
struct Vector2D;

class UIManager : public Trackable
{
private:
	std::map<int, UIObject*> mUIOBjects;
	std::stack<int> mAvailalbeIDs;

public:

	UIManager();
	~UIManager();
	void update(float _dt);
	UIObject* addObject(UIType _type, Vector2D _position, int _alignmentFlags, bool _isActive = true);

};
