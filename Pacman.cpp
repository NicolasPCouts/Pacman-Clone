#include "Pacman.h"
#include <iostream>


Pacman::Pacman(float x, float y)
{
	speed = 25;
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
	{
		Move(Up);
	}
	else if (key.code == sf::Keyboard::Key::S)
	{
		Move(Down);
	}
	else if (key.code == sf::Keyboard::Key::A)
	{
		Move(Left);
	}
	else if (key.code == sf::Keyboard::Key::D)
	{
		Move(Right);
	}
}

void Pacman::Update()
{

}

void Pacman::Move(Directions dirToMove) 
{
	switch (dirToMove)
	{
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