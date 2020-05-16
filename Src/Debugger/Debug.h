#pragma once
#include "../Common.h"

void DrawGrid(sf::RenderWindow& window);
void DrawPathfinding(sf::RenderWindow& window, std::vector<sf::Vector2i>& path, sf::Vector2i pathStart, sf::Vector2i pathTarget);