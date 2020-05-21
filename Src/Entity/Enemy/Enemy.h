#pragma once

#include "../Entity.h"

enum class EnemyState {
	Scatter,
	Chase,
	Frightened,
	Eaten
};

class Enemy : public Entity
{
public:
	EnemyState state = EnemyState::Scatter;
	Enemy(sf::Vector2i gridPos, sf::Vector2i texturePos);
	~Enemy();
	void UpdateTileArray(sf::Vector2i newPos) override;
	void Update() override;
	void Draw(sf::RenderWindow& rw) override;
private:
	struct Wave {
		EnemyState waveState;
		float duration;
		Wave(EnemyState s, float d) { waveState = s; duration = d; }
	};

	int currentWave = 0;
	float totalWaveTime = 0;
	Wave waves[8] = {Wave(EnemyState::Scatter, 7), Wave(EnemyState::Chase, 20)
					, Wave(EnemyState::Scatter, 7), Wave(EnemyState::Chase, 20)
					, Wave(EnemyState::Scatter, 5), Wave(EnemyState::Chase, 20)
					, Wave(EnemyState::Scatter, 5), Wave(EnemyState::Chase, -1)
	};

	std::vector<sf::Vector2i> currentPath;
	void UpdateEnemyTilePosition();
	sf::Vector2i GetOppositeDirectionNeighbour();
	void Move() override;

protected:
	virtual sf::Vector2i GetScatterTargetPosition();
	virtual sf::Vector2i GetChaseTargetPosition();

};
