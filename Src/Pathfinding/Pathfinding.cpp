#include "Pathfinding.h"


void Pathfinding::FindPath(sf::Vector2i startNode, sf::Vector2i endNode)
{
	std::vector<sNode> openList;
	std::vector<sNode> openList;

	openList.push_back(sNode(startNode));

	while(!openList.empty())
	{
		sNode currentNode = openList[0];

		for(sNode n : openList)
		{
			if (n.fCost() < currentNode.fCost() || n.fCost() == currentNode.fCost() && n.hCost < currentNode.hCost) {
				currentNode = n;

			}
		}

		
	}
}
