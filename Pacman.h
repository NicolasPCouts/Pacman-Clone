#pragma once
#include <SFML/Graphics.hpp>

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
	float X, Y;
	sf::Sprite sprite;
	Pacman(float x, float y);
	void OnKeyPressed(sf::Event::KeyEvent key);
	void Update();
private:
	float speed;
	Directions currentDir = None;
	sf::Texture texture;
	void Move();
};

