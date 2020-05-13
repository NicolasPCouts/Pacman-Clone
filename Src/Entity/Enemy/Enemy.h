#pragma once

#include "../Entity.h"

enum EnemyState {
	Scatter,
	Chase,
	Frightened,
	Eaten
};


class Enemy : Entity
{
public:
	float speed;
	Enemy(int tileX, int tileY);
	~Enemy();
	void Move() override;
	void Draw(sf::RenderWindow& rw) override;
};