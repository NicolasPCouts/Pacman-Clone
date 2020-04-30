#pragma once
#include "Common.h"


class Snack {
public:
    enum SnackType { SmallSnack, BigSnack };
    SnackType snackType;


    sf::Vector2i gridPos;

    Snack(SnackType type, sf::Vector2i gridPos);
    void Draw(sf::RenderWindow& rw);
private:
    sf::Texture text;
    sf::RectangleShape rect;
};