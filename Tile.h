#pragma once

struct Tile {
    enum TileType { None, Wall, Enemy, Player, Snack };

    bool isEmpty = true;
    TileType tileType = Wall;
};