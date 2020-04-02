#pragma once
#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;
extern sf::Sprite mapSprite;

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
	Pacman(float x, float y);
	void OnKeyPressed(sf::Event::KeyEvent key);
	void Update();
private:
	int speed;
	Directions currentDir = Right;
	sf::Texture texture;
	void Move(Directions dirToMove);
};

