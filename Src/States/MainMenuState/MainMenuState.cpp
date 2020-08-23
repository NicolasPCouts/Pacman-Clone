#include "MainMenuState.h"

#include "../../GameManager.h"
#include "../GameState/GameState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, GameManager* gameManager)
	: State(window, states, gameManager) 
{
	//if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	//{
	//	throw("Could not load font");
	//}

	this->buttons["GAME_STATE"] = new Button(
		window->getView().getCenter().x - 50, 480.f,
		100.f, 30.f,
		"New Game", 20,
		sf::Color(105, 105, 105, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color::Black, sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	if (mapTexture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(0, 0, 226, 248)))
	{
		mapTexture.setSmooth(false);
		mapSprite.setTexture(mapTexture);
		mapSprite.setScale((window->getView().getSize().x) / (mapSprite.getLocalBounds().width * gameManager->aspectRatio), window->getView().getSize().y / mapSprite.getLocalBounds().height);
		mapSprite.move(0, 1);
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
