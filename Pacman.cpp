#include <SFML/Graphics.hpp>
#include <iostream>

#include "Pacman.h"
#include "GameManager.h"

extern sf::RenderWindow window;
extern GameManager gameManager;

Pacman::Pacman(float x, float y)
{
	X = x;
	Y = y;

	if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 1, 13, 13)))
	{
		sprite.setTexture(texture);
		sprite.setScale(gameManager.mapSprite.getScale().x * 2, gameManager.mapSprite.getScale().y * 2);
		sprite.move(sf::Vector2f(X, Y));
	}
	else 
	{
		std::cout << "texture not loaded correctly" << std::endl;
	}
}

void Pacman::OnKeyPressed(sf::Keyboard::Key key)
{
	if (key == currentDir) {
		std::cout << "Current Direction" << std::endl;
		return;
	}
	std::cout << "Key Pressed" << std::endl;
}

void Pacman::Update()
{

}