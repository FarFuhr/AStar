#pragma once

#include "Point.h"

#include <vector>

namespace AStar
{
	bool checkPassable(const Point& p, const unsigned char* pMap, const int nMapWidth);

	std::vector<Point> getFreeNeighbors(const int nPosX, const int nPosY,
										const unsigned char* pMap, const int nMapWidth, const int nMapHeight);
	std::vector<Point> getFreeNeighbors(const Point& pos, const unsigned char* pMap, const int nMapWidth, const int nMapHeight);

	int heuristic(int startX, int startY, int targetX, int targetY);
	int heuristic(const Point& start, const Point& target);

	int FindPath(const int nStartX, const int nStartY,
		const int nTargetX, const int nTargetY,
		const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
		int* pOutBuffer, const int nOutBufferSize);
}
