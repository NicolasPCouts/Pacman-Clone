#include "Blinky.h"
#include "../../States/GameState/GameState.h"

Blinky::Blinky(sf::Vector2i gridPos, GameState* gameState)
	: Enemy(gridPos, sf::Vector2i(230, 65), gameState, Entities::Blinky)
{
	SetupAnimations();
}

Blinky::~Blinky() {	}

sf::Vector2i Blinky::GetScatterTargetPosition()
{
	return sf::Vector2i(26,1);
}

void Blinky::SetupAnimations()
{
	sf::Texture r1, r2, l1, l2;
	r1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 65, 14, 14));
	r2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(246, 65, 14, 14));
	l1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(262, 65, 14, 14));
	l2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(278, 65, 14, 14));
	std::vector<sf::Texture> leftAnimTextures{ l1,l2 };
	std::vector<sf::Texture> rightAnimTextures{ r1,r2 };

	sf::Texture u1, u2, d1, d2;
	u1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(294, 65, 14, 14));
	u2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(310, 65, 14, 14));
	d1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(326, 65, 14, 14));
	d2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(342, 65, 14, 14));
	std::vector<sf::Texture> upAnimTextures{ u1,u2 };
	std::vector<sf::Texture> downAnimTextures{ d1,d2 };

	animations[0] = new Animation(leftAnimTextures, true, 0.1f);
	animations[1] = new Animation(rightAnimTextures, true, 0.1f);
	animations[2] = new Animation(upAnimTextures, true, 0.1f);
	animations[3] = new Animation(downAnimTextures, true, 0.1f);
}