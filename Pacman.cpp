#include "Pacman.h"
#include <iostream>


Pacman::Pacman(int tileX, int tileY) : body(sf::Vector2f(40, 40))
{
	tilePos = sf::Vector2i(tileX, tileY);
	tileArray[tileX][tileY].isEmpty = false;
	tileArray[tileX][tileY].tileType = Tile::Player;

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
		if (GetFinalPosition().y < body.getPosition().y) 
			body.setPosition(body.getPosition().x, body.getPosition().y - speed);
		else if(tileArray[tilePos.x][tilePos.y - 1].isEmpty)
		{
			UpdatePlayerTilePosition(sf::Vector2i(tilePos.x, tilePos.y - 1));
		}
		break;
	case Down:
		if (GetFinalPosition().y > body.getPosition().y)
			body.setPosition(body.getPosition().x, body.getPosition().y + speed);
		else if (tileArray[tilePos.x][tilePos.y + 1].isEmpty)
		{
			UpdatePlayerTilePosition(sf::Vector2i(tilePos.x, tilePos.y + 1));
		}
		break;
	case Left:
		if (GetFinalPosition().x < body.getPosition().x)
			body.setPosition(body.getPosition().x - speed, body.getPosition().y);
		else if (tileArray[tilePos.x - 1][tilePos.y].isEmpty)
		{
			UpdatePlayerTilePosition(sf::Vector2i(tilePos.x - 1, tilePos.y));
		}
		break;
	case Right:
		if (GetFinalPosition().x > body.getPosition().x)
			body.setPosition(body.getPosition().x + speed, body.getPosition().y);
		else if (tileArray[tilePos.x + 1][tilePos.y].isEmpty)
		{
			UpdatePlayerTilePosition(sf::Vector2i(tilePos.x + 1, tilePos.y));
		}
		break;
	}
}

sf::Vector2f Pacman::GetFinalPosition()
{
	return sf::Vector2f(tilePos.x * tileWidth, tilePos.y * tileHeight);
}

void Pacman::UpdatePlayerTilePosition(sf::Vector2i newPos) 
{
	tileArray[tilePos.x][tilePos.y].isEmpty = true;
	tileArray[tilePos.x][tilePos.y].tileType = Tile::None;
	tilePos = newPos;
	tileArray[tilePos.x][tilePos.y].isEmpty = false;
	tileArray[tilePos.x][tilePos.y].tileType = Tile::Player;
}