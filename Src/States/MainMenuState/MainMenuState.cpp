#include "MainMenuState.h"

#include "../../GameManager.h"
#include "../GameState/GameState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, GameManager* gameManager)
	: State(window, states, gameManager) 
{
	this->buttons["GAME_STATE"] = new Button(
		window->getView().getCenter().x - 100, 480.f,
		200.f, 53.f,
		"New Game", 50,
		sf::Color(130, 130, 130, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50)
	);

	if (mapTexture.loadFromFile("Resources/pac-man-logo.png"))
	{
		mapTexture.setSmooth(false);
		mapSprite.setTexture(mapTexture);
		mapSprite.setScale(0.1f, 0.1f);
		mapSprite.setPosition(window->getView().getCenter().x - (mapSprite.getGlobalBounds().width / 2), 20);
	}
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
	window->draw(mapSprite);
	for (auto& it : this->buttons)
	{
		it.second->render(window);
	}

	window->display();
}
