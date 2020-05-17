#pragma once

#include "../Entity.h"

enum class EnemyState {
	Scatter,
	Chase,
	Frightened,
	Eaten
};

class Enemy : Entity
{
public:
	EnemyState state = EnemyState::Scatter;
	std::vector<sf::Vector2i> currentPath;
	Enemy(int tileX, int tileY);
	~Enemy();
	void UpdateEnemyTilePosition();
	sf::Vector2i GetOppositeDirectionNeighbour();
	void UpdateTileArray(sf::Vector2i newPos) override;
	void Move() override;
	void Update() override;
	void Draw(sf::RenderWindow& rw) override;
};