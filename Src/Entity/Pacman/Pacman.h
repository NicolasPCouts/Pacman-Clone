#pragma once
#include "../../Common.h"
#include "../../GameManager.h"
#include "../Entity.h"
#include "../../Animation/Animation.h"
#include "../../Animation/Animator.h"

class Pacman : Entity
{
public:
	Pacman(int x, int y);
	void OnKeyPressed(sf::Event::KeyEvent key);
	void Update();
	void Draw(sf::RenderWindow& rw) override;
private:
	Animator* animator;
	Animation* animations[5];
	Directions nextDir = None;
	float speed;
	bool hasCompletedMovement = false;
	void Move() override;
	void EatSnack(sf::Vector2i snackGridPosition);
	void UpdatePlayerTilePosition();
	void UpdateTileArray(sf::Vector2i newPos);
	bool IsNeighbourTileAvailable(Directions dir);
	sf::Vector2f GetFinalPosition();
	void SetupAnimations();
	void ChangeAnimation(Directions dir);
};

