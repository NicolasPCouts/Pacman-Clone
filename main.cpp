#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pacman.h"

sf::RenderWindow window(sf::VideoMode(800, 800), "Pac-Man", sf::Style::Close);
sf::Sprite mapSprite;
int main()
{
    
    //loading map
    sf::Texture texture;
    if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(0, 0, 226, 248)))
    {
        texture.setSmooth(false);
        mapSprite.setTexture(texture);
        mapSprite.setScale(window.getSize().x / mapSprite.getLocalBounds().width, window.getSize().y / mapSprite.getLocalBounds().height);
        mapSprite.move(0, 1);
    }
    else {
        std::cout << "texture not loaded correctly" << std::endl;
    }

    Pacman pacman = Pacman(50,50);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) 
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    break;
            }
        }

        window.clear();
        window.draw(mapSprite);
        window.draw(pacman.sprite);
        window.display();
    }

    return 0;
}