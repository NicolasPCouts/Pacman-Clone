#include "Enemy.h"
#include "../../GameManager.h"
#include  "../../Debug.h"
#include "../../Pathfinding/Pathfinding.h"
#include "../Pacman/Pacman.h"

extern GameManager* gameManager;

Enemy::Enemy(int tileX, int tileY)
{
	body.setSize(sf::Vector2f(40, 40));
	gridPos = sf::Vector2i(tileX, tileY);
	gameManager->tileArray[tileX][tileY].isEmpty = false;
	gameManager->tileArray[tileX][tileY].tileType = sTile::Player;

	if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 65, 14, 14)))
		body.setTexture(&texture);
	else
		std::cout << "texture not loaded correctly" << std::endl;

	body.move(sf::Vector2f(30 * tileX, 20 * tileY));
}


Enemy::~Enemy()
{
}

void Enemy::Move()
{
	float dt = speed * gameManager->deltaTime;
	switch (currentDir)
	{
	case None:
		
		return;
	case Up:
		if (GetFinalTilePosition().y <= body.getPosition().y)
			body.setPosition(body.getPosition().x, body.getPosition().y - dt);
		else
			
		break;
	case Down:
		if (GetFinalTilePosition().y >= body.getPosition().y)
			body.setPosition(body.getPosition().x, body.getPosition().y + dt);
		else
			
		break;
	case Left:
		if (GetFinalTilePosition().x <= body.getPosition().x)
			body.setPosition(body.getPosition().x - dt, body.getPosition().y);
		else
			
		break;
	case Right:
		if (GetFinalTilePosition().x >= body.getPosition().x)
			body.setPosition(body.getPosition().x + dt, body.getPosition().y);
		else
			
		break;
	}
}

void Enemy::Update()
{

}

void Enemy::Draw(sf::RenderWindow& rw)
{
	rw.draw(body);
	std::vector<sf::Vector2i> pos = FindPath(gridPos, gameManager->pacman->gridPos, currentDir);
	DrawPathfinding(rw, pos, gridPos, gameManager->pacman->gridPos);
}