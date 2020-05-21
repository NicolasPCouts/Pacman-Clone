#include "Inky.h"

#include "../../GameManager.h"
#include "../Pacman/Pacman.h"

extern GameManager* gameManager;

Inky::Inky(sf::Vector2i gridPos) : Enemy(gridPos, sf::Vector2i(230, 97)) {	}
Inky::~Inky() {	}

sf::Vector2i Inky::GetScatterTargetPosition()
{
	return sf::Vector2i(26, 29);
}

sf::Vector2i Inky::GetChaseTargetPosition()
{
	sf::Vector2i dist;
	switch (gameManager->pacman->currentDir)
	{
	Up:
		dist.y -= 2;
		break;
	Down:
		dist.y += 2;
		break;
	Left:
		dist.x -= 2;
		break;
	Right:
		dist.x += 2;
		break;
	}
	sf::Vector2i pacmanPos = gameManager->pacman->gridPos;
	sf::Vector2i blinkyPos = gameManager->enemys[0]->gridPos;

	if (pacmanPos.x < blinkyPos.x)
		dist.x = blinkyPos.x - pacmanPos.x;
	else
		dist.x = pacmanPos.x - blinkyPos.x;

	if (pacmanPos.y < blinkyPos.y)
		dist.y = blinkyPos.y - pacmanPos.y;
	else
		dist.y = pacmanPos.y - blinkyPos.y;

	dist *= 2;

	sf::Vector2i finalPos;
	if (gridPos.x + dist.x > NumberOfTilesX - 2)	finalPos.x = NumberOfTilesX - 2;
	else if (gridPos.x + dist.x < 1)	finalPos.x = 1;
	else finalPos.x = gridPos.x + dist.x;

	if (gridPos.y + dist.y > NumberOfTilesY - 2)	finalPos.y = NumberOfTilesY - 2;
	else if (gridPos.y + dist.y < 1)	finalPos.y = 1;
	else finalPos.y = gridPos.y + dist.y;

	std::cout << "X : " << finalPos.x << " Y : " << finalPos.y << std::endl;

	return finalPos;
}