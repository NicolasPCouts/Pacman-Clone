#include "GameManager.h"
#include <SFML/Graphics.hpp>

sf::RenderWindow window(sf::VideoMode(800, 800), "Pac-Man", sf::Style::Close);
GameManager gameManager = GameManager();

int main()
{
    gameManager.Update();
    return 0;
}
