#include "Entity.h"
#include "../GameManager.h"

extern GameManager* gameManager;

Directions GetOppositeDirection(Directions dir) 
{
	switch (dir)
	{
    case Up:
        return Down;
        break;
    case Down:
        return Up;
        break;
    case Left:
        return Right;
        break;
    case Right:
        return Left;
        break;
	}
    return None;
}

sf::Vector2f Entity::GetFinalTilePosition()
{
    return sf::Vector2f(gridPos.x * gameManager->tileWidth, gridPos.y * gameManager->tileHeight);
}
