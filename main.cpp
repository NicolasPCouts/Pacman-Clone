#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pacman.h"

struct ColliderObj
{
    sf::RectangleShape body;
    Collider coll;

    ColliderObj(sf::Vector2f rectangleSize, sf::Vector2f bodyPosition) : body(rectangleSize), coll(&body)
    {
        body.setPosition(bodyPosition);
    }
};

sf::RenderWindow window(sf::VideoMode(800, 800), "Pac-Man", sf::Style::Close);

sf::Sprite mapSprite;
sf::Texture mapTexture;

Pacman pacman = Pacman(40, 40);

std::vector<ColliderObj> mapColliders;

//test
sf::RectangleShape body = sf::RectangleShape(sf::Vector2f(100, 100));
Collider coll = Collider(&body);
sf::RectangleShape pixel = sf::RectangleShape(sf::Vector2f(5, 5));
//end test


void Draw();
void LoadMap();
void CreateMapColliders();

int main()
{
    //test
    body.move(sf::Vector2f(400, 400));
    body.setFillColor(sf::Color::White);
    pixel.setFillColor(sf::Color::Red);
    //end test

    LoadMap();
    CreateMapColliders();

    while (window.isOpen())
    {
        //get input
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) 
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    pacman.OnKeyPressed(event.key);
                    break;
            }
        }

        //Logic
        pacman.Update();
        std::cout << pacman.coll.CheckCollision(coll) << std::endl;
        //render
        Draw();
    }

    return 0;
}


void LoadMap()
{
    if (mapTexture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(0, 0, 226, 248)))
    {
        mapTexture.setSmooth(false);
        mapSprite.setTexture(mapTexture);
        mapSprite.setScale(window.getSize().x / mapSprite.getLocalBounds().width, window.getSize().y / mapSprite.getLocalBounds().height);
        mapSprite.move(0, 1);
    }
    else 
    {
        std::cout << "texture not loaded correctly" << std::endl;
    }
}

void Draw() 
{
    window.clear();
    window.draw(mapSprite);
    window.draw(pacman.body);

    //test
    pixel.setPosition(pacman.coll.GetPosition() + pacman.body.getSize());
    window.draw(pixel);
    pixel.setPosition(pacman.coll.GetPosition());
    window.draw(pixel);

    for (int i = 0; i < mapColliders.size(); i++)
    {
        pixel.setPosition(mapColliders[i].coll.GetPosition());
        window.draw(pixel);
        pixel.setPosition(mapColliders[i].coll.GetPosition() + mapColliders[i].body.getSize());
        window.draw(pixel);
    }

    window.draw(body);
    pixel.setPosition(coll.GetPosition());
    window.draw(pixel);
    pixel.setPosition(coll.GetPosition() + body.getSize());
    window.draw(pixel);
    //end test


    window.display();
}

void CreateMapColliders() 
{
    mapColliders.push_back(ColliderObj(sf::Vector2f(10, 80), sf::Vector2f(50, 50)));
}
