#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states, GameManager* gameManager)
{
	this->window = window;
	this->states = states;
	this->gameManager = gameManager;
	this->quit = false;
}

const bool& State::GetQuit() const
{
	return this->quit;
}

void State::EndState()
{
	this->quit = true;
}