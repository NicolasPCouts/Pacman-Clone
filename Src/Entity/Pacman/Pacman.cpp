#include "Pacman.h"
#include "../../Tile.h"
#include "../Enemy/Enemy.h"
#include "../../Debugger/Debug.h"
#include "../../States/GameState/GameState.h"
#include "../../Audio/AudioAssets.h"

Pacman::Pacman(int tileX, int tileY, GameState* gameState)
	: Entity(gameState, Entities::Pacman)
{
	body.setSize(sf::Vector2f(40, 40));
	gridPos = sf::Vector2i(tileX, tileY);
	gameState->tileArray[tileX][tileY].isEmpty = false;
	gameState->tileArray[tileX][tileY].tileTypes.push_back(sTile::Player);

	SetupAnimations();
	animator = new Animator(&body);

	if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 1, 13, 13)))
		body.setTexture(&texture);
	else
		std::cout << "texture not loaded correctly" << std::endl;

	body.move(sf::Vector2f(30 * tileX, 25.5f * tileY));
}

Pacman::~Pacman()
{
	delete animator;
	for (auto const& x : animations)
		delete x;
}

void Pacman::Draw(sf::RenderWindow& rw)
{
	rw.draw(body);
	DrawCube(rw, gridPos, gameState);
}

void Pacman::Update(const float& deltaTime)
{
	if (!gameState->isPacmanDead)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			nextDir = Up;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			nextDir = Down;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			nextDir = Left;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			nextDir = Right;

		//handle eating snack sound effect
		if (isEatingSnacks && !audio.IsPlayingAudio(Sounds::Munch))
			audio.PlaySound(Sounds::Munch, true, VOLUME);
		else if (!isEatingSnacks && audio.IsPlayingAudio(Sounds::Munch))
			audio.StopSound(Sounds::Munch);

		Move(deltaTime);
	}
	animator->Update(deltaTime);
}

void Pacman::Die() 
{
	animator->SetAnimationClip(animations[4]);
	audio.StopSound();
	gameState->OnPacmanDeath();
}

void Pacman::Move(const float& deltaTime)
{
	float dt = speed * deltaTime;
	switch (currentDir)
	{
	case None:
		UpdatePlayerTilePosition();
		return;
	case Up:
		if (GetFinalTilePosition().y <= body.getPosition().y) 
			body.setPosition(body.getPosition().x, body.getPosition().y - dt);
		else
			UpdatePlayerTilePosition();
		break;
	case Down:
		if (GetFinalTilePosition().y >= body.getPosition().y)
			body.setPosition(body.getPosition().x, body.getPosition().y + dt);
		else
			UpdatePlayerTilePosition();
		break;
	case Left:
		if (GetFinalTilePosition().x <= body.getPosition().x)
			body.setPosition(body.getPosition().x - dt, body.getPosition().y);
		else
			UpdatePlayerTilePosition();
		break;
	case Right:
		if (GetFinalTilePosition().x >= body.getPosition().x)
			body.setPosition(body.getPosition().x + dt, body.getPosition().y);
		else
			UpdatePlayerTilePosition();
		break;
	}
}

void Pacman::EatSnack(sf::Vector2i snackGridPosition)
{
	if (gameState->SnackList[gameState->FindSnackID(snackGridPosition)]->snackType == Snack::BigSnack) {
		gameState->ScareEnemys();
	}

	isEatingSnacks = true;
	gameState->score += 10;

	gameState->DeleteSnack(snackGridPosition);
}

