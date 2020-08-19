#pragma once
#include "Enemy.h"

class Clyde : public Enemy
{
public:
	Clyde(sf::Vector2i gridPos, GameState* gameState);
	~Clyde();
private:
	sf::Vector2i GetScatterTargetPosition() override;
	sf::Vector2i GetChaseTargetPosition() override;
	void SetupAnimations() override;
};