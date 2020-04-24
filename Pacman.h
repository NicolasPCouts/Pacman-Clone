#pragma once
#include "Common.h"

extern sf::RenderWindow window;
extern sf::Sprite mapSprite;
extern Tile tileArray[28][31];
extern float tileWidth;
extern float tileHeight;

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
	sf::Vector2i tilePos;
	Pacman(int x, int y);
	void OnKeyPressed(sf::Event::KeyEvent key);
	void Update();
private:
	Directions currentDir = None;
	sf::Texture texture;
	float speed;
	void Move();
	sf::Vector2f GetFinalPosition();
	void UpdatePlayerTilePosition(sf::Vector2i newPos);
};

