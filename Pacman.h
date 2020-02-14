#pragma once
#include <SFML/Graphics.hpp>

class Pacman
{
public:
	float X, Y;
	Pacman(float x, float y);
	sf::Sprite sprite;
private:
	sf::Texture texture;
};

