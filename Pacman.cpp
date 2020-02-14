#include "Pacman.h"
#include <iostream>


Pacman::Pacman(float x, float y)
{
	X = x;
	Y = y;

	if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 1, 13, 13)))
	{
		sprite.setTexture(texture);
		sprite.setScale(mapSprite.getScale().x, mapSprite.getScale().y);
		sprite.move(sf::Vector2f(25, 25));
	}
	else {
		std::cout << "texture not loaded correctly" << std::endl;
	}
}