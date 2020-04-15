#include <iostream>
#include <SFML/Graphics.hpp>

#include "Pacman.h"

struct ColliderObj
{
    sf::RectangleShape body;
    Collider coll;

    ColliderObj(sf::Vector2f bodyPosition, sf::Vector2f rectangleSize) : body(rectangleSize), coll(&body)
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
ColliderObj testCollider(sf::Vector2f(80, 60), sf::Vector2f(70, 60));

sf::RectangleShape pixel = sf::RectangleShape(sf::Vector2f(5, 5));
//end test


void Draw();
void LoadMap();
void ChangeTestColliderValues(sf::Event::KeyEvent key);

int main()
{
    //test
    pixel.setFillColor(sf::Color::Red);
    //end test

    LoadMap();

    //Create Map Colliders
    mapColliders.push_back(ColliderObj(sf::Vector2f(74, 64), sf::Vector2f(81, 49)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(217, 64), sf::Vector2f(108, 49)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(471, 64), sf::Vector2f(108, 49)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(641, 64), sf::Vector2f(81, 49)));

    mapColliders.push_back(ColliderObj(sf::Vector2f(73, 165), sf::Vector2f(85, 28)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(300, 165), sf::Vector2f(197, 28)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(640, 165), sf::Vector2f(85, 28)));

    mapColliders.push_back(ColliderObj(sf::Vector2f(214, 166), sf::Vector2f(28, 182)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(214, 237), sf::Vector2f(113, 34)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(378, 168), sf::Vector2f(35, 102)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(471, 244), sf::Vector2f(109, 33)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(555, 166), sf::Vector2f(27, 181)));

    mapColliders.push_back(ColliderObj(sf::Vector2f(216, 399), sf::Vector2f(25, 103)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(301, 476), sf::Vector2f(197, 28)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(383, 479), sf::Vector2f(29, 101)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(556, 399), sf::Vector2f(25, 103)));

    mapColliders.push_back(ColliderObj(sf::Vector2f(73, 554), sf::Vector2f(83, 33)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(125, 554), sf::Vector2f(31, 100)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(215, 554), sf::Vector2f(112, 26)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(470, 554), sf::Vector2f(112, 26)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(638, 554), sf::Vector2f(31, 100)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(638, 554), sf::Vector2f(85, 28)));

    mapColliders.push_back(ColliderObj(sf::Vector2f(74, 709), sf::Vector2f(252, 25)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(215, 631), sf::Vector2f(29, 100)));

    mapColliders.push_back(ColliderObj(sf::Vector2f(301, 631), sf::Vector2f(195, 25)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(381, 632), sf::Vector2f(29, 100)));

    mapColliders.push_back(ColliderObj(sf::Vector2f(471, 709), sf::Vector2f(252, 25)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(555, 631), sf::Vector2f(29, 100)));

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
                    //pacman.OnKeyPressed(event.key);
                    ChangeTestColliderValues(event.key);
                    break;
            }
        }

        //Logic
        pacman.Update();

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
    pixel.setPosition(testCollider.coll.GetPosition());
    window.draw(pixel);
    pixel.setPosition(testCollider.coll.GetPosition() + testCollider.body.getSize());
    window.draw(pixel);

    for (int i = 0; i < mapColliders.size(); i++)
    {
        pixel.setPosition(mapColliders[i].coll.GetPosition());
        window.draw(pixel);
        pixel.setPosition(mapColliders[i].coll.GetPosition() + mapColliders[i].body.getSize());
        window.draw(pixel);
    }
    //end test


    window.display();
}

//tests
void ChangeTestColliderValues(sf::Event::KeyEvent key)
{
    if (key.code == sf::Keyboard::Key::W)
        testCollider.body.move(sf::Vector2f(0, -1));
    else if (key.code == sf::Keyboard::Key::S)
        testCollider.body.move(sf::Vector2f(0, 1));
    else if (key.code == sf::Keyboard::Key::A)
        testCollider.body.move(sf::Vector2f(-1, 0));
    else if (key.code == sf::Keyboard::Key::D)
        testCollider.body.move(sf::Vector2f(1, 0));

    else if (key.code == sf::Keyboard::Key::Up)
        testCollider.body.setSize(sf::Vector2f(testCollider.body.getSize().x, testCollider.body.getSize().y - 1));
    else if (key.code == sf::Keyboard::Key::Down)
        testCollider.body.setSize(sf::Vector2f(testCollider.body.getSize().x, testCollider.body.getSize().y + 1));
    else if (key.code == sf::Keyboard::Key::Left)
        testCollider.body.setSize(sf::Vector2f(testCollider.body.getSize().x - 1, testCollider.body.getSize().y));
    else if (key.code == sf::Keyboard::Key::Right)
        testCollider.body.setSize(sf::Vector2f(testCollider.body.getSize().x + 1, testCollider.body.getSize().y));

    std::cout << "Pos X : " << testCollider.body.getPosition().x << " - Pos Y : " << testCollider.body.getPosition().y 
        << " - Size X : " << testCollider.body.getSize().x << " - Size Y : " << testCollider.body.getSize().y << std::endl;
}