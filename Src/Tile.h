#pragma once

struct sTile {
    enum TileType { None, Wall, Ghost, GhostHouse, Player, Snack };

    bool isEmpty = true;
    TileType tileType = Wall;
};