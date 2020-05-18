#include "Pinky.h"

#include "../../GameManager.h"
#include "../Pacman/Pacman.h"

extern GameManager* gameManager;

Pinky::Pinky(sf::Vector2i gridPos) : Enemy(gridPos, sf::Vector2i(230, 81)) {	}
Pinky::~Pinky() {	}

sf::Vector2i Pinky::GetChaseTargetPosition()
{
	sf::Vector2i pos = gameManager->pacman->gridPos;
	switch (gameManager->pacman->currentDir)
	{
	case Up:
		pos.y -= 2;
		break;
	case Down:
		pos.y += 2;
		break;
	case Left:
		pos.x -= 2;
		break;
	case Right:
		pos.x += 2;
		break;
	}

	return pos;
}
