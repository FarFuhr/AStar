#pragma once

struct Point
{
	int x;
	int y;
	int priority; // move cost + heuristic to cut off not relevant points
	int mapWidth;

	Point(int x_ = 0, int y_ = 0, int mapWidth_ = 0, int priority_ = 0) 
		: x(x_), y(y_), mapWidth(mapWidth_), priority(priority_)
	{}
	
	int toIndex() const
	{
		return y * mapWidth + x;
	}
	
	bool operator == (const Point& rhs) const
	{
		return x == rhs.x && y == rhs.y; 
	}

	bool operator != (const Point& rhs) const
	{
		return x != rhs.x || y != rhs.y; 
	}
	
	bool operator < (const Point& rhs) const 
	{ 
		return toIndex() < rhs.toIndex(); 
	}
};

class PriorityComparator
{
public:
	bool operator() (const Point& lhs, const Point& rhs) const
	{
		return lhs.priority > rhs.priority;
	}
};
