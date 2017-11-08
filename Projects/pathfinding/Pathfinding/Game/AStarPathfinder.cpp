#include "AStarPathfinder.h"
#include <queue>
#include "Connection.h"
#include "Graph.h"
#include "Node.h"
#include "Grid.h"
#include "GameApp.h"
#include "Vector2D.h"
#include "PerformanceTracker.h"

AStarPathfinder::AStarPathfinder(GridGraph* _graph):GridPathfinder(_graph, Color(BLUE))
{}

AStarPathfinder::~AStarPathfinder()
{}

const Path& AStarPathfinder::findPath(Node* pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	AStarState currentState = AStarState(pTo);

	AStarNode startNode = AStarNode(pFrom);
	startNode.heuristicCostEstimate = getHeuristic(startNode, currentState.goalNode);

	currentState.openList.push(startNode);

	currentState.currentNode = currentState.openList.top();

	while (currentState.currentNode.node != currentState.goalNode && currentState.openList.size() > 0)
	{
		currentState.openList.pop();

		evaluateConnections(currentState);

		currentState.closedList.push_back(currentState.currentNode);

		currentState.currentNode = currentState.openList.top();
	}

	//No result found
	if (currentState.currentNode.node != currentState.goalNode)
	{
		std::cout << "No path was found.\n";
		return mPath;
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	return generatePath(currentState);
}

void AStarPathfinder::evaluateConnections(AStarState &_currentState)
{
	std::vector<Connection*> connections = mpGraph->getConnections(*_currentState.currentNode.node);
	std::vector<AStarNode>::iterator closedListIter;

	for (size_t i = 0; i < connections.size(); ++i)
	{
		AStarNode tempNode;
		Node* connectionNode = connections[i]->getToNode();
		AStarNode* newConnection = NULL;
		float newCost = _currentState.currentNode.cost + connections[i]->getCost();
		float newHeuristic = 0;

		// if node is in closed list
		if ((closedListIter = std::find(_currentState.closedList.begin(), _currentState.closedList.end(), connectionNode)) != _currentState.closedList.end())
		{
			tempNode = *closedListIter;

			if (tempNode.cost <= newCost)
			{
				continue;
			}

			newHeuristic = tempNode.heuristicCostEstimate - tempNode.cost;

			_currentState.closedList.erase(closedListIter);

		}
		// if node is in open list
		else if ((tempNode = getNodeInOpenList(connectionNode, _currentState.openList)).node != NULL)
		{
			if (tempNode.cost <= newCost)
			{
				continue;
			}

			newHeuristic = tempNode.heuristicCostEstimate - tempNode.cost;

		}
		// if node is unvisited
		else
		{
			tempNode = AStarNode(connectionNode);

			newHeuristic = getHeuristic(connectionNode, _currentState.goalNode);
		}

		tempNode.cost = newCost;

		tempNode.connection = new AStarNode(&_currentState.currentNode);
		_currentState.coverage.push_back(tempNode.connection);

		tempNode.heuristicCostEstimate = newCost + newHeuristic;

		_currentState.openList.push(tempNode);
	}
}

Path& AStarPathfinder::generatePath(AStarState &_currentState)
{ 
	//generates a temporary path going from goal to start
	std::vector<Node*> tempPath;

	AStarNode* toAdd = new AStarNode(&_currentState.currentNode);
	_currentState.coverage.push_back(toAdd);

	//loops until it reaches start node
	while (toAdd != NULL)
	{
		tempPath.push_back(toAdd->node);

		toAdd = toAdd->connection;
	}

	//clears current path
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


AStarPathfinder::AStarNode AStarPathfinder::getNodeInOpenList(Node* _node, std::priority_queue<AStarNode> _openList)
{
	AStarNode currentNode;

	while (_openList.size() > 0)
	{
		currentNode = _openList.top();

		if (currentNode.node == _node)
			return currentNode;

		_openList.pop();
	}

	return AStarNode();
}


float AStarPathfinder::getHeuristic(AStarNode _node, Node* _goal)
{
	float toReturn;

	GameApp* game = static_cast<GameApp*>(gpGame);

	Vector2D nodePos = game->getGrid()->getULCornerOfSquare(_node.node->getId());
	Vector2D goalPos = game->getGrid()->getULCornerOfSquare(_goal->getId());

	//distance from node to goal
	//sqrt((x1 - x2)^2 + (y1 - y2)^2))
	float vecDistance = sqrt( ( ( nodePos.getX() - goalPos.getX() ) * ( nodePos.getX() - goalPos.getX() ) + ( nodePos.getY() - goalPos.getY() ) * ( nodePos.getY() - goalPos.getY() ) ) );

	toReturn = abs(vecDistance);

	
	return toReturn;
}

AStarPathfinder::AStarNode::AStarNode()
{
	node = NULL;
	connection = NULL;
	cost = 0;
	heuristicCostEstimate = 0;
}

AStarPathfinder::AStarNode::AStarNode(AStarNode* _copy)
{
	node = _copy->node;
	connection = _copy->connection;
	cost = _copy->cost;
	heuristicCostEstimate = _copy->heuristicCostEstimate;
}

AStarPathfinder::AStarNode::AStarNode(Node* _node, AStarNode* _connection, float _weight, float _totalCost) : node(_node), connection(_connection), cost(_weight), heuristicCostEstimate(_totalCost)
{};

AStarPathfinder::AStarNode::~AStarNode()
{};

bool AStarPathfinder::AStarNode::operator<(const AStarNode &_toCompare) const
{
	bool toReturn = _toCompare.heuristicCostEstimate < heuristicCostEstimate;

	return toReturn;
}

bool AStarPathfinder::AStarNode::operator==(const Node* &_node) const
{
	return node == _node;
}

bool AStarPathfinder::AStarNode::operator==(const AStarNode &_node) const
{
	return node == _node.node;
}
