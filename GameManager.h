#pragma once
#include "Common.h"

#include "Tile.h"
#include "Snack.h"

class Pacman;

class GameManager
{
public:
	sf::RenderWindow* window;

	sf::Sprite mapSprite;
	sf::Texture mapTexture;

	Pacman* pacman;

	Tile tileArray[28][31];
	std::vector<Snack*> SnackList;

	bool showTiles = false;

	int numberOfTilesX = sizeof(tileArray) / sizeof(tileArray[0]);
	int numberOfTilesY = sizeof(tileArray[0]) / sizeof(tileArray[0][0]);
	float tileWidth = 800 / (float)numberOfTilesX;
	float tileHeight = 800 / (float)numberOfTilesY;
	float deltaTime;

	void Update();
	void StartGameManager();
	~GameManager();
	void DeleteSnack(sf::Vector2i snackPos);
private:
	sf::Clock clock;
	float aspectRatio;
	void Draw();
	void LoadMap();
	void CreateMapColliders();
	void CreateSnacks();
	int FindSnackID(sf::Vector2i snackPos);
	void DeleteSnacks();
};