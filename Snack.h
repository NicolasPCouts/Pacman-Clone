#pragma once
#include "Common.h"

struct Snack {
    enum SnackType { SmallSnack, BigSnack };
    SnackType snackType;

    sf::RectangleShape rect;
    sf::Texture text;

    Snack(SnackType type) 
    {

    }
};