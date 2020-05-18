#pragma once
#include "Enemy.h"

class Pinky : public Enemy
{
public:
	Pinky(sf::Vector2i gridPos);
	~Pinky();
private:
	sf::Vector2i GetChaseTargetPosition() override;
};


