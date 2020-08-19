#pragma once
#include "../Common.h"
#include "../States/GameState/GameState.h"

void DrawGrid(sf::RenderWindow& window, GameState* gameState);
void DrawCube(sf::RenderWindow& window, sf::Vector2i pos, GameState* gameState);
void DrawPathfinding(sf::RenderWindow& window, std::vector<sf::Vector2i>& path, sf::Vector2i pathStart, sf::Vector2i pathTarget, GameState* gameState);