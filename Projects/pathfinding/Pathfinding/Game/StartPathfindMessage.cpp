#include "StartPathFindMessage.h"
#include "GameApp.h"
#include "GridPathfinder.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "Path.h"
#include "Node.h"
#include "Grid.h"

StartPathfindMessage::StartPathfindMessage(Vector2D _pathTo):GameMessage(START_PATHFIND), mPathTo(_pathTo)
{}

StartPathfindMessage::~StartPathfindMessage()
{}

void StartPathfindMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);

	if (pGame->getGrid()->getValueAtPixelXY((int)mPathTo.getX(), (int)mPathTo.getY()) == BLOCKING_VALUE)
	{
		std::cout << "Invalid destination\n";
		return;
	}

	Path currentPath = pGame->getPathfinder()->getPath();

	Vector2D startPos = (currentPath.getNumNodes() > 0) ? pGame->getGrid()->getULCornerOfSquare(currentPath.peekNode(currentPath.getNumNodes() - 1)->getId()) 
														: Vector2D();

	PathToMessage* pathToMsg = new PathToMessage(startPos, mPathTo);
		
	pGame->getMessageManager()->addMessage(pathToMsg, 0);
}