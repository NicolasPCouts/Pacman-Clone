#include "Snack.h"
#include "../../States/GameState/GameState.h"

Snack::Snack(SnackType type, sf::Vector2i gridPos, GameState* gameState)
    : Entity(gameState)
{
    snackType = type;
    if (type == SmallSnack)
    {
        body = sf::RectangleShape(sf::Vector2f(gameState->tileWidth, gameState->tileHeight));
        texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(226, 240, 7, 7));
    }
    else
    {
        body = sf::RectangleShape(sf::Vector2f(gameState->tileWidth, gameState->tileHeight));
        texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(233, 240, 8, 8));
    }
    this->gridPos = gridPos;
    body.setTexture(&texture);
    body.move(sf::Vector2f(gameState->tileWidth * gridPos.x, gameState->tileHeight * gridPos.y));
}

void Snack::Draw(sf::RenderWindow& rw)
{
    rw.draw(body);
}
