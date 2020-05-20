#pragma once
#include "Common.h"

#include "Tile.h"
#include "Entity/Snack/Snack.h"

class Enemy;
class Pacman;

class GameManager
{
public:
	sf::RenderWindow* window;

	sf::Sprite mapSprite;
	sf::Texture mapTexture;

	Pacman* pacman;
	Enemy* enemys[4];

	sTile tileArray[28][31];
	std::vector<Snack*> SnackList;

	int numberOfTilesX = sizeof(tileArray) / sizeof(tileArray[0]);
	int numberOfTilesY = sizeof(tileArray[0]) / sizeof(tileArray[0][0]);
	float tileWidth = 800 / (float)numberOfTilesX;
	float tileHeight = 800 / (float)numberOfTilesY;
	float deltaTime = 0;


	void Update();
	void StartGameManager();
	~GameManager();
	int FindSnackID(sf::Vector2i snackPos);
	void DeleteSnack(sf::Vector2i snackPos);
private:
	sf::Clock clock;
	float aspectRatio;
	void Draw();
	void LoadMap();
	void CreateMapColliders();
	void CreateSnacks();
	void DeleteSnacks();
};