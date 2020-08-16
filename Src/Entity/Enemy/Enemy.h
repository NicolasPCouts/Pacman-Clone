#pragma once

#include "../Entity.h"
#include "../../Animation/Animator.h"
#include "../../Animation/Animation.h"

#include "../../Audio/AudioManager.h"

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
	void Scare();
	void UpdateTileArray(sf::Vector2i newPos) override;
	void Update() override;
	void Draw(sf::RenderWindow& rw) override;
	void Eaten();
private:
	int currentWave = 0;
	float totalWaveTime = 0;
	struct Wave {
		EnemyState waveState;
		float duration;
		Wave(EnemyState s, float d) { waveState = s; duration = d; }
	};
	Wave waves[8] = {Wave(EnemyState::Scatter, 7), Wave(EnemyState::Chase, 20)
					, Wave(EnemyState::Scatter, 7), Wave(EnemyState::Chase, 20)
					, Wave(EnemyState::Scatter, 5), Wave(EnemyState::Chase, 20)
					, Wave(EnemyState::Scatter, 5), Wave(EnemyState::Chase, -1)
	};

	float scaredTimer = 0;
	bool hasStartedflickeringAnim = false;
	AudioManager audio;
	std::vector<sf::Vector2i> currentPath;
	void UpdateEnemyTilePosition();
	void ChangeAnimation();
	sf::Vector2i GetOppositeDirectionNeighbour();
	void Move() override;
protected:
	Animator* animator;
	Animation* animations[6]; //left, right, up, down, frightened, flickeringFrightened
	virtual void SetupAnimations();
	virtual sf::Vector2i GetScatterTargetPosition();
	virtual sf::Vector2i GetChaseTargetPosition();
	virtual sf::Vector2i GetFrightenedTargetPosition();
};