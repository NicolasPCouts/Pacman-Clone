#pragma once

struct sTile {
    enum TileType { None, Wall, Enemy, EnemyCenter, Player, Snack };

    bool isEmpty = true;
    TileType tileType = Wall;
};