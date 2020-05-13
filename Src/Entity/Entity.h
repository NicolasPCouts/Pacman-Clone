#pragma once
#include "../Common.h"

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
	float speed = 0.05f;
	sf::Vector2i gridPos;
	Directions currentDir = None;
	sf::RectangleShape body;
	sf::Texture texture;
	sf::Vector2f GetFinalTilePosition();
	virtual void Draw(sf::RenderWindow& rw) = 0;
	virtual void Move() = 0;
};

Directions GetOppositeDirection(Directions dir);