#pragma once

struct sTile {
    enum TileType { None, Wall, Ghost, GhostHouse, Player, Snack };

    bool isEmpty = true;

    std::vector<TileType> tileTypes;

    static int GetDistanceBetweenTiles(sf::Vector2i a, sf::Vector2i b)
    {
        return std::sqrt(std::pow(a.x - b.x, 2) +
            std::pow(a.y - b.y, 2) * 1.0);
    }

    bool DoesTileHaveType(TileType type) {
        for(TileType t : tileTypes)
        {
            if (type == t) return true;
        }
        return false;
    }

    bool DoesTileHaveOnlyType(TileType type) {
        if (tileTypes.size() == 1) {
            if (tileTypes[0] == Wall) return true;
        }
        return false;
    }

    void EraseTileType(TileType type) {
        for (int i = 0; i < tileTypes.size(); i++){
            if (tileTypes[i] == type)
                tileTypes.erase(tileTypes.begin() + i);
        }
    }
};
