#pragma once
#include "Common.h"

#include "Tile.h"
#include "Snack.h"

class Pacman;

class GameManager
{
public:
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 800), "Pac-Man", sf::Style::Close);

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

	void Update();
	void StartGameManager();
	~GameManager();
	void DeleteSnack(sf::Vector2i snackPos);
private:
	void Draw();
	void LoadMap();
	void CreateMapColliders();
	void CreateSnacks();
	int FindSnackID(sf::Vector2i snackPos);
	void DeleteSnacks();
};