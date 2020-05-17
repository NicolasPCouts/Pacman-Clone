#include "Enemy.h"
#include "../../GameManager.h"
#include  "../../Debugger/Debug.h"
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

void Enemy::Update()
{
	Move();
}

void Enemy::Move()
{
	float dt = speed * gameManager->deltaTime;
	switch (currentDir)
	{
	case None:
		UpdateEnemyTilePosition();
		return;
	case Up:
		if (GetFinalTilePosition().y <= body.getPosition().y)
			body.setPosition(body.getPosition().x, body.getPosition().y - dt);
		else
			UpdateEnemyTilePosition();
		break;
	case Down:
		if (GetFinalTilePosition().y >= body.getPosition().y)
			body.setPosition(body.getPosition().x, body.getPosition().y + dt);
		else
			UpdateEnemyTilePosition();
		break;
	case Left:
		if (GetFinalTilePosition().x <= body.getPosition().x)
			body.setPosition(body.getPosition().x - dt, body.getPosition().y);
		else
			UpdateEnemyTilePosition();
		break;
	case Right:
		if (GetFinalTilePosition().x >= body.getPosition().x)
			body.setPosition(body.getPosition().x + dt, body.getPosition().y);
		else
			UpdateEnemyTilePosition();
		break;
	}
}


void Enemy::Draw(sf::RenderWindow& rw)
{
	rw.draw(body);
	std::vector<sf::Vector2i> pos = FindPath(gridPos, gameManager->pacman->gridPos, currentDir);
	if(currentPath.size() > 0)
		DrawPathfinding(rw, currentPath, gridPos, gameManager->pacman->gridPos);
}

void Enemy::UpdateEnemyTilePosition()
{
	std::vector<sf::Vector2i> pos = FindPath(gridPos, gameManager->pacman->gridPos, currentDir);

	//in the case that no path is found, the enemy will set a neighbour tile as his path 
	if (pos.size() <= 0) {
		pos = FindPath(gridPos, GetOppositeDirectionNeighbour(), currentDir);
	}

	currentPath = pos;
	if (pos[0].x > gridPos.x)
		currentDir = Right;
	else if (pos[0].x < gridPos.x)
		currentDir = Left;
	else if (pos[0].y > gridPos.y)
		currentDir = Down;
	else if (pos[0].y < gridPos.y)
		currentDir = Up;

	UpdateTileArray(pos[0]);
}

sf::Vector2i Enemy::GetOppositeDirectionNeighbour()
{
	Directions dir = GetOppositeDirection(currentDir);

	sf::Vector2i tile = gridPos;

	switch (dir)
	{
	case Up:
		tile.y--;
		break;
	case Down:
		tile.y++;
		break;
	case Left:
		tile.x--;
		break;
	case Right:
		tile.x++;
		break;
	}

	return tile;
}

void Enemy::UpdateTileArray(sf::Vector2i newPos)
{
	//emptying current tile
	gameManager->tileArray[gridPos.x][gridPos.y].isEmpty = true;
	gameManager->tileArray[gridPos.x][gridPos.y].tileType = sTile::None;

	gridPos = newPos;

	//transfering enemy to next tile
	gameManager->tileArray[gridPos.x][gridPos.y].isEmpty = false;
	gameManager->tileArray[gridPos.x][gridPos.y].tileType = sTile::Enemy;
}
