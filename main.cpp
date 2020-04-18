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

//debug
bool drawTestCollider = false;
bool drawColliderBoxes = true;

ColliderObj testCollider(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
//end debug


void Draw();
void LoadMap();
void ChangeTestColliderValues(sf::Event::KeyEvent key);
void DrawColliderBoxes();

int main()
{
    LoadMap();

#pragma region Creating Map Colliders

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

    mapColliders.push_back(ColliderObj(sf::Vector2f(2, 631), sf::Vector2f(72, 30)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(726, 631), sf::Vector2f(72, 30)));

    //border colliders
    mapColliders.push_back(ColliderObj(sf::Vector2f(0, 0), sf::Vector2f(800, 15)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(0, 786), sf::Vector2f(800, 15)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(0, 490), sf::Vector2f(20, 310)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(780, 490), sf::Vector2f(20, 310)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(0, 0), sf::Vector2f(20, 260)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(780, 0), sf::Vector2f(20, 260)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(385, 0), sf::Vector2f(31, 115)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(641, 490), sf::Vector2f(156, 16)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(641, 400), sf::Vector2f(156, 16)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(641, 333), sf::Vector2f(156, 16)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(641, 244), sf::Vector2f(156, 16)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(3, 490), sf::Vector2f(156, 16)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(3, 400), sf::Vector2f(156, 16)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(3, 333), sf::Vector2f(156, 16)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(3, 244), sf::Vector2f(156, 16)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(142, 245), sf::Vector2f(18, 103)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(142, 400), sf::Vector2f(18, 103)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(641, 245), sf::Vector2f(18, 103)));
    mapColliders.push_back(ColliderObj(sf::Vector2f(641, 400), sf::Vector2f(18, 103)));

#pragma endregion

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
                    //ChangeTestColliderValues(event.key);
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

    //DrawColliderBoxes();
    sf::Vector2f vec(0, 0);

    int numberOfGridsX = 28;
    int numberOfGridsY = 31;
    float dividedNumberX = 800 / (float)numberOfGridsX;
    float dividedNumberY = 800 / (float)numberOfGridsY;

    for (int i = 0; i < numberOfGridsY; i++)
    {
        vec.x = 0;
        for (int j = 0; j < numberOfGridsX; j++)
        {
            sf::VertexArray quad(sf::LinesStrip, 5);

            quad[0].position = vec;

            sf::Vector2f v = vec;
            v.x += dividedNumberX;
            quad[1].position = v;

            quad[2].position = sf::Vector2f(vec.x + dividedNumberX, vec.y + dividedNumberY);

            sf::Vector2f v2 = vec;
            v2.y += dividedNumberY;
            quad[3].position = v2;

            quad[4].position = vec;

            window.draw(quad);
            vec.x += dividedNumberX;
        }
        vec.y += dividedNumberY;
    }


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

void DrawColliderBoxes() 
{
    if (drawTestCollider)
    {
        sf::VertexArray quad(sf::LinesStrip, 5);

        quad[0].position = testCollider.coll.GetPosition();

        sf::Vector2f v = testCollider.coll.GetPosition();
        v.x += testCollider.body.getSize().x;
        quad[1].position = v;

        quad[2].position = testCollider.coll.GetPosition() + testCollider.body.getSize();

        sf::Vector2f v2 = testCollider.coll.GetPosition();
        v2.y += testCollider.body.getSize().y;
        quad[3].position = v2;

        quad[4].position = testCollider.coll.GetPosition();

        window.draw(quad);
    }

    if (drawColliderBoxes)
    {
        for (int i = 0; i < mapColliders.size(); i++)
        {
            sf::VertexArray lines(sf::LinesStrip, 5);

            lines[0].position = mapColliders[i].coll.GetPosition();

            sf::Vector2f v = mapColliders[i].coll.GetPosition();
            v.x += mapColliders[i].body.getSize().x;
            lines[1].position = v;

            lines[2].position = mapColliders[i].coll.GetPosition() + mapColliders[i].body.getSize();

            sf::Vector2f v2 = mapColliders[i].coll.GetPosition();
            v2.y += mapColliders[i].body.getSize().y;
            lines[3].position = v2;

            lines[4].position = mapColliders[i].coll.GetPosition();

            window.draw(lines);
        }
    }
}