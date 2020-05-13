#pragma once
#include "../../Common.h"

#include "../Entity.h"

class Snack : public Entity {
public:
    enum SnackType { SmallSnack, BigSnack };
    SnackType snackType;

    Snack(SnackType type, sf::Vector2i gridPos);
    void Draw(sf::RenderWindow& rw) override;
    void Move() {};
    void Update() {};
};