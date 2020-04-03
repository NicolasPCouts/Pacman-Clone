#include "Pacman.h"
#include <iostream>


Pacman::Pacman(float x, float y)
{
	speed = 0.1f;
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

void Pacman::OnKeyPressed(sf::Event::KeyEvent key)
{
	if (key.code == sf::Keyboard::Key::W) 
		currentDir = Up;
	else if (key.code == sf::Keyboard::Key::S)
		currentDir = Down;
	else if (key.code == sf::Keyboard::Key::A)
		currentDir = Left;
	else if (key.code == sf::Keyboard::Key::D)
		currentDir = Right;
}

void Pacman::Update()
{
	Move();
}

void Pacman::Move() 
{
	switch (currentDir)
	{
	case None:
		return;
	case Up:
		sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - speed);
		break;
	case Down:
		sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + speed);
		break;
	case Left:
		sprite.setPosition(sprite.getPosition().x - speed, sprite.getPosition().y);
		break;
	case Right:
		sprite.setPosition(sprite.getPosition().x + speed, sprite.getPosition().y);
		break;
	}
}