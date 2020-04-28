#pragma once
#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>


struct Tile {
    enum TileType { None, Wall, Enemy, Player, Snack, BigSnack };

    bool isEmpty = true;
    TileType tileType = Wall;
};