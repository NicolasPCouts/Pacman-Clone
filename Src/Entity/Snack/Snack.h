#pragma once
#include "../../Common.h"

#include "../Entity.h"

class Snack : public Entity {
public:
    enum SnackType { SmallSnack, BigSnack };
    SnackType snackType;

    Snack(SnackType type, sf::Vector2i gridPos);
    void UpdateTileArray(sf::Vector2i newPos) {};
    void Move() {};
    void Update() {};
    void Draw(sf::RenderWindow& rw) override;
};