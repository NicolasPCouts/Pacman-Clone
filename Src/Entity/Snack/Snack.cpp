#include "Snack.h"
#include "../../GameManager.h"

extern GameManager* gameManager;

Snack::Snack(SnackType type, sf::Vector2i gridPos)
{
    snackType = type;
    if (type == SmallSnack)
    {
        body = sf::RectangleShape(sf::Vector2f(gameManager->tileWidth, gameManager->tileHeight));
        texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(226, 240, 7, 7));
    }
    else
    {
        body = sf::RectangleShape(sf::Vector2f(gameManager->tileWidth, gameManager->tileHeight));
        texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(233, 240, 8, 8));
    }
    this->gridPos = gridPos;
    body.setTexture(&texture);
    body.move(sf::Vector2f(gameManager->tileWidth * gridPos.x, gameManager->tileHeight * gridPos.y));
}

void Snack::Draw(sf::RenderWindow& rw)
{
    rw.draw(body);
}
