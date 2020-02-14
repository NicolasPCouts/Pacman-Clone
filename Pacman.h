#pragma once
#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;
extern sf::Sprite mapSprite;

class Pacman
{
public:
	float X, Y;
	Pacman(float x, float y);
	sf::Sprite sprite;
private:
	sf::Texture texture;
};

