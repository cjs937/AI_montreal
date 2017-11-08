#pragma once
#include "GridPathfinder.h"
#include <queue>

class Node;

class AStarPathfinder : public GridPathfinder
{
public:

	struct AStarNode : public Trackable
	{
	public:
		AStarNode();

		AStarNode(AStarNode* _copy);
		AStarNode(Node* _node, AStarNode* _connection = NULL, float _weight = 0.0f, float _totalCost = 0.0f);

		~AStarNode();

		bool operator<(const AStarNode &_toCompare) const;
		bool operator==(const Node* &_node) const;

		bool operator==(const AStarNode &_node) const;

		Node* node;
		AStarNode* connection;
		float cost;
		float heuristicCostEstimate;
	};

	struct AStarState
	{
	public:
		AStarState(Node* _goal):goalNode(_goal) {};

		~AStarState() 
		{
			for (int i = 0; i < coverage.size(); ++i)
			{
				delete coverage[i];
				coverage[i] = NULL;
			}
		};

		AStarNode currentNode;
		std::priority_queue<AStarNode> openList;
		std::vector<AStarNode> closedList;
		std::vector<AStarNode*> coverage;
		Node* goalNode;
	};

	AStarPathfinder(GridGraph* _graph);
	~AStarPathfinder();

	const Path& findPath(Node* pFrom, Node* pTo);

	virtual PathfinderType getType() { return ASTAR; };

private:
	AStarNode getNodeInOpenList(Node* node, std::priority_queue<AStarNode> openList);
	void evaluateConnections(AStarState &_currentState);
	Path& generatePath(AStarState &_currentState);
	float getHeuristic(AStarNode _node, Node* _goal);
};