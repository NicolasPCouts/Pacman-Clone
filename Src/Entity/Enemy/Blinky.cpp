#include "Blinky.h"

Blinky::Blinky(sf::Vector2i gridPos) : Enemy(gridPos, sf::Vector2i(230, 65)){	}
Blinky::~Blinky() {	}

sf::Vector2i Blinky::GetScatterTargetPosition()
{
	return sf::Vector2i(26,1);
}
