#pragma once
#include "Enemy.h"

class Pinky : public Enemy
{
public:
	Pinky(sf::Vector2i gridPos, GameState* gameState);
	~Pinky();
private:
	sf::Vector2i GetChaseTargetPosition() override;
	void SetupAnimations() override;
};


