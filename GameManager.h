#pragma once
#include "Common.h"
class Pacman;

class GameManager
{
public:
	sf::Sprite mapSprite;
	Pacman* pacman;
	GameManager();
	void Update();
};