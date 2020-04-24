#pragma once
#include "Common.h"

extern sf::RenderWindow window;
extern sf::Sprite mapSprite;
extern Tile tileArray[28][31];

enum Directions {
	Up,
	Down,
	Left,
	Right,
	None
};

class Pacman
{
public:
	sf::RectangleShape body;
	sf::Vector2f tilePos;
	Pacman(int x, int y);
	void OnKeyPressed(sf::Event::KeyEvent key);
	void Update();
private:
	float speed;
	Directions currentDir = None;
	sf::Texture texture;
	void Move();
};

