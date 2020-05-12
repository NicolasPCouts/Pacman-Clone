#pragma once
#include "Common.h"

#include "Tile.h"
#include "Entity/Snack/Snack.h"

class Pacman;

class GameManager
{
public:
	sf::RenderWindow* window;

	sf::Sprite mapSprite;
	sf::Texture mapTexture;

	Pacman* pacman;

	sTile tileArray[28][31];
	std::vector<Snack*> SnackList;

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


	//debugging
	int pathfindingTestX = 1;
	int pathfindingTestY = 1;
	int pathfindingTargetTestX = 5;
	int pathfindingTargetTestY = 1;
	void DrawDebug(bool drawTiles, bool drawPathfinding);
};