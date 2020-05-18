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
	EnemyState state = EnemyState::Chase;
	Enemy(sf::Vector2i gridPos, sf::Vector2i texturePos);
	~Enemy();
	void UpdateTileArray(sf::Vector2i newPos) override;
	void Update() override;
	void Draw(sf::RenderWindow& rw) override;
private:
	std::vector<sf::Vector2i> currentPath;
	void UpdateEnemyTilePosition();
	sf::Vector2i GetOppositeDirectionNeighbour();
	void Move() override;
protected:
	virtual sf::Vector2i GetScatterTargetPosition();
	virtual sf::Vector2i GetChaseTargetPosition();
};
