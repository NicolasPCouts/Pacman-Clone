#pragma once
#include "Common.h"
#include "States/GameState/GameState.h"

class GameManager
{
public:
	sf::RenderWindow* window;
	std::stack<State*> states;
	float deltaTime = 0;
	float aspectRatio;


	void Update();
	void StartGameManager();
	~GameManager();
private:
	sf::Clock clock;
};