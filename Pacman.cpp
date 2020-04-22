#include "Pacman.h"
#include <iostream>


Pacman::Pacman(float x, float y) : body(sf::Vector2f(x,y))
{
	speed = 0.1f;

	if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 1, 13, 13)))
		body.setTexture(&texture);
	else
		std::cout << "texture not loaded correctly" << std::endl;

	body.move(sf::Vector2f(25, 25));
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
		body.setPosition(body.getPosition().x, body.getPosition().y - speed);
		break;
	case Down:
		body.setPosition(body.getPosition().x, body.getPosition().y + speed);
		break;
	case Left:
		body.setPosition(body.getPosition().x - speed, body.getPosition().y);
		break;
	case Right:
		body.setPosition(body.getPosition().x + speed, body.getPosition().y);
		break;
	}
}