#include "UiManager.h"
#include "allegro5\allegro_ttf.h"
#include "UIObject.h"
#include "UIText.h"
#include "allegro5\allegro_color.h"
#include "Color.h"

UIManager::UIManager()
{
	if (!al_init_ttf_addon())
	{
		printf("ttf font addon not initted properly!\n");
		return;
	}

	mAvailalbeIDs.push(0);

	addObject(TEXT, Vector2D(0, 0), ALLEGRO_ALIGN_LEFT);
}

UIManager::~UIManager()
{}

void UIManager::update(float _dt)
{
	for (std::map<int, UIObject*>::iterator uiObject = mUIOBjects.begin(); uiObject != mUIOBjects.end(); ++uiObject)
	{
		uiObject->second->update(_dt);
	}
}

UIObject* UIManager::addObject(UIType _type, Vector2D _position, int _alignmentFlags, bool _isActive)
{
	int newID = mAvailalbeIDs.top();

	mAvailalbeIDs.pop();

	if (mAvailalbeIDs.size() == 0)
		mAvailalbeIDs.push(newID + 1);

	UIObject* newObj = NULL;

	switch (_type)
	{
		case TEXT:
		{
			newObj = new UIText(newID, _position, al_load_ttf_font("cour.ttf", 20, 0), new Color(BLACK), static_cast<int>(ALLEGRO_ALIGN_LEFT));
			break;
		}
		default:
			break;
	}

	mUIOBjects.insert(std::pair<int, UIObject*>(newID, newObj));

	return newObj;
}
