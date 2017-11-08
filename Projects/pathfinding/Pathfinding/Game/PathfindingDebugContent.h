#pragma once

#include "DebugContent.h"

class GridPathfinder;

class PathfindingDebugContent:public DebugContent
{
public:
	PathfindingDebugContent( GridPathfinder* pPathfinder );
	~PathfindingDebugContent(){};

	std::string getDebugString();
	void setPathfinder(GridPathfinder* _newPathfinder) { mpPathfinder = _newPathfinder; };
private:
	GridPathfinder* mpPathfinder;
};