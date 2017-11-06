#pragma once
#include "GridPathfinder.h"
#include <queue>
class GridGraph;
class Node;
class Connection;


class DijkstraPathfinder : public GridPathfinder
{
	struct DijkstraNode : public Trackable
	{
		public:
			DijkstraNode();

			DijkstraNode(DijkstraNode* _copy);

			DijkstraNode(Node* _node, DijkstraNode* _connection = NULL, float _weight = 0.0f);

			~DijkstraNode();

			bool operator<(const DijkstraNode &_toCompare) const;

			Node* node;
			DijkstraNode* connection;
			float cost;
	};

public:
	DijkstraPathfinder(GridGraph* pGraph);
	~DijkstraPathfinder();

	const Path& findPath(Node* pFrom, Node* pTo);

	PathfinderType getType() { return DIJKSTRA; };

private:

	DijkstraNode getNodeInOpenList(Node* node, std::priority_queue<DijkstraNode> openList);
};
