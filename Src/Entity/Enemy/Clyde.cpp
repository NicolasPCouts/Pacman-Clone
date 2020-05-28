#include "Clyde.h"

#include "../../Tile.h"
#include "../../GameManager.h"
#include "../Pacman/Pacman.h"

extern GameManager* gameManager;

Clyde::Clyde(sf::Vector2i gridPos) : Enemy(gridPos, sf::Vector2i(230, 113)) {	}
Clyde::~Clyde() {	}


sf::Vector2i Clyde::GetScatterTargetPosition()
{
	return sf::Vector2i(1, 29);
}

sf::Vector2i Clyde::GetChaseTargetPosition()
{
	if (sTile::GetDistanceBetweenTiles(gridPos, gameManager->pacman->gridPos) > 8)
		return gameManager->pacman->gridPos;
	
	return sf::Vector2i(1, 29);
}

void Clyde::SetupAnimations()
{

}