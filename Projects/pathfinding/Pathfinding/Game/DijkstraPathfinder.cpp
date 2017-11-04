#include "DijkstraPathfinder.h"
#include <queue>
#include <vector>
#include "Node.h"
#include "GridGraph.h"
#include "Connection.h"

DijkstraPathfinder::DijkstraPathfinder(GridGraph* pGraph):GridPathfinder(pGraph)
{}

DijkstraPathfinder::~DijkstraPathfinder()
{}

const Path& DijkstraPathfinder::findPath(Node* pFrom, Node* pTo)
{
	std::priority_queue<DijkstraNode*> openList;
	std::vector<Node*> closedList;
	std::vector<Node*> tempPath;

	//initialization
	mPath.clear();
	mVisitedNodes.clear();


	openList.push(new DijkstraNode(pFrom, NULL, 0.0f));

	DijkstraNode* currentNode = openList.top();

	while (currentNode->node != pTo && openList.size() > 0)
	{
		openList.pop();

		std::vector<Connection*> connections = mpGraph->getConnections(*currentNode->node);

		for (int i = 0; i < connections.size(); ++i)
		{
			Node* connectionNode = connections[i]->getToNode();

			// if node isn't already in closed list
			if (std::find(closedList.begin(), closedList.end(), connectionNode) == closedList.end())
			{
				float newCost = currentNode->cost + connections[i]->getCost();

				DijkstraNode* newNode = new DijkstraNode(connectionNode, currentNode, newCost);

				openList.push(newNode);
			}
		}

		closedList.push_back(currentNode->node);

		currentNode = openList.top();
	}

	//generates a temporary path going from goal to start
	DijkstraNode* previousNode = currentNode;

	while (currentNode != NULL)
	{
		tempPath.push_back(currentNode->node);

		previousNode = currentNode;

		currentNode = currentNode->connection;

		delete previousNode;
	}

	//reverses path so the start is the first node
	for (int i = tempPath.size() - 1; i >= 0; --i)
	{
		mPath.addNode(tempPath[i]);

		mVisitedNodes.push_back(tempPath[i]);
	}

	//clears out any remaining nodes in open list
	//while(openList.size() > 0)
	//{
	//	currentNode = openList.top();

	//	delete currentNode;

	//	openList.pop();
	//}


	return mPath;
}