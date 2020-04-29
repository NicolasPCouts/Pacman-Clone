#pragma once
#include "Common.h"


struct Snack {
    enum SnackType { SmallSnack, BigSnack };
    SnackType snackType;

    sf::RectangleShape rect;
    sf::Texture text;

    sf::Vector2i gridPos;

    Snack(SnackType type, sf::Vector2i gridPos);
};