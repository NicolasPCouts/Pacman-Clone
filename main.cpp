#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pacman.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pac-Man", sf::Style::Close);
    
    //loading map
    sf::Texture texture;
    sf::Sprite mapSprite;
    if (texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(0, 0, 226, 248)))
    {
        texture.setSmooth(false);
        mapSprite.setTexture(texture);
        mapSprite.setScale(2, 2);
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
        //window.draw(pacman.sprite);
        window.display();
    }

    return 0;
}