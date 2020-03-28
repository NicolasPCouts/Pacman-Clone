#pragma once

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
	void OnKeyPressed(sf::Keyboard::Key key);
	void Update();
	sf::Texture texture;
private:
	Directions currentDir = Right;
};