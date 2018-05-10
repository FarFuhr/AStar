#include "AStar.h"
#include "Point.h"

#include <vector>
#include <queue>
#include <map>
#include <list>

#include <cmath>

#include <functional>

bool AStar::checkPassable(const Point& p, const unsigned char* pMap, const int nMapWidth)
{
	return (pMap[p.toIndex()] != 0);
}

std::vector<Point> AStar::getFreeNeighbors(const int nPosX, const int nPosY,
										   const unsigned char* pMap, const int nMapWidth, const int nMapHeight)
{
	std::vector<Point> ret;

	Point buf;
	buf.mapWidth = nMapWidth;
	if (nPosX > 0) // left
	{
		buf.x = nPosX - 1;
		buf.y = nPosY;
		if (checkPassable(buf, pMap, nMapWidth))
			ret.push_back(buf);
	}
	if (nPosX < nMapWidth - 1) // right
	{
		buf.x = nPosX + 1;
		buf.y = nPosY;
		if (checkPassable(buf, pMap, nMapWidth))
			ret.push_back(buf);
	}
	if (nPosY > 0) // bottom
	{
		buf.x = nPosX;
		buf.y = nPosY - 1;
		if (checkPassable(buf, pMap, nMapWidth))
			ret.push_back(buf);
	}
	if (nPosY < nMapHeight - 1) // top
	{
		buf.x = nPosX;
		buf.y = nPosY + 1;
		if (checkPassable(buf, pMap, nMapWidth))
			ret.push_back(buf);
	}

	return ret;
}

std::vector<Point> AStar::getFreeNeighbors(const Point& pos, const unsigned char* pMap, const int nMapWidth, const int nMapHeight)
{
	return getFreeNeighbors(pos.x, pos.y, pMap, nMapWidth, nMapHeight);
}

int AStar::heuristic(int startX, int startY, int targetX, int targetY)
{
	return std::abs(targetX - startX) + std::abs(targetY - startY);
}

int AStar::heuristic(const Point& start, const Point& target)
{
	return heuristic(start.x, start.y, target.x, target.y);
}

int AStar::FindPath(const int nStartX, const int nStartY,
					const int nTargetX, const int nTargetY,
					const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
					int* pOutBuffer, const int nOutBufferSize)
{
	// We want to process only most cheap points, so we should
	// contain frontier in priority queue and use (move cost + heuristic) as priority
	std::priority_queue<Point, std::vector<Point>, PriorityComparator> frontier;

	std::map<Point, Point> cameFrom;
	// cost for moving in this cell from start cell
	std::map<Point, int> farCost;

	// we don't want to process one point several times
	std::vector<Point> processed; 

	Point start(nStartX, nStartY, nMapWidth);
	Point target(nTargetX, nTargetY, nMapWidth);
	frontier.push(start);
	farCost[start] = 0;

	processed.push_back(start);
	while (!frontier.empty())
	{
		Point current = frontier.top();
		frontier.pop();

		if (current == target)
		{
			std::list<int> path;

			for (auto next = target; next != start; next = cameFrom[next])
			{
				path.push_front(next.toIndex());
			}

			if (path.size() > nOutBufferSize) // I didn't understand from task what to do in this situation, so only error
				return -1;
			else
			{
				std::copy(path.begin(), path.end(), pOutBuffer); // std::copy is not safe, but now we're sure that everything is correct
				return path.size();
			}
		}

		for (auto next : getFreeNeighbors(current, pMap, nMapWidth, nMapHeight))
		{
			if (std::find(processed.begin(), processed.end(), next) != processed.end())
				continue;

			int cost = farCost[current] + 1; // we'll move only horizontal or vertical
			if (farCost.find(next) == farCost.end()
				|| cost < farCost[next])
			{
				farCost[next] = cost;
				int priority = cost + heuristic(next, target);
				next.priority = priority;
				frontier.push(next);
				cameFrom[next] = current;
			}
			processed.push_back(next);
		}
	}

	return -1;
}