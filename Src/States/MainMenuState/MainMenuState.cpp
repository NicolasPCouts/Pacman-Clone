#include "MainMenuState.h"

#include "../GameState/GameState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, GameManager* gameManager)
	: State(window, states, gameManager) 
{
	//if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	//{
	//	throw("Could not load font");
	//}

	this->buttons["GAME_STATE"] = new Button(
		300.f, 480.f, 250.f, 50.f,
		/*&this->font,*/ "New Game", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::Update(const float& deltaTime)
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)));
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(window, states, gameManager));
	}

	Draw();
}

void MainMenuState::Draw()
{
	window->clear();
	for (auto& it : this->buttons)
	{
		it.second->render(window);
	}

	window->display();
}
