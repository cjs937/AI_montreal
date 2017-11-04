#pragma once
#include "GridPathfinder.h"

class GridGraph;
class Node;
class Connection;


class DijkstraPathfinder : public GridPathfinder
{
	struct DijkstraNode
	{
		public:
			DijkstraNode(Node* _node, DijkstraNode* _connection, float _weight) : node(_node), connection(_connection), cost(_weight)
			{};

			~DijkstraNode() {};

			bool operator<(DijkstraNode* _toCompare)
			{
				return cost < _toCompare->cost;
			}

			Node* node;
			DijkstraNode* connection;
			float cost;
	};

public:
	DijkstraPathfinder(GridGraph* pGraph);
	~DijkstraPathfinder();

	const Path& findPath(Node* pFrom, Node* pTo);
};
