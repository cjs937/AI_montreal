#include "AStarPathfinder.h"
#include <queue>
#include "Connection.h"
#include "Graph.h"
#include "Node.h"
#include "Grid.h"
#include "GameApp.h"
#include "Vector2D.h"

AStarPathfinder::AStarPathfinder(GridGraph* _graph):GridPathfinder(_graph, Color(BLUE))
{}

AStarPathfinder::~AStarPathfinder()
{}

const Path& AStarPathfinder::findPath(Node* pFrom, Node* pTo)
{
	std::priority_queue<AStarNode> openList;
	std::vector<AStarNode> closedList;
	std::vector<AStarNode>::iterator closedListIter;

	AStarNode startNode = AStarNode(pFrom);
	startNode.heuristicCostEstimate = getHeuristic(startNode, pTo);

	openList.push(startNode);

	AStarNode currentNode = openList.top();
	bool here = false;

	while (currentNode.node != pTo && openList.size() > 0)
	{
		openList.pop();

		std::vector<Connection*> connections = mpGraph->getConnections(*currentNode.node);

		for (size_t i = 0; i < connections.size(); ++i)
		{
			AStarNode tempNode;
			Node* connectionNode = connections[i]->getToNode();
			AStarNode* newConnection = NULL;
			float newCost = currentNode.cost + connections[i]->getCost();
			float newHeuristic = 0;

			// if node is in closed list
			if ((closedListIter = std::find(closedList.begin(), closedList.end(), connectionNode)) != closedList.end())
			{
				tempNode = *closedListIter;

				if (tempNode.cost <= newCost)
				{
					continue;
				}

				//if (tempNode.connection != NULL)
				//{
				//	delete tempNode.connection;

				//	tempNode.connection = NULL;
				//}

				newHeuristic = tempNode.heuristicCostEstimate - tempNode.cost;

				closedList.erase(closedListIter);

			}
			// if node is in open list
			else if ((tempNode = getNodeInOpenList(connectionNode, openList)).node != NULL)
			{
				if (tempNode.cost <= newCost)
				{
					continue;
				}

				//if (tempNode.connection != NULL)
				//{
				//	delete tempNode.connection;

				//	tempNode.connection = NULL;
				//}

				newHeuristic = tempNode.heuristicCostEstimate - tempNode.cost;

				continue;
			}
			// if node is unvisited
			else
			{
				tempNode = AStarNode(connectionNode);

				newHeuristic = getHeuristic(connectionNode, pTo);
			}

			tempNode.cost = newCost;
			
			tempNode.connection = new AStarNode(&currentNode);

			tempNode.heuristicCostEstimate = newCost + newHeuristic;

			openList.push(tempNode);
		}

		closedList.push_back(currentNode);

		currentNode = openList.top();
	}

	//No result found
	if (currentNode.node != pTo)
	{
		std::cout << "No path was found.\n";
		return mPath;
	}

	//clears current path
	mPath.clear();
	mVisitedNodes.clear();

	//generates a temporary path going from goal to start
	std::vector<Node*> tempPath;

	AStarNode* toAdd = new AStarNode(&currentNode);
	AStarNode* prevNode = NULL;

	while (true)
	{
		tempPath.push_back(toAdd->node);

		//if this is start node
		if (toAdd->connection == NULL)
		{
			//delete toAdd;

			break;
		}

//		prevNode = toAdd;

		toAdd = toAdd->connection;

		//delete prevNode;

		//prevNode = toAdd;
	}

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
	//sqrt((x1 - x2)^2 + (y1 + y2)^2))
	float vecDistance = sqrt( ( ( nodePos.getX() - goalPos.getX() ) * ( nodePos.getX() - goalPos.getX() ) + ( nodePos.getY() + goalPos.getY() ) * ( nodePos.getY() + goalPos.getY() ) ) );

	//only goes upwards??
	toReturn = abs(vecDistance);

	//only goes downwards????
	//toReturn = _goal->getId() - _node.node->getId();
	
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
