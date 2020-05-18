#include "Enemy.h"

#include "../../GameManager.h"
#include  "../../Debugger/Debug.h"
#include "../../Pathfinding/Pathfinding.h"
#include "../Pacman/Pacman.h"

extern GameManager* gameManager;

Enemy::Enemy(sf::Vector2i gridPos, sf::Vector2i texturePos)
{
	body.setSize(sf::Vector2f(40, 40));
	this->gridPos = gridPos;
	gameManager->tileArray[gridPos.x][gridPos.y].isEmpty = false;
	gameManager->tileArray[gridPos.x][gridPos.y].tileType = sTile::Player;

	if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(texturePos.x, texturePos.y, 14, 14)))
		body.setTexture(&texture);
	else
		std::cout << "texture not loaded correctly" << std::endl;

	body.move(sf::Vector2f(30 * gridPos.x, 20 * gridPos.y));
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
	if (currentPath.size() > 0) {
		switch (state)
		{
		case EnemyState::Scatter:
			DrawPathfinding(rw, currentPath, gridPos, GetScatterTargetPosition());
			break;
		case EnemyState::Chase:
			DrawPathfinding(rw, currentPath, gridPos, GetChaseTargetPosition());
			break;
		}
	}
}

void Enemy::UpdateEnemyTilePosition()
{
	std::vector<sf::Vector2i> pos;
	switch (state)
	{
	case EnemyState::Scatter:
		pos = FindPath(gridPos, GetScatterTargetPosition(), currentDir);
		break;
	case EnemyState::Chase:
		pos = FindPath(gridPos, GetChaseTargetPosition(), currentDir);
		break;
	}

	//in the case that no path is found, the enemy will set a neighbour tile as his path 
	if (pos.size() <= 0) {
		pos = FindPath(gridPos, GetOppositeDirectionNeighbour(), currentDir);
	}

	if (pos[0].x > gridPos.x)
		currentDir = Right;
	else if (pos[0].x < gridPos.x)
		currentDir = Left;
	else if (pos[0].y > gridPos.y)
		currentDir = Down;
	else if (pos[0].y < gridPos.y)
		currentDir = Up;

	currentPath = pos;
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

sf::Vector2i Enemy::GetScatterTargetPosition()
{
	return sf::Vector2i(1, 1);
}

sf::Vector2i Enemy::GetChaseTargetPosition()
{
	return gameManager->pacman->gridPos;
}