#pragma once

#include "../Common.h"
#include "../Entity/Entity.h"

class GameState;

std::vector<sf::Vector2i> FindPath(sf::Vector2i startNode, sf::Vector2i endNode, Directions currentDir, GameState* gameState);