#include "Debug.h"

void DrawGrid(sf::RenderWindow& window, GameState* gameState)
{
    sf::Vector2f vec(0, 0);
    for (int y = 0; y < NumberOfTilesY; y++)
    {
        vec.x = 0;
        for (int x = 0; x < NumberOfTilesX; x++)
        {
            sf::VertexArray quad(sf::LinesStrip, 5);

            quad[0].color = sf::Color::White;
            quad[1].color = sf::Color::White;
            quad[2].color = sf::Color::White;
            quad[3].color = sf::Color::White;
            quad[4].color = sf::Color::White;
            //if (!tileArray[x][y].isEmpty)
            //{
            //    if (tileArray[x][y].tileType == sTile::Player)
            //    {
            //        quad[0].color = sf::Color::Green;
            //        quad[1].color = sf::Color::Green;
            //        quad[2].color = sf::Color::Green;
            //        quad[3].color = sf::Color::Green;
            //        quad[4].color = sf::Color::Green;
            //    }
            //    else
            //    {
            //        quad[0].color = sf::Color::Red;
            //        quad[1].color = sf::Color::Red;
            //        quad[2].color = sf::Color::Red;
            //        quad[3].color = sf::Color::Red;
            //        quad[4].color = sf::Color::Red;
            //    }
            //}


            quad[0].position = vec;

            sf::Vector2f v = vec;
            v.x += gameState->tileWidth;
            quad[1].position = v;

            quad[2].position = sf::Vector2f(vec.x + gameState->tileWidth, vec.y + gameState->tileHeight);

            sf::Vector2f v2 = vec;
            v2.y += gameState->tileHeight;
            quad[3].position = v2;

            quad[4].position = vec;

            window.draw(quad);
            vec.x += gameState->tileWidth;
        }
        vec.y += gameState->tileHeight;
    }
}

void DrawCube(sf::RenderWindow& window, sf::Vector2i pos, GameState* gameState)
{
    sf::Vector2f vec;
    vec.x = pos.x * gameState->tileWidth;
    vec.y = pos.y * gameState->tileHeight;
    sf::VertexArray quad(sf::LinesStrip, 5);

    quad[0].color = sf::Color::Red;
    quad[1].color = sf::Color::Red;
    quad[2].color = sf::Color::Red;
    quad[3].color = sf::Color::Red;
    quad[4].color = sf::Color::Red;

    quad[0].position = vec;
    sf::Vector2f v = vec;
    v.x += gameState->tileWidth;
    quad[1].position = v;

    quad[2].position = sf::Vector2f(vec.x + gameState->tileWidth, vec.y + gameState->tileHeight);

    sf::Vector2f v2 = vec;
    v2.y += gameState->tileHeight;
    quad[3].position = v2;

    quad[4].position = vec;

    window.draw(quad);
}

void DrawPathfinding(sf::RenderWindow& window, std::vector<sf::Vector2i>& path, sf::Vector2i pathStart, sf::Vector2i pathTarget, GameState* gameState)
{
    for (sf::Vector2i pos : path)
    {
        sf::Vector2f vec;
        vec.x = pos.x * gameState->tileWidth;
        vec.y = pos.y * gameState->tileHeight;
        sf::VertexArray quad(sf::LinesStrip, 5);

        quad[0].color = sf::Color::Green;
        quad[1].color = sf::Color::Green;
        quad[2].color = sf::Color::Green;
        quad[3].color = sf::Color::Green;
        quad[4].color = sf::Color::Green;

        quad[0].position = vec;

        sf::Vector2f v = vec;
        v.x += gameState->tileWidth;
        quad[1].position = v;

        quad[2].position = sf::Vector2f(vec.x + gameState->tileWidth, vec.y + gameState->tileHeight);

        sf::Vector2f v2 = vec;
        v2.y += gameState->tileHeight;
        quad[3].position = v2;

        quad[4].position = vec;

        window.draw(quad);
    }


    sf::Vector2f vec;
    vec.x = pathStart.x * gameState->tileWidth;
    vec.y = pathStart.y * gameState->tileHeight;
    sf::VertexArray quad(sf::LinesStrip, 5);

    quad[0].color = sf::Color::Red;
    quad[1].color = sf::Color::Red;
    quad[2].color = sf::Color::Red;
    quad[3].color = sf::Color::Red;
    quad[4].color = sf::Color::Red;

    quad[0].position = vec;
    sf::Vector2f v = vec;
    v.x += gameState->tileWidth;
    quad[1].position = v;

    quad[2].position = sf::Vector2f(vec.x + gameState->tileWidth, vec.y + gameState->tileHeight);

    sf::Vector2f v2 = vec;
    v2.y += gameState->tileHeight;
    quad[3].position = v2;

    quad[4].position = vec;

    window.draw(quad);

    vec.x = pathTarget.x * gameState->tileWidth;
    vec.y = pathTarget.y * gameState->tileHeight;

    quad[0].position = vec;
    v = vec;
    v.x += gameState->tileWidth;
    quad[1].position = v;

    quad[2].position = sf::Vector2f(vec.x + gameState->tileWidth, vec.y + gameState->tileHeight);

    v2 = vec;
    v2.y += gameState->tileHeight;
    quad[3].position = v2;

    quad[4].position = vec;

    window.draw(quad);
}