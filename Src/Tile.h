#pragma once

struct sTile {
    enum TileType { None, Wall, Ghost, GhostHouse, Player, Snack };

    bool isEmpty = true;
    TileType tileType = Wall;
    static int GetDistanceBetweenTiles(sf::Vector2i a, sf::Vector2i b)
    {
        return std::sqrt(std::pow(a.x - b.x, 2) +
            std::pow(a.y - b.y, 2) * 1.0);
    }
};
