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

	mpDefaultFont = al_load_ttf_font("cour.ttf", 20, 0);

	mAvailalbeIDs.push(0);

	int textID = addObject(TEXT, Vector2D(0, 0), ALLEGRO_ALIGN_LEFT)->getID();

	static_cast<UIText*>(mUIOBjects[textID])->displayText("test");
}

UIManager::~UIManager()
{
	for (std::map<int, UIObject*>::iterator uiObject = mUIOBjects.begin(); uiObject != mUIOBjects.end(); ++uiObject)
	{
		//not deleting the object for some reason, leading to memory leaks
		delete mUIOBjects[uiObject->first];

		mUIOBjects[uiObject->first] = NULL;
	}

	mUIOBjects.clear();

	if (mpDefaultFont != NULL)
	{
		al_destroy_font( mpDefaultFont );

		mpDefaultFont = NULL;
	}
}

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
			newObj = new UIText(newID, _position, mpDefaultFont, new Color(WHITE), static_cast<int>(ALLEGRO_ALIGN_LEFT));
			break;
		}
		default:
			break;
	}

	mUIOBjects.insert(std::pair<int, UIObject*>(newID, newObj));

	return newObj;
}
