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

	sf::Sprite readyTextSprite;
	sf::Texture readyTextTexture;

	sf::Sprite gameOverTextSprite;
	sf::Texture gameOverTextTexture;

	AudioManager audioManager;

	int score = 0;

	float tileWidth = 800 / (float)NumberOfTilesX;
	float tileHeight = 800 / (float)NumberOfTilesY;

	bool isPacmanDead = false;
	bool powerSnackActive = false;

	GameState(sf::RenderWindow* window, std::stack<State*>* states, GameManager* gameManager);
	~GameState();
	void Update(const float& deltaTime);
	void Draw();
	void OnPacmanDeath();
	int FindSnackID(sf::Vector2i snackPos);
	void DeleteSnack(sf::Vector2i snackPos);
	void ScareEnemys();
	void FreezeGame(Entities entityThatWontFreeze);
	void UnfreezeGame();
	void StopPowerSnackSound();
	Enemy* FindEnemyByPosition(sf::Vector2i pos);
private:
	int lifes = 3;

	bool isFreezed = false;
	bool gameHasStarted = false;
	Entities entityThatWontFreeze = Entities::NotDefined;

	sf::Font font;
	sf::Text scoreText;
	sf::Text lifesText;

	void Restart();
	void LoadTextures();
	void CreateMapCollidersAndSnacks();
	void EmptyTileArray();
	void CreatePacmanAndEnemys();
	void CreateUI();
	void UpdateUI();
	void DeleteSnacks();
};

