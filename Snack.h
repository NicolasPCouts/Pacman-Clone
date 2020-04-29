#pragma once
#include "Common.h"

extern float tileWidth;
extern float tileHeight;

struct Snack {
    enum SnackType { SmallSnack, BigSnack };
    SnackType snackType;

    sf::RectangleShape rect;
    sf::Texture text;

    sf::Vector2i gridPos;

    Snack(SnackType type, sf::Vector2i gridPos)
    {
        if(type == SmallSnack)
        {
            rect = sf::RectangleShape(sf::Vector2f(tileWidth, tileHeight));
            text.loadFromFile("Resources/PacManSprites.png", sf::IntRect(226, 240, 6, 6));
            rect.setFillColor(sf::Color::White);
            rect.setTexture(&text);
            rect.move(sf::Vector2f(tileWidth * gridPos.x, tileHeight * gridPos.y));
        }
    }
};