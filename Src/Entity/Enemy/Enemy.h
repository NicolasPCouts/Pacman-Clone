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
	EnemyState state = Scatter;
	std::vector<sf::Vector2i> currentPath;
	void UpdateEnemyTilePosition();
	Enemy(int tileX, int tileY);
	~Enemy();
	void UpdateTileArray(sf::Vector2i newPos) override;
	void Move() override;
	void Update() override;
	void Draw(sf::RenderWindow& rw) override;
};