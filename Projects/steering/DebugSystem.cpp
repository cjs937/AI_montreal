#include "DebugSystem.h"
#include "Game.h"
#include "UiManager.h"
#include "UIText.h"

DebugSystem::DebugSystem()
{
	mCurrentMode = NO_DEBUG;
	mIsActive = false;

	mUIText = static_cast<UIText*>(gpGame->getUIManager()->addObject(TEXT, Vector2D(0.0f, 0.0f), ALLEGRO_ALIGN_LEFT, mIsActive));
	mUIText->displayText("test");
}

DebugSystem::~DebugSystem()
{
	if (gpGame->getUIManager() == NULL)
		return;

	gpGame->getUIManager()->removeObject(mUIText->getID());
}

void DebugSystem::update(float _dt)
{
	if (!mIsActive)
		return;

	//std::string newText;

	//switch (mCurrentMode)
	//{
	//case(VELOCITY_CONTROL):
	//{
	//	gpGame->getUnitManager()->get
	//}
	//}

}

void DebugSystem::changeDebugText(std::string _newText)
{
	mUIText->displayText(_newText);
}

void DebugSystem::toggleActivation()
{
	mIsActive = !mIsActive;

	mUIText->setActive(mIsActive);
}

void DebugSystem::DebugVelocityControl()
{

}