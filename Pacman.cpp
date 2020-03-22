#include "Pacman.h"
#include <iostream>

void Pacman::OnKeyPressed(sf::Keyboard::Key key)
{
	if (key == currentDir) {
		std::cout << "Current Direction" << std::endl;
		return;
	}
	std::cout << "Key Pressed" << std::endl;
}

Pacman::Pacman(float x, float y, GameManager* gameManager)
{
	X = x;
	Y = y;

	if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 1, 13, 13)))
	{
		sprite.setTexture(texture);
		sprite.setScale(gameManager->mapSprite.getScale().x, gameManager->mapSprite.getScale().y);
		sprite.move(sf::Vector2f(25, 25));
	}
	else 
	{
		std::cout << "texture not loaded correctly" << std::endl;
	}
}