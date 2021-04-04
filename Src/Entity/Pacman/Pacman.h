#pragma once
#include "../../Common.h"
#include "../../GameManager.h"
#include "../Entity.h"
#include "../../Animation/Animation.h"
#include "../../Animation/Animator.h"
#include "../../Audio/AudioManager.h"

class Pacman : public Entity
{
public:
	Pacman(int x, int y, GameState* gameState);
	~Pacman();
	void Update(const float& deltaTime) override;
	void Draw(sf::RenderWindow& rw) override;
	void Die();
private:
	Animator* animator;
	AudioManager audio;
	Animation* animations[5];//left, right, up, down, death
	Directions nextDir = None;
	bool hasCompletedMovement = false;
	bool isEatingSnacks = false;

	void Move(const float& deltaTime) override;
	void EatSnack(sf::Vector2i snackGridPosition);
	void UpdatePlayerTilePosition();
	void UpdateTileArray(sf::Vector2i newPos);
	void SetupAnimations();
	void ChangeAnimation(Directions dir);
};

