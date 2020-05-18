#pragma once
#include "Enemy.h"

class Blinky : public Enemy
{
public:
	Blinky(sf::Vector2i gridPos);
	~Blinky();
	sf::Vector2i GetScatterTargetPosition() override;
};

