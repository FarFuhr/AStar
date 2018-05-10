#include <iostream>

#include "AStar.h"

int main()
{
	unsigned char pMap[] = { 
		1, 1, 1, 0, 1, 1, 
		1, 1, 1, 0, 1, 1,
		1, 1, 1, 0, 1, 1,
		1, 0, 0, 1, 1, 1, 
		1, 1, 1, 1, 0, 1
	};
	int pOutBuffer[16];
	std::cout << AStar::FindPath(0, 0, 5, 4, pMap, 6, 5, pOutBuffer, 16) << std::endl;
	std::cin.get();
	return 0;
}