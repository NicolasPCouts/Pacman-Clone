#include "Pacman.h"
#include <iostream>

Pacman::Pacman(float x, float y)
{
	X = x;
	Y = y;

	if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(0,0,226,248)))
	{
		//load pacman
	}
	else {
		std::cout << "texture not loaded correctly" << std::endl;
	}
}
