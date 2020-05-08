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
			if (&left != NULL)	neighbours.push_back(left);
		}
		if (ignoreDirection != Right) {
			sNode right = CreateNode(sf::Vector2i(pos.x + 1, pos.y));
			if (&right != NULL)	neighbours.push_back(right);
		}
		if (ignoreDirection != Up) {
			sNode up = CreateNode(sf::Vector2i(pos.x, pos.y - 1));
			if (&up != NULL)	neighbours.push_back(up);
		}
		if (ignoreDirection != Down) {
			sNode down = CreateNode(sf::Vector2i(pos.x, pos.y + 1));
			if (&down != NULL)	neighbours.push_back(down);
		}

		return neighbours;
	}

	sNode CreateNode(sf::Vector2i pos) 
	{
		sTile* tile = &gameManager->tileArray[pos.x][pos.y];
		sNode node = sNode(pos);
		if (tile != NULL) {
			if (tile->tileType == sTile::Wall)
				node.walkable = false;
			else
				node.walkable = true;

			return node;
		}
	}
};

std::vector<sf::Vector2i> FindPath(sf::Vector2i startNode, sf::Vector2i endNode, Directions currentDir);