#pragma once

#include "../GameManager.h"
#include "../Common.h"
#include "Node.h"

std::vector<sf::Vector2i> FindPath(sf::Vector2i startNode, sf::Vector2i endNode, Directions currentDir);