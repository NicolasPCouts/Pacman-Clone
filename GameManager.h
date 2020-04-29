#pragma once
#include "Common.h"

class GameManager
{
public:
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 800), "Pac-Man", sf::Style::Close);

	sf::Sprite mapSprite;
	sf::Texture mapTexture;

	Pacman pacman = Pacman(5, 1);

	Tile tileArray[28][31];
	std::vector<Snack*> snackList;

	bool showTiles = false;

	int numberOfTilesX = sizeof(tileArray) / sizeof(tileArray[0]);
	int numberOfTilesY = sizeof(tileArray[0]) / sizeof(tileArray[0][0]);
	float tileWidth = 800 / (float)numberOfTilesX;
	float tileHeight = 800 / (float)numberOfTilesY;

	GameManager();
	void Update();
private:
	void Draw();
	void LoadMap();
	void CreateMapColliders();
	void CreateSnacks();
};

