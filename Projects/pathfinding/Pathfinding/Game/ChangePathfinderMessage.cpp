#include "ChangePathfinderMessage.h"
#include "GameApp.h"
#include "GridPathfinder.h"
#include "Path.h"
#include "Grid.h"
#include "Vector2D.h"
#include "Node.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"

ChangePathfinderMessage::ChangePathfinderMessage(PathfinderType _type):GameMessage(TOGGLE_PATHFIND_ALGORITHM), mPathfinderType(_type)
{}

ChangePathfinderMessage::~ChangePathfinderMessage() {}

void ChangePathfinderMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	GridPathfinder* pathFinder = pGame->getPathfinder();
	
	if (pathFinder == NULL || pathFinder->getType() == mPathfinderType)
		return;

	Path oldPath = pathFinder->getPath();

	pGame->setPathfinder(mPathfinderType);

	if (oldPath.getNumNodes() == 0)
	{
		return;
	}

	Vector2D startPos = pGame->getGrid()->getULCornerOfSquare(oldPath.peekNode(0)->getId());
	Vector2D endPos = pGame->getGrid()->getULCornerOfSquare(oldPath.peekNode(oldPath.getNumNodes() - 1)->getId());

	pGame->getMessageManager()->addMessage(new PathToMessage(startPos, endPos), 0);
}
