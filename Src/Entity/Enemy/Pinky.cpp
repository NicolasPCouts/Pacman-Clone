#include "Pinky.h"

#include "../../GameManager.h"
#include "../Pacman/Pacman.h"

extern GameManager* gameManager;

Pinky::Pinky(sf::Vector2i gridPos) : Enemy(gridPos, sf::Vector2i(230, 81)) 
{
	
}

Pinky::~Pinky() {	}

sf::Vector2i Pinky::GetChaseTargetPosition()
{
	sf::Vector2i pos = gameManager->pacman->gridPos;
	switch (gameManager->pacman->currentDir)
	{
	case Up:
		pos.y -= 4;
		break;
	case Down:
		pos.y += 4;
		break;
	case Left:
		pos.x -= 4;
		break;
	case Right:
		pos.x += 4;
		break;
	}

	return pos;
}
