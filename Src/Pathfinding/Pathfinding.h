#pragma once

#include "../GameManager.h"
#include "../Common.h"

struct sNode 
{
	sNode* parent = NULL;

	sf::Vector2i pos;

	int gCost;
	int hCost;
	int fCost(){ return gCost + hCost; }

	bool visited = false;

	sNode(sf::Vector2i pos) { this->pos = pos; }
};

static class Pathfinding
{
public:
	void FindPath(sf::Vector2i startNode, sf::Vector2i endNode);
private:

};