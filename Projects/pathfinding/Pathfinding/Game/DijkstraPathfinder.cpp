#include "DijkstraPathfinder.h"
#include <queue>
#include <vector>
#include "Node.h"
#include "GridGraph.h"
#include "Connection.h"
#include "PerformanceTracker.h"
#include "GameApp.h"

DijkstraPathfinder::DijkstraPathfinder(GridGraph* pGraph):GridPathfinder(pGraph, Color(RED))
{}

DijkstraPathfinder::~DijkstraPathfinder()
{}

const Path& DijkstraPathfinder::findPath(Node* pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	DijkstraState currentState = DijkstraState();

	currentState.openList.push(DijkstraNode(pFrom));

	currentState.currentNode = currentState.openList.top();

	while (currentState.currentNode.node != pTo && currentState.openList.size() > 0)
	{
		evaluateConnections(currentState);

		currentState.closedList.push_back(currentState.currentNode.node);

		currentState.openList.pop();
		currentState.currentNode = currentState.openList.top();
	}

	//No path was found
	if (currentState.currentNode.node != pTo)
	{
		std::cout << "No path was found.\n";
		return mPath;
	}
	
	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	return generatePath(currentState);
}

void DijkstraPathfinder::evaluateConnections(DijkstraState &_currentState)
{
	std::vector<Connection*> connections = mpGraph->getConnections(*_currentState.currentNode.node);

	for (size_t i = 0; i < connections.size(); ++i)
	{
		DijkstraNode tempNode;
		Node* connectionNode = connections[i]->getToNode();
		float newCost = _currentState.currentNode.cost + connections[i]->getCost();

		// if node is in closed list
		if (std::find(_currentState.closedList.begin(), _currentState.closedList.end(), connectionNode) != _currentState.closedList.end())
		{
			continue;
		}
		// if node is in open list
		else if ((tempNode = getNodeInOpenList(connectionNode, _currentState.openList)).node != NULL)
		{
			if (tempNode.cost <= newCost)
			{
				continue;
			}

			tempNode.connection = new DijkstraNode(&_currentState.currentNode);
			_currentState.coverage.push_back(tempNode.connection);

			tempNode.cost = newCost;

			continue;
		}

		// if node is unvisited
		tempNode = DijkstraNode(connectionNode, new DijkstraNode(&_currentState.currentNode), newCost);
		_currentState.coverage.push_back(tempNode.connection);

		_currentState.openList.push(tempNode);
	}
}

Path& DijkstraPathfinder::generatePath(DijkstraState &_currentState)
{
	//generates a temporary path going from goal to start
	std::vector<Node*> tempPath;

	DijkstraNode* toAdd = new DijkstraNode(&_currentState.currentNode);
	_currentState.coverage.push_back(toAdd);

	while (toAdd != NULL)
	{
		tempPath.push_back(toAdd->node);

		toAdd = toAdd->connection;
	}

	//clear old path
	mPath.clear();
	mVisitedNodes.clear();

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

DijkstraPathfinder::DijkstraNode::DijkstraNode()
{
	node = NULL;
	connection = NULL;
	cost = 0;
}

DijkstraPathfinder::DijkstraNode::DijkstraNode(DijkstraNode* _copy)
{
	node = _copy->node;
	connection = _copy->connection;
	cost = _copy->cost;
}

DijkstraPathfinder::DijkstraNode::DijkstraNode(Node* _node, DijkstraNode* _connection, float _weight) : node(_node), connection(_connection), cost(_weight)
{};

DijkstraPathfinder::DijkstraNode::~DijkstraNode()
{
};

bool DijkstraPathfinder::DijkstraNode::operator<(const DijkstraNode &_toCompare) const
{
	return  _toCompare.cost < cost;
}