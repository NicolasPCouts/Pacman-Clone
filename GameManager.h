#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

#include "Pacman.h"

class GameManager
{
public:
	sf::RenderWindow window;
	sf::Sprite mapSprite;
	Pacman pacman;
	GameManager();
	void Update();
};