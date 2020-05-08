#include "Entity.h"

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

void Entity::Draw(sf::RenderWindow& rw)
{
	rw.draw(body);
}