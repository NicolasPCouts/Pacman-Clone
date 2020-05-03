#include "Pacman.h"
#include "../../Tile.h"

extern GameManager* gameManager;

Pacman::Pacman(int tileX, int tileY)
{
	body.setSize(sf::Vector2f(40, 40));
	gridPos = sf::Vector2i(tileX, tileY);
	gameManager->tileArray[tileX][tileY].isEmpty = false;
	gameManager->tileArray[tileX][tileY].tileType = Tile::Player;

	speed = 0.1f;
	animator = new Animator(animations[0], &body);//REMINDER - DELETE ANIMATOR LATER

	if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 1, 13, 13)))
		body.setTexture(&texture);
	else
		std::cout << "texture not loaded correctly" << std::endl;

	body.move(sf::Vector2f(30 * tileX, 20 * tileY));
}

void Pacman::Draw(sf::RenderWindow& rw)
{
	rw.draw(body);
}

void Pacman::OnKeyPressed(sf::Event::KeyEvent key)
{
	if (key.code == sf::Keyboard::Key::W)
		nextDir = Up;
	else if (key.code == sf::Keyboard::Key::S)
		nextDir = Down;
	else if (key.code == sf::Keyboard::Key::A)
		nextDir = Left;
	else if (key.code == sf::Keyboard::Key::D)
		nextDir = Right;
}

void Pacman::Update()
{
	Move();
	animator->Update();
}

void Pacman::Move() 
{
	float dt = speed * gameManager->deltaTime;
	switch (currentDir)
	{
	case None:
		UpdatePlayerTilePosition();
		return;
	case Up:
		if (GetFinalPosition().y <= body.getPosition().y) 
			body.setPosition(body.getPosition().x, body.getPosition().y - dt);
		else
			UpdatePlayerTilePosition();
		break;
	case Down:
		if (GetFinalPosition().y >= body.getPosition().y)
			body.setPosition(body.getPosition().x, body.getPosition().y + dt);
		else
			UpdatePlayerTilePosition();
		break;
	case Left:
		if (GetFinalPosition().x <= body.getPosition().x)
			body.setPosition(body.getPosition().x - dt, body.getPosition().y);
		else
			UpdatePlayerTilePosition();
		break;
	case Right:
		if (GetFinalPosition().x >= body.getPosition().x)
			body.setPosition(body.getPosition().x + dt, body.getPosition().y);
		else
			UpdatePlayerTilePosition();
		break;
	}
}

void Pacman::EatSnack(sf::Vector2i snackGridPosition)
{
	gameManager->DeleteSnack(snackGridPosition);
}

sf::Vector2f Pacman::GetFinalPosition()
{
	return sf::Vector2f(gridPos.x * gameManager->tileWidth, gridPos.y * gameManager->tileHeight);
}

void Pacman::UpdatePlayerTilePosition()
{
	if (nextDir != None)
	{
		if(IsNeighbourTileAvailable(nextDir))
			currentDir = nextDir;

		nextDir = None;

		//change anim
	}

	if (IsNeighbourTileAvailable(currentDir))
	{
		switch (currentDir)
		{
		case Up:
			UpdateTileArray(sf::Vector2i(gridPos.x, gridPos.y - 1));
			break;
		case Down:
			UpdateTileArray(sf::Vector2i(gridPos.x, gridPos.y + 1));
			break;
		case Left:
			UpdateTileArray(sf::Vector2i(gridPos.x - 1, gridPos.y));
			break;
		case Right:
			UpdateTileArray(sf::Vector2i(gridPos.x + 1, gridPos.y));
			break;
		}
	}
}

void Pacman::UpdateTileArray(sf::Vector2i newPos) 
{
	//emptying current tile
	gameManager->tileArray[gridPos.x][gridPos.y].isEmpty = true;
	gameManager->tileArray[gridPos.x][gridPos.y].tileType = Tile::None;

	gridPos = newPos;

	if (gameManager->tileArray[gridPos.x][gridPos.y].tileType == Tile::Snack)
	{
		EatSnack(newPos);
	}

	//transfering player to next tile
	gameManager->tileArray[gridPos.x][gridPos.y].isEmpty = false;
	gameManager->tileArray[gridPos.x][gridPos.y].tileType = Tile::Player;
}

bool Pacman::IsNeighbourTileAvailable(Directions dir) 
{
	switch (dir)
	{
	case Up:
		if (gameManager->tileArray[gridPos.x][gridPos.y - 1].tileType != Tile::Wall)
			return true;
		break;
	case Down:
		if (gameManager->tileArray[gridPos.x][gridPos.y + 1].tileType != Tile::Wall)
			return true;
		break;
	case Left:
		if (gameManager->tileArray[gridPos.x - 1][gridPos.y].tileType != Tile::Wall)
			return true;
		break;
	case Right:
		if (gameManager->tileArray[gridPos.x + 1][gridPos.y].tileType != Tile::Wall)
			return true;
		break;
	}

	return false;
}

void Pacman::SetupAnimations() 
{
	//left animation
	sf::Texture l1, l2, l3;
	l1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 1, 13, 13));
	l2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(246, 1, 13, 13));
	l3.loadFromFile("Resources/PacManSprites.png", sf::IntRect(262, 1, 13, 13));
	std::vector<sf::Texture> leftAnimTextures{ l1,l2,l3 };

	animations[0] = new Animation(leftAnimTextures); //REMINDER - DELETE ANIMATIONS LATER
}