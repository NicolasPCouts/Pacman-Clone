#include "Pacman.h"
#include <iostream>


Pacman::Pacman(float x, float y)
{
	X = x;
	Y = y;

	if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 1, 13, 13)))
	{
		sprite.setTexture(texture);
		sprite.setScale(mapSprite.getScale().x * 2, mapSprite.getScale().y * 2);
		sprite.move(sf::Vector2f(X, Y));
	}
	else {
		std::cout << "texture not loaded correctly" << std::endl;
	}
}

void Pacman::OnKeyPressed(sf::Keyboard::Key key)
{

}

void Pacman::Update()
{

}