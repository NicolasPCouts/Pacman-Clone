#pragma once
#include "Common.h"

#include "GameManager.h"

class Pacman
{
public:
	sf::RectangleShape body;
	sf::Vector2i tilePos;
	Pacman(int x, int y);
	void OnKeyPressed(sf::Event::KeyEvent key);
	void Update();
private:
	Directions currentDir = None;
	Directions nextDir = None;
	sf::Texture texture;
	float speed;
	bool hasCompletedMovement = false;
	void Move();
	void UpdatePlayerTilePosition();
	void UpdateTileArray(sf::Vector2i newPos);
	bool IsNeighbourTileAvailable(Directions dir);
	sf::Vector2f GetFinalPosition();
};