void Pacman::UpdatePlayerTilePosition()
{
	if (nextDir != None)
	{
		if (IsNeighbourTileAvailable(nextDir)) {
			currentDir = nextDir;
			ChangeAnimation(currentDir);
		}

		//nextDir = None;
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
	else {
		switch (currentDir)
		{
		case Left:
			if (IsTeleportTile(sf::Vector2i(gridPos.x - 1, gridPos.y))) {
				Teleport(Right);
				UpdateTileArray(sf::Vector2i(27, gridPos.y));
				break;
			}
		case Right:
			if (IsTeleportTile(sf::Vector2i(gridPos.x + 1, gridPos.y))) {
				Teleport(Left);
				UpdateTileArray(sf::Vector2i(0, gridPos.y));
				break;
			}
		}
		//if the player is stuck on a corner, and its not a teleport tile, munching sound should stop playing
		if (isEatingSnacks) isEatingSnacks = false;
	}
}

void Pacman::UpdateTileArray(sf::Vector2i newPos) 
{
	//emptying current tile
	gameState->tileArray[gridPos.x][gridPos.y].isEmpty = true;
	gameState->tileArray[gridPos.x][gridPos.y].EraseTileType(sTile::Player);

	gridPos = newPos;

	if (gameState->tileArray[gridPos.x][gridPos.y].DoesTileHaveType(sTile::Snack)) {
		gameState->tileArray[gridPos.x][gridPos.y].EraseTileType(sTile::Snack);
		EatSnack(newPos);
	}
	else isEatingSnacks = false;

	Enemy* e = gameState->FindEnemyByPosition(gridPos);
	if (e != NULL) 
	{
		if (e->state == EnemyState::Frightened)
		{
			e->Eaten();
			gameState->score += 100;
		}
		else if (e->state != EnemyState::Eaten)
			Die();
	}

	//transfering player to next tile
	gameState->tileArray[gridPos.x][gridPos.y].isEmpty = false;
	gameState->tileArray[gridPos.x][gridPos.y].tileTypes.push_back(sTile::Player);
}

void Pacman::SetupAnimations() 
{
	//right animation
	sf::Texture r1, r2, r3;
	r1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 1, 13, 13));
	r2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(246, 1, 13, 13));
	r3.loadFromFile("Resources/PacManSprites.png", sf::IntRect(262, 1, 13, 13));
	std::vector<sf::Texture> rightAnimTextures{ r1,r2,r3 };

	//left animation
	sf::Texture l1, l2, l3;
	l1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 17, 13, 13));
	l2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(246, 17, 13, 13));
	l3.loadFromFile("Resources/PacManSprites.png", sf::IntRect(262, 17, 13, 13));
	std::vector<sf::Texture> leftAnimTextures{ l1,l2,l3 };

	//up animation
	sf::Texture u1, u2, u3;
	u1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 33, 13, 13));
	u2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(246, 33, 13, 13));
	u3.loadFromFile("Resources/PacManSprites.png", sf::IntRect(262, 33, 13, 13));
	std::vector<sf::Texture> upAnimTextures{ u1,u2,u3 };

	//down animation
	sf::Texture d1, d2, d3;
	d1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 49, 13, 13));
	d2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(246, 49, 13, 13));
	d3.loadFromFile("Resources/PacManSprites.png", sf::IntRect(262, 49, 13, 13));
	std::vector<sf::Texture> downAnimTextures{ d1, d2, d3 };

	//death animation
	sf::Texture de1, de2, de3, de4, de5, de6, de7, de8, de9, de10, de11, de12;
	de1.loadFromFile("Resources/PacManSprites.png", sf::IntRect(278, 1, 13, 13));
	de2.loadFromFile("Resources/PacManSprites.png", sf::IntRect(294, 1, 13, 13));
	de3.loadFromFile("Resources/PacManSprites.png", sf::IntRect(310, 1, 13, 13));
	de4.loadFromFile("Resources/PacManSprites.png", sf::IntRect(326, 1, 13, 13));
	de5.loadFromFile("Resources/PacManSprites.png", sf::IntRect(342, 1, 13, 13));
	de6.loadFromFile("Resources/PacManSprites.png", sf::IntRect(358, 1, 13, 13));
	de7.loadFromFile("Resources/PacManSprites.png", sf::IntRect(374, 1, 13, 13));
	de8.loadFromFile("Resources/PacManSprites.png", sf::IntRect(390, 1, 13, 13));
	de9.loadFromFile("Resources/PacManSprites.png", sf::IntRect(406, 1, 13, 13));
	de10.loadFromFile("Resources/PacManSprites.png", sf::IntRect(422, 1, 13, 13));
	de11.loadFromFile("Resources/PacManSprites.png", sf::IntRect(438, 1, 13, 13));
	de12.loadFromFile("Resources/PacManSprites.png", sf::IntRect(438, 17, 13, 13));
	std::vector<sf::Texture> deathAnimTextures{ de1, de2, de3, de4, de5, de6, de7, de8, de9, de10, de11, de12 };

	animations[0] = new Animation(leftAnimTextures);
	animations[1] = new Animation(rightAnimTextures);
	animations[2] = new Animation(upAnimTextures);
	animations[3] = new Animation(downAnimTextures);
	animations[4] = new Animation(deathAnimTextures, false, 0.20f);
}

void Pacman::ChangeAnimation(Directions dir)
{
	switch (dir)
	{
	case Up:
		animator->SetAnimationClip(animations[2]);
		break;
	case Down:
		animator->SetAnimationClip(animations[3]);
		break;
	case Left:
		animator->SetAnimationClip(animations[0]);
		break;
	case Right:
		animator->SetAnimationClip(animations[1]);
		break;
	}
}
