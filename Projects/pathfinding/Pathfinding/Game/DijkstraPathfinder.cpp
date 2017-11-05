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
	std::priority_queue<DijkstraNode> openList;
	std::vector<Node*> closedList;

	//initialization
	mPath.clear();
	mVisitedNodes.clear();

	openList.push(DijkstraNode(pFrom, NULL, 0.0f));

	DijkstraNode currentNode = openList.top();
	bool here = false;

	while (currentNode.node != pTo && openList.size() > 0)
	{
		std::vector<Connection*> connections = mpGraph->getConnections(*currentNode.node);

		for (size_t i = 0; i < connections.size(); ++i)
		{
			DijkstraNode tempNode;
			Node* connectionNode = connections[i]->getToNode();
			float newCost = currentNode.cost + connections[i]->getCost();

			// if node is in closed list
			if (std::find(closedList.begin(), closedList.end(), connectionNode) != closedList.end())
			{
				continue;
			}
			// if node is in open list
			else if ((tempNode = getNodeInOpenList(connectionNode, openList)).node != NULL) 
			{
				if (tempNode.cost <= newCost)
				{
					continue;
				}

				tempNode.connection = new DijkstraNode(&currentNode);
				tempNode.cost = newCost;

				continue;
			}

			// if node is unvisited
			tempNode = DijkstraNode(connectionNode, new DijkstraNode(&currentNode), newCost);

			openList.push(tempNode);
		}

		closedList.push_back(currentNode.node);

		openList.pop();
		currentNode = openList.top();

	}

	if (currentNode.node != pTo)
	{
		return mPath;
	}

	//generates a temporary path going from goal to start
	std::vector<Node*> tempPath;

	DijkstraNode* toAdd = new DijkstraNode(&currentNode);
	DijkstraNode* prevNode = NULL;

	while (true)
	{
		tempPath.push_back(toAdd->node);

		//if this is start node
		if (toAdd->connection == NULL)
		{
			delete toAdd;

			break;
		}

		prevNode = toAdd;

		toAdd = toAdd->connection;

		delete prevNode;

		prevNode = toAdd;

	}

	//reverses path so the start is the first node
	for (int i = tempPath.size() - 1; i >= 0; --i)
	{
		mPath.addNode(tempPath[i]);

		mVisitedNodes.push_back(tempPath[i]);
	}

	return mPath;
}

DijkstraPathfinder::DijkstraNode DijkstraPathfinder::getNodeInOpenList(Node* _node, std::priority_queue<DijkstraNode> _openList)
{
	DijkstraNode currentNode;

	while (_openList.size() > 0)
	{
		currentNode = _openList.top();

		if (currentNode.node == _node)
			return currentNode;

		_openList.pop();
	}

	return DijkstraNode();
}
