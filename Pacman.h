#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

extern sf::RenderWindow window;
extern sf::Sprite mapSprite;

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
	Collider coll;
	Pacman(float x, float y);
	void OnKeyPressed(sf::Event::KeyEvent key);
	void Update();
private:
	float speed;
	Directions currentDir = None;
	sf::Texture texture;
	void Move();
};

