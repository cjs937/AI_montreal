#include "DebugSystem.h"
#include "Game.h"
#include "UiManager.h"
#include "UIText.h"
#include "UnitManager.h"

DebugSystem::DebugSystem()
{
	mCurrentMode = NO_DEBUG;
	mIsActive = true;

	mUIText = static_cast<UIText*>(gpGame->getUIManager()->addObject(TEXT, Vector2D(0.0f, 0.0f), ALLEGRO_ALIGN_LEFT, mIsActive));
	mUIText->displayText("test");

	mUISelectedText = static_cast<UIText*>(gpGame->getUIManager()->addObject(TEXT, Vector2D(0.0f, 30.0f), ALLEGRO_ALIGN_LEFT, mIsActive, true));
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

	switch (mCurrentMode)
	{
	case(COHESION):
	{
		mUISelectedText->displayText("Cohesion Weight: " + std::to_string(gpGame->getUnitManager()->getCohesionWeight()));

		mUIText->displayText("Separation Weight: " + std::to_string(gpGame->getUnitManager()->getSeparationWeight()) + "\n" +
			"Alignment Weight: " + std::to_string(gpGame->getUnitManager()->getAlignWeight()));

		break;
	}
	case(SEPARATION):
	{
		mUISelectedText->displayText("Separation Weight: " + std::to_string(gpGame->getUnitManager()->getSeparationWeight()));

		mUIText->displayText("Cohesion Weight: " + std::to_string(gpGame->getUnitManager()->getCohesionWeight()) + "\n" +
			"Alignment Weight: " + std::to_string(gpGame->getUnitManager()->getAlignWeight()));

		break;
	}
	case(ALIGNMENT):
	{
		mUISelectedText->displayText("Alignment Weight: " + std::to_string(gpGame->getUnitManager()->getAlignWeight()));

		mUIText->displayText("Separation Weight: " + std::to_string(gpGame->getUnitManager()->getSeparationWeight()) + "\n" +
			"Cohesion Weight: " + std::to_string(gpGame->getUnitManager()->getCohesionWeight()));

		break;
	}
	default:

		mUISelectedText->displayText("");

		mUIText->displayText(
			"Cohesion Weight: " + std::to_string(gpGame->getUnitManager()->getCohesionWeight()) + "\n" +
			"Separation Weight: " + std::to_string(gpGame->getUnitManager()->getSeparationWeight()) + "\n" +
			"Alignment Weight: " + std::to_string(gpGame->getUnitManager()->getAlignWeight()));
	}

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

void DebugSystem::increaseCurrentValue(float _increaseBy)
{
	switch (mCurrentMode)
	{
	case(COHESION):
		{
		gpGame->getUnitManager()->increaseCohesionWeight(_increaseBy);

			break;
		}
	case(SEPARATION):
		{
		gpGame->getUnitManager()->increaseSeparationWeight(_increaseBy);

			break;
		}
	case(ALIGNMENT):
		{
		gpGame->getUnitManager()->increaseAlignmentWeight(_increaseBy);

			break;
		}
	default:
		{
			break;
		}
	}
}


//
//void DebugSystem::DebugVelocityControl()
//{
//
//}
//
//void DebugReactionRadius()
//{}
//void DebugAngularVelocity()
//{}
//void DebugCohesion()
//{}
//void DebugSeparation()
//{}
//void DebugAlignment()
//{}