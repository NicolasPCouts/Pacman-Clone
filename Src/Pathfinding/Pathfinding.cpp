#include "Pathfinding.h"
#include "Node.h"
#include "../Entity/Entity.h"

bool IsNodeInsideList(sNode& n, std::vector<sNode>& list) 
{
	for (sNode node : list)
	{
		if (node.pos == n.pos)
			return true;
	}
	return false;
}

void DeleteNodeOnList(sNode& n, std::vector<sNode>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].pos == n.pos) {
			list.erase(list.begin() + i);
			break;
		}
	}
}

int GetDistance(sNode& a, sNode& b)
{
	int disX = a.pos.x - b.pos.x;
	int disY = a.pos.y - b.pos.y;

	if(disX < 0)
		disX *= -1;
	if(disY < 0)
		disY *= -1;

	int totalDis = disX + disY;
	
	return totalDis;
}

std::vector<sf::Vector2i> FindPath(sf::Vector2i startNodePos, sf::Vector2i endNodePos, Directions currentDir, GameState* gameState)
{
	std::vector<sNode> openList;
	std::vector<sNode> closedList;

	sNode startNode = sNode(startNodePos, gameState);
	sNode endNode = sNode(endNodePos, gameState);
	startNode.ignoreDirection = GetOppositeDirection(currentDir);
	openList.push_back(startNode);

	bool foundPath = false;

	sNode currentNode = openList[0];
	while(!openList.empty())
	{
		currentNode = openList[0];
		int i = 0;
		for(; i < openList.size(); i++)
		{
			if (openList[i].fCost() < currentNode.fCost() || (openList[i].fCost() == currentNode.fCost() && openList[i].hCost < currentNode.hCost))
			{
				currentNode = openList[i];
			}
		}

		DeleteNodeOnList(currentNode, openList);
		closedList.push_back(currentNode);

		if (currentNode.pos == endNodePos)
		{
			foundPath = true;
			break;
		}

		std::vector<sNode> neighbours = currentNode.GetNeighbours();
		for (sNode neighbour : neighbours) 
		{
			if (!neighbour.walkable || IsNodeInsideList(neighbour, closedList))
				continue;

			int newMovementCostToNeighbour = currentNode.gCost + GetDistance(currentNode, neighbour);
			if(newMovementCostToNeighbour < neighbour.gCost || !IsNodeInsideList(neighbour, openList))
			{
				neighbour.gCost = newMovementCostToNeighbour;
				neighbour.hCost = GetDistance(neighbour, endNode);
				neighbour.SetParent(currentNode);

				if (!IsNodeInsideList(neighbour, openList))
					openList.push_back(neighbour);
			}
		}
	}

	if (foundPath)
	{
		std::vector<sf::Vector2i> pathPositionsList;
		while (currentNode.pos != startNode.pos)
		{
			pathPositionsList.push_back(currentNode.pos);
			currentNode = *currentNode.parent;
		}
		std::reverse(pathPositionsList.begin(), pathPositionsList.end());
		return pathPositionsList;
	}
	else
		return std::vector<sf::Vector2i>();
}