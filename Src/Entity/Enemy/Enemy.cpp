#include "Enemy.h"

#include <cstdlib>

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

	SetupAnimations();
	animator = new Animator(&body);

	if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(texturePos.x, texturePos.y, 14, 14)))
		body.setTexture(&texture);
	else
		std::cout << "texture not loaded correctly" << std::endl;

	body.move(sf::Vector2f(30 * gridPos.x, 20 * gridPos.y));
}


Enemy::~Enemy()
{
}

void Enemy::Scare()
{
	state = EnemyState::Frightened;
	animator->SetAnimationClip(animations[4]);
}

void Enemy::Update()
{
	//updating frightened timer
	if (state == EnemyState::Frightened) {
		scaredTimer += gameManager->deltaTime;

		if (scaredTimer >= 6 && !hasStartedflickeringAnim){
			animator->SetAnimationClip(animations[5]);
			scaredTimer = 0;
			hasStartedflickeringAnim = true;
		}

		if (scaredTimer >= 6 && hasStartedflickeringAnim) {
			scaredTimer = 0;
			state = waves[currentWave].waveState;
			hasStartedflickeringAnim = false;
		}
	}
	//updating wave system
	else {
		totalWaveTime += gameManager->deltaTime;

		if (totalWaveTime >= waves[currentWave].duration)
		{
			totalWaveTime -= waves[currentWave].duration;

			if(currentWave < (sizeof(waves) / sizeof(waves[0])) - 1)
				currentWave++;

			state = waves[currentWave].waveState;
		}
	}

	animator->Update(gameManager->deltaTime);
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

void Enemy::Eaten()
{
	state = EnemyState::Eaten;
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
	case EnemyState::Frightened:
		std::vector<sf::Vector2i> path{ GetFrightenedTargetPosition() };
		pos = path;
		break;
	}

	//in the case that no path is found, the enemy will set a neighbour tile as his path 
	if (pos.size() == 0) {
		pos = FindPath(gridPos, GetOppositeDirectionNeighbour(), currentDir);

		//in the case that no path is found, its because the enemy is about to be teleported to the other side of the screen
		if (pos.size() == 0) {
			sf::Vector2i p = gridPos;
			switch (currentDir)
			{
			case Left:
				p.x--;
				if (p.x < 0) {
					Teleport(Right);
					gridPos.x = 27;
					return;
				}
				else
					pos.push_back(p);
				break;
			case Right:
				p.x++;
				if (p.x > 27) {
					Teleport(Left);
					gridPos.x = 0;
					return;
				}
				else
					pos.push_back(p);
				break;
			}
		}
	}
	currentPath = pos;

	if (pos[0].x < gridPos.x) {
		if (currentDir != Left) {
			currentDir = Left;
			ChangeAnimation();
		}
	}
	else if (pos[0].x > gridPos.x) {
		if (currentDir != Right) {
			currentDir = Right;
			ChangeAnimation();
		}
	}
	else if (pos[0].y < gridPos.y) {
		if (currentDir != Up) {
			currentDir = Up;
			ChangeAnimation();
		}
	}
	else if (pos[0].y > gridPos.y) {
		if (currentDir != Down) {
			currentDir = Down;
			ChangeAnimation();
		}
	}
	
	UpdateTileArray(pos[0]);
}

void Enemy::ChangeAnimation()
{
	switch (currentDir)
	{
	case Left:
		if (state != EnemyState::Frightened) {
			if (state == EnemyState::Eaten) {
				if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(374, 81, 14, 14)))
					body.setTexture(&texture);
			}
			else
				animator->SetAnimationClip(animations[0]);
		}
		break;
	case Right:
		if (state != EnemyState::Frightened) {
			if (state == EnemyState::Eaten) {
				if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(358, 81, 14, 14)))
					body.setTexture(&texture);
			}
			else
				animator->SetAnimationClip(animations[1]);
		}
		break;
	case Up:
		if (state != EnemyState::Frightened) {
			if (state == EnemyState::Eaten) {
				if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(390, 81, 14, 14)))
					body.setTexture(&texture);
			}
			else
				animator->SetAnimationClip(animations[2]);
		}
		break;
	case Down:
		if (state != EnemyState::Frightened) {
			if (state == EnemyState::Eaten) {
				if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(406, 81, 14, 14)))
					body.setTexture(&texture);
			}
			else
				animator->SetAnimationClip(animations[3]);
		}
		break;
	}

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
	bool hasSnack = gameManager->FindSnackID(gridPos) == -1;
	gameManager->tileArray[gridPos.x][gridPos.y].isEmpty = hasSnack? true : false;
	gameManager->tileArray[gridPos.x][gridPos.y].tileType = hasSnack? sTile::None : sTile::Snack;

	gridPos = newPos;

	//transfering enemy to next tile
	gameManager->tileArray[gridPos.x][gridPos.y].isEmpty = false;
	gameManager->tileArray[gridPos.x][gridPos.y].tileType = sTile::Ghost;
}

sf::Vector2i Enemy::GetScatterTargetPosition()
{
	return sf::Vector2i(1, 1);
}

sf::Vector2i Enemy::GetChaseTargetPosition()
{
	return gameManager->pacman->gridPos;
}

sf::Vector2i Enemy::GetFrightenedTargetPosition()
{
	std::vector<Directions> possibleDirections;

	if (GetOppositeDirection(currentDir) != Left && IsNeighbourTileAvailable(Left))
		possibleDirections.push_back(Left);
	if (GetOppositeDirection(currentDir) != Right && IsNeighbourTileAvailable(Right))
		possibleDirections.push_back(Right);
	if (GetOppositeDirection(currentDir) != Up && IsNeighbourTileAvailable(Up))
		possibleDirections.push_back(Up);
	if (GetOppositeDirection(currentDir) != Down && IsNeighbourTileAvailable(Down))
		possibleDirections.push_back(Down);

	if (possibleDirections.size() != 0) {
		int randomDir = std::rand() % possibleDirections.size();

		sf::Vector2i pos = gridPos;
		switch (possibleDirections[randomDir])
		{
		case Up:
			pos.y--;
			break;
		case Down:
			pos.y++;
			break;
		case Left:
			pos.x--;
			break;
		case Right:
			pos.x++;
			break;
		}

		return pos;
	}

	return gridPos;
}

void Enemy::SetupAnimations()
{
	sf::Texture f1, f2, ff1, ff2;
	f1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(358, 65, 14, 14));
	f2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(374, 65, 14, 14));
	ff1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(390, 65, 14, 14));
	ff2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(406, 65, 14, 14));
	std::vector<sf::Texture> frightenedAnimTextures{ f1, f2 };
	std::vector<sf::Texture> flickeringFrightenedAnimTextures{ f1, f2, ff1, ff2 };


	animations[4] = new Animation(frightenedAnimTextures);
	animations[5] = new Animation(flickeringFrightenedAnimTextures);
}