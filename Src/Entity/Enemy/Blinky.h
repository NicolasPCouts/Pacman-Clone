#pragma once
#include "Enemy.h"

class Blinky : public Enemy
{
public:
	Blinky(sf::Vector2i gridPos);
	~Blinky();
private:
	sf::Vector2i GetScatterTargetPosition() override;
	void SetupAnimations() override;
};

