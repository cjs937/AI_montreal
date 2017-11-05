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
			DijkstraNode()
			{
				node = NULL;
				connection = NULL;
				cost = 0;
			}

			DijkstraNode(DijkstraNode* _copy)
			{
				node = _copy->node;
				connection = _copy->connection;
				cost = _copy->cost;
			}

			DijkstraNode(Node* _node, DijkstraNode* _connection, float _weight) : node(_node), connection(_connection), cost(_weight)
			{};

			~DijkstraNode() 
			{
			};

			bool operator<(const DijkstraNode &_toCompare) const
			{
				return  _toCompare.cost < cost;
			}

			Node* node;
			DijkstraNode* connection;
			float cost;
	};

public:
	DijkstraPathfinder(GridGraph* pGraph);
	~DijkstraPathfinder();

	const Path& findPath(Node* pFrom, Node* pTo);

private:

	DijkstraNode getNodeInOpenList(Node* node, std::priority_queue<DijkstraNode> openList);
};
