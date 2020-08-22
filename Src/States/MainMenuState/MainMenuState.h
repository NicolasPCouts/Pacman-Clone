#pragma once

#include "../State.h"
#include "../../UI/Button.h"

class MainMenuState : public State
{
public:
	MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, GameManager* gameManager);
	~MainMenuState();
	void Update(const float& deltaTime);
	void Draw();
private:
	//sf::Font font;
	std::map<std::string, Button*> buttons;

	sf::Sprite mapSprite;
	sf::Texture mapTexture;
};

