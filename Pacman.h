#pragma once
#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;
extern sf::Sprite mapSprite;

class Pacman
{
public:
	float X, Y;
	sf::Sprite sprite;
	Pacman(float x, float y);
	void OnKeyPressed(sf::Keyboard::Key key);
	void Update();
private:
	sf::Texture texture;
};

