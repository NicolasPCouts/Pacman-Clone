#pragma once
#include "GameManager.h"

enum Directions {
	Up = 22,
	Down = 18,
	Left = 0,
	Right = 3
};

class Pacman
{
public:
	float X, Y;
	sf::Sprite sprite;
	Pacman(float x, float y, GameManager* gameManager);
	void OnKeyPressed(sf::Keyboard::Key key);
private:
	sf::Texture texture;
	Directions currentDir = Right;
};