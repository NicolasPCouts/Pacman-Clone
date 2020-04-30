#pragma once
#include "Common.h"


enum Directions {
	Up,
	Down,
	Left,
	Right,
	None
};


class Entity
{
public:
	sf::Vector2i gridPos;
	Directions currentDir = None;
	sf::RectangleShape body;
	sf::Texture texture;
	virtual void Draw(sf::RenderWindow& rw);
	virtual void Move() = 0;
private:
};

