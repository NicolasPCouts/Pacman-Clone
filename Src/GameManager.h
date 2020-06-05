#pragma once
#include "Common.h"

#include "Tile.h"
#include "Entity/Snack/Snack.h"

class Enemy;
class Pacman;

#define NumberOfTilesX 28
#define NumberOfTilesY 31

class GameManager
{
public:
	sf::RenderWindow* window;

	sf::Sprite mapSprite;
	sf::Texture mapTexture;

	Pacman* pacman;
	Enemy* enemys[4];

	sTile tileArray[NumberOfTilesX][NumberOfTilesY];
	std::vector<Snack*> SnackList;

	float tileWidth = 800 / (float)NumberOfTilesX;
	float tileHeight = 800 / (float)NumberOfTilesY;
	float deltaTime = 0;


	void Update();
	void StartGameManager();
	~GameManager();
	int FindSnackID(sf::Vector2i snackPos);
	void DeleteSnack(sf::Vector2i snackPos);
	Enemy* FindEnemyByPosition(sf::Vector2i pos);
private:
	sf::Clock clock;
	float aspectRatio;
	void Draw();
	void LoadMap();
	void CreateMapColliders();
	void CreateSnacks();
	void DeleteSnacks();
};