#pragma once

#include "../GameManager.h"
#include "../Common.h"

extern GameManager* gameManager;

struct sNode 
{
	sNode* parent;
	Directions ignoreDirection = Directions::None;
	sf::Vector2i pos;

	int gCost = 0;
	int hCost = 0;
	int fCost(){ return (gCost + hCost); }

	bool visited = false;
	bool walkable = true;

	sNode(sf::Vector2i pos) { this->pos = pos; }

	void SetParent(sNode p)
	{
		parent = new sNode(p);
	}

	std::vector<sNode> GetNeighbours() 
	{
		std::vector<sNode> neighbours;
		if (ignoreDirection != Left) {
			sNode left = CreateNode(sf::Vector2i(pos.x - 1, pos.y));
			if (left.pos != sf::Vector2i(-100, -100))	neighbours.push_back(left);
		}
		if (ignoreDirection != Right) {
			sNode right = CreateNode(sf::Vector2i(pos.x + 1, pos.y));
			if (right.pos != sf::Vector2i(-100, -100))	neighbours.push_back(right);
		}
		if (ignoreDirection != Up) {
			sNode up = CreateNode(sf::Vector2i(pos.x, pos.y - 1));
			if (up.pos != sf::Vector2i(-100, -100))	neighbours.push_back(up);
		}
		if (ignoreDirection != Down) {
			sNode down = CreateNode(sf::Vector2i(pos.x, pos.y + 1));
			if (down.pos != sf::Vector2i(-100, -100))	neighbours.push_back(down);
		}

		return neighbours;
	}

	sNode CreateNode(sf::Vector2i pos) 
	{
		sTile* tile = &gameManager->tileArray[pos.x][pos.y];
		sNode node = sNode(pos);
		if (tile != NULL) {

			if(pos.x < 0 || pos.y < 0 || pos.x >= gameManager->numberOfTilesX || pos.y >= gameManager->numberOfTilesY)
				return sNode(sf::Vector2i(-100, -100));

			if (tile->tileType == sTile::Wall)
				node.walkable = false;
			else
				node.walkable = true;

			return node;
		}
		return sNode(sf::Vector2i(-100, -100));
	}
};

std::vector<sf::Vector2i> FindPath(sf::Vector2i startNode, sf::Vector2i endNode, Directions currentDir);