#pragma once

#include "../Entity.h"
#include "../../Animation/Animator.h"
#include "../../Animation/Animation.h"

#include "../../Audio/AudioManager.h"

enum class EnemyState {
	Scatter,
	Chase,
	Frightened,
	Eaten_FreezedGame,
	Eaten_Retreating
};

class Enemy : public Entity
{
public:
	EnemyState state = EnemyState::Scatter;
	Enemy(sf::Vector2i gridPos, sf::Vector2i texturePos, GameState* gameState, Entities entityType);
	~Enemy();
	void Scare();
	void UpdateTileArray(sf::Vector2i newPos) override;
	void Update(const float& deltaTime) override;
	void Draw(sf::RenderWindow& rw) override;
	void Eaten();
private:
	int currentWave = 0;
	float totalWaveTime = 0;
	float scaredTimer = 0;
	bool hasStartedflickeringAnim = false;
	AudioManager audio;
	std::vector<sf::Vector2i> currentPath;

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

	void UpdateEnemyTilePosition();
	void ChangeAnimation();
	sf::Vector2i GetOppositeDirectionNeighbour();
	void Move(const float& deltaTime) override;
protected:
	Animator* animator;
	Animation* animations[6]; //left, right, up, down, frightened, flickeringFrightened
	virtual void SetupAnimations();
	virtual sf::Vector2i GetScatterTargetPosition();
	virtual sf::Vector2i GetChaseTargetPosition();
	virtual sf::Vector2i GetFrightenedTargetPosition();
};