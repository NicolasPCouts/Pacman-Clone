#include "Snack.h"
#include "GameManager.h"

extern GameManager* gameManager;

Snack::Snack(SnackType type, sf::Vector2i gridPos)
{
    snackType = type;
    if (type == SmallSnack)
    {
        rect = sf::RectangleShape(sf::Vector2f(gameManager->tileWidth, gameManager->tileHeight));
        text.loadFromFile("Resources/PacManSprites.png", sf::IntRect(226, 240, 6, 6));
        rect.setFillColor(sf::Color::White);
        rect.setTexture(&text);
        rect.move(sf::Vector2f(gameManager->tileWidth * gridPos.x, gameManager->tileHeight * gridPos.y));
    }
}

void Snack::Draw(sf::RenderWindow& rw)
{
    if(snackType == SmallSnack)
        rw.draw(rect);
}
