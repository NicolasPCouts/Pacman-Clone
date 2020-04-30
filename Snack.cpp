#include "Snack.h"
#include "GameManager.h"

extern GameManager* gameManager;

Snack::Snack(SnackType type, sf::Vector2i gridPos)
{
    snackType = type;
    if (type == SmallSnack)
    {
        body = sf::RectangleShape(sf::Vector2f(gameManager->tileWidth, gameManager->tileHeight));
        texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(226, 240, 6, 6));
        body.setFillColor(sf::Color::White);
        body.setTexture(&texture);
        body.move(sf::Vector2f(gameManager->tileWidth * gridPos.x, gameManager->tileHeight * gridPos.y));
    }
}

void Snack::Draw(sf::RenderWindow& rw)
{
    if(snackType == SmallSnack)
        rw.draw(body);
}
