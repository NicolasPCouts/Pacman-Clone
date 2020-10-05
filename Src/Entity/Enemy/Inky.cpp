#include "Inky.h"
#include "../Pacman/Pacman.h"
#include "../../States/GameState/GameState.h"

Inky::Inky(sf::Vector2i gridPos, GameState* gameState)
	: Enemy(gridPos, sf::Vector2i(230, 97), gameState, Entities::Inky)
{
	SetupAnimations();
}

Inky::~Inky() {	}

sf::Vector2i Inky::GetScatterTargetPosition()
{
	return sf::Vector2i(26, 29);
}

sf::Vector2i Inky::GetChaseTargetPosition()
{
	sf::Vector2i dist;
	switch (gameState->pacman->currentDir)
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
	sf::Vector2i pacmanPos = gameState->pacman->gridPos;
	sf::Vector2i blinkyPos = gameState->enemys[0]->gridPos;

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

	return finalPos;
}

void Inky::SetupAnimations()
{
	sf::Texture r1, r2, l1, l2;
	r1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 97, 14, 14));
	r2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(246, 97, 14, 14));
	l1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(262, 97, 14, 14));
	l2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(278, 97, 14, 14));
	std::vector<sf::Texture> leftAnimTextures{ l1,l2 };
	std::vector<sf::Texture> rightAnimTextures{ r1,r2 };

	sf::Texture u1, u2, d1, d2;
	u1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(294, 97, 14, 14));
	u2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(310, 97, 14, 14));
	d1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(326, 97, 14, 14));
	d2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(342, 97, 14, 14));
	std::vector<sf::Texture> upAnimTextures{ u1,u2 };
	std::vector<sf::Texture> downAnimTextures{ d1,d2 };

	animations[0] = new Animation(leftAnimTextures, true, 0.1f);
	animations[1] = new Animation(rightAnimTextures, true, 0.1f);
	animations[2] = new Animation(upAnimTextures, true, 0.1f);
	animations[3] = new Animation(downAnimTextures, true, 0.1f);
}