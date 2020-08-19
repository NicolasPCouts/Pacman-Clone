#include "GameManager.h"


void GameManager::StartGameManager()
{
    window = new sf::RenderWindow();
    window->create(sf::VideoMode(1200, 1200), "Pacman", sf::Style::Close);
    //window->create(sf::VideoMode::getFullscreenModes()[0], "Pacman", sf::Style::Resize);

    states.push(new GameState(window, &states, this));

    aspectRatio = float(window->getSize().x) / float(window->getSize().y);
    sf::View v(sf::Vector2f(400, 400), sf::Vector2f(800 * aspectRatio, 800));
    window->setView(v);
}

GameManager::~GameManager()
{

}

void GameManager::Update()
{
    while (window->isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        //get input
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::Resized:
                aspectRatio = float(window->getSize().x) / float(window->getSize().y);
                sf::View v(sf::Vector2f(400, 400), sf::Vector2f(800 * aspectRatio, 800));
                window->setView(v);
                break;
            }
        }

        //handle states
        if (!this->states.empty())
        {
            this->states.top()->Update(deltaTime);

            if (this->states.top()->GetQuit())
            {
                this->states.top()->EndState();
                delete this->states.top();
                this->states.pop();
            }
        }
        //Application end
        else
        {
            this->window->close();
        }

    }
}
