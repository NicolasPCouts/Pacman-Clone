#pragma once

#include "SFML/Graphics.hpp"
#include "../Common.h"

class GameManager;

class State
{
protected:
	sf::RenderWindow* window;
	std::stack<State*>* states;
	bool quit;
	GameManager* gameManager;
public:
	State(sf::RenderWindow* window, std::stack<State*>* states, GameManager* gameManager);
	virtual void Update(const float& deltaTime) = 0;
	virtual void Draw() = 0;
	const bool& GetQuit() const;
	void EndState();
};