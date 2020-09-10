#pragma once

#include "../State.h"
#include "../../Tile.h"
#include "../../Entity/Snack/Snack.h"
#include "../../Audio/AudioManager.h"

class Enemy;
class Pacman;

#define NumberOfTilesX 28
#define NumberOfTilesY 31

class GameState : public State
{
public:
	Pacman* pacman;
	Enemy* enemys[4];
	sTile tileArray[NumberOfTilesX][NumberOfTilesY];
	std::vector<Snack*> SnackList;
	sf::Sprite mapSprite;
	sf::Texture mapTexture;
	AudioManager audioManager;

	float tileWidth = 800 / (float)NumberOfTilesX;
	float tileHeight = 800 / (float)NumberOfTilesY;
	int lives = 3;
	int score = 0;

	GameState(sf::RenderWindow* window, std::stack<State*>* states, GameManager* gameManager);
	~GameState();
	void Update(const float& deltaTime);
	void Draw();
	void OnPacmanDeath();
	int FindSnackID(sf::Vector2i snackPos);
	void DeleteSnack(sf::Vector2i snackPos);
	void ScareEnemys();
	void StopPowerSnackSound();
	Enemy* FindEnemyByPosition(sf::Vector2i pos);
private:
	sf::Font font;
	sf::Text text;

	void Restart();
	void LoadMap();
	void CreateMapColliders();
	void CreatePacmanAndEnemys();
	void CreateSnacks();
	void CreateUI();
	void DeleteSnacks();
};

