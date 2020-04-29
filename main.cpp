#include "Common.h"
#include "Tile.h"
#include "Pacman.h"

sf::RenderWindow window(sf::VideoMode(800, 800), "Pac-Man", sf::Style::Close);

sf::Sprite mapSprite;
sf::Texture mapTexture;

Pacman pacman = Pacman(5,1);

Tile tileArray[28][31];

bool showTiles = true;

int numberOfTilesX = sizeof(tileArray) / sizeof(tileArray[0]);
int numberOfTilesY = sizeof(tileArray[0]) / sizeof(tileArray[0][0]);
float tileWidth = 800 / (float)numberOfTilesX;
float tileHeight = 800 / (float)numberOfTilesY;

void Draw();
void LoadMap();
void CreateMapColliders();

int main()
{
    LoadMap();
    CreateMapColliders();

    while (window.isOpen())
    {
        //get input
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) 
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    pacman.OnKeyPressed(event.key);
                    break;
            }
        }

        //Logic
        pacman.Update();

        //render
        Draw();
    }

    return 0;
}


void LoadMap()
{
    if (mapTexture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(0, 0, 226, 248)))
    {
        mapTexture.setSmooth(false);
        mapSprite.setTexture(mapTexture);
        mapSprite.setScale(window.getSize().x / mapSprite.getLocalBounds().width, window.getSize().y / mapSprite.getLocalBounds().height);
        mapSprite.move(0, 1);
    }
    else 
    {
        std::cout << "texture not loaded correctly" << std::endl;
    }
}

void Draw() 
{
    window.clear();
    window.draw(mapSprite);
    window.draw(pacman.body);

    sf::Texture text;
    text.loadFromFile("Resources/PacManSprites.png", sf::IntRect(226, 240, 6, 6));

    sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(tileWidth, tileHeight));
    rect.setFillColor(sf::Color::White);
    rect.setTexture(&text);
    rect.move(sf::Vector2f(tileWidth * 6, tileHeight * 4));
    window.draw(rect);

    sf::Vector2f vec(0, 0);

    if (showTiles)
    {
        for (int y = 0; y < numberOfTilesY; y++)
        {
            vec.x = 0;
            for (int x = 0; x < numberOfTilesX; x++)
            {
                sf::VertexArray quad(sf::LinesStrip, 5);
                quad[0].color = sf::Color::Transparent;
                quad[1].color = sf::Color::Transparent;
                quad[2].color = sf::Color::Transparent;
                quad[3].color = sf::Color::Transparent;
                quad[4].color = sf::Color::Transparent;
                if (!tileArray[x][y].isEmpty)
                {
                    if (tileArray[x][y].tileType == Tile::Player) 
                    {
                        quad[0].color = sf::Color::Green;
                        quad[1].color = sf::Color::Green;
                        quad[2].color = sf::Color::Green;
                        quad[3].color = sf::Color::Green;
                        quad[4].color = sf::Color::Green;
                    }
                    else
                    {
                        quad[0].color = sf::Color::Red;
                        quad[1].color = sf::Color::Red;
                        quad[2].color = sf::Color::Red;
                        quad[3].color = sf::Color::Red;
                        quad[4].color = sf::Color::Red;
                    }
                }
                quad[0].position = vec;

                sf::Vector2f v = vec;
                v.x += tileWidth;
                quad[1].position = v;

                quad[2].position = sf::Vector2f(vec.x + tileWidth, vec.y + tileHeight);

                sf::Vector2f v2 = vec;
                v2.y += tileHeight;
                quad[3].position = v2;

                quad[4].position = vec;

                window.draw(quad);
                vec.x += tileWidth;
            }
            vec.y += tileHeight;
        }
    }

    window.display();
}

void CreateMapColliders() 
{
    for (int i = 0; i < numberOfTilesX; i++)
    {
        tileArray[i][0].isEmpty = false;
        tileArray[i][numberOfTilesY - 1].isEmpty = false;
    }
    for (int i = 2; i <= 5; i++)
    {
        tileArray[i][2].isEmpty = false;
        tileArray[i][3].isEmpty = false;
        tileArray[i][4].isEmpty = false;

        tileArray[i + 20][2].isEmpty = false;
        tileArray[i + 20][3].isEmpty = false;
        tileArray[i + 20][4].isEmpty = false;
    }
    for (int i = 7; i <= 11; i++)
    {
        tileArray[i][2].isEmpty = false;
        tileArray[i][3].isEmpty = false;
        tileArray[i][4].isEmpty = false;

        tileArray[i + 9][2].isEmpty = false;
        tileArray[i + 9][3].isEmpty = false;
        tileArray[i + 9][4].isEmpty = false;
    }
    for (int i = 2; i <= 5; i++)
    {
        tileArray[i][6].isEmpty = false;
        tileArray[i][7].isEmpty = false;

        tileArray[i + 20][6].isEmpty = false;
        tileArray[i + 20][7].isEmpty = false;
    }
    for (int i = 10; i <= 17; i++)
    {
        tileArray[i][6].isEmpty = false;
        tileArray[i][7].isEmpty = false;

        tileArray[i][18].isEmpty = false;
        tileArray[i][19].isEmpty = false;

        tileArray[i][24].isEmpty = false;
        tileArray[i][25].isEmpty = false;
    }
    for (int i = 8; i <= 10; i++)
    {
        tileArray[13][i].isEmpty = false;
        tileArray[14][i].isEmpty = false;

        tileArray[13][i + 12].isEmpty = false;
        tileArray[14][i + 12].isEmpty = false;

        tileArray[13][i + 18].isEmpty = false;
        tileArray[14][i + 18].isEmpty = false;
    }
    for (int i = 6; i <= 13; i++)
    {
        tileArray[7][i].isEmpty = false;
        tileArray[8][i].isEmpty = false;

        tileArray[7 + 12][i].isEmpty = false;
        tileArray[8 + 12][i].isEmpty = false;
    }
    for (int i = 1; i < 10; i++)
    {
        tileArray[0][i].isEmpty = false;
        tileArray[numberOfTilesX - 1][i].isEmpty = false;
    }
    for (int i = 19; i < 30; i++)
    {
        tileArray[0][i].isEmpty = false;
        tileArray[numberOfTilesX - 1][i].isEmpty = false;
    }
    for (int i = 0; i <= 5; i++)
    {
        tileArray[i][9].isEmpty = false;
        tileArray[i][9 + 4].isEmpty = false;
        tileArray[i][9 + 6].isEmpty = false;
        tileArray[i][9 + 10].isEmpty = false;

        tileArray[i + 22][9].isEmpty = false;
        tileArray[i + 22][9 + 4].isEmpty = false;
        tileArray[i + 22][9 + 6].isEmpty = false;
        tileArray[i + 22][9 + 10].isEmpty = false;
    }
    for (int i = 10; i <= 12; i++)
    {
        tileArray[5][i].isEmpty = false;
        tileArray[22][i].isEmpty = false;
        tileArray[5][i + 6].isEmpty = false;
        tileArray[22][i + 6].isEmpty = false;
    }
    for (int i = 10; i <= 17; i++)
    {
        tileArray[i][12].isEmpty = false;
        tileArray[i][16].isEmpty = false;
    }
    for (int i = 13; i <= 15; i++)
    {
        tileArray[10][i].isEmpty = false;
        tileArray[17][i].isEmpty = false;
    }

    for (int i = 9; i < 12; i++)
    {
        tileArray[i][9].isEmpty = false;
        tileArray[i][10].isEmpty = false;
        tileArray[i + 7][9].isEmpty = false;
        tileArray[i + 7][10].isEmpty = false;
    }
    for (int i = 15; i <= 19; i++)
    {
        tileArray[7][i].isEmpty = false;
        tileArray[8][i].isEmpty = false;
        tileArray[7 + 12][i].isEmpty = false;
        tileArray[8 + 12][i].isEmpty = false;
    }
    for (int i = 7; i <= 11; i++)
    {
        tileArray[i][21].isEmpty = false;
        tileArray[i][22].isEmpty = false;
        tileArray[i + 9][21].isEmpty = false;
        tileArray[i + 9][22].isEmpty = false;
    }
    for (int i = 24; i <= 26; i++)
    {
        tileArray[7][i].isEmpty = false;
        tileArray[8][i].isEmpty = false;
        tileArray[7 + 12][i].isEmpty = false;
        tileArray[8 + 12][i].isEmpty = false;
    }
    for (int i = 2; i <= 11; i++)
    {
        tileArray[i][27].isEmpty = false;
        tileArray[i][28].isEmpty = false;
        tileArray[i + 14][27].isEmpty = false;
        tileArray[i + 14][28].isEmpty = false;
    }
    for (int i = 1; i <= 2; i++)
    {
        tileArray[i][24].isEmpty = false;
        tileArray[i][25].isEmpty = false;
        tileArray[i + 24][24].isEmpty = false;
        tileArray[i + 24][25].isEmpty = false;
    }
    for (int i = 21; i <= 25; i++)
    {
        tileArray[4][i].isEmpty = false;
        tileArray[5][i].isEmpty = false;
        tileArray[22][i].isEmpty = false;
        tileArray[23][i].isEmpty = false;
    }
    for (int i = 2; i <= 3; i++)
    {
        tileArray[i][21].isEmpty = false;
        tileArray[i][22].isEmpty = false;
        tileArray[i + 22][21].isEmpty = false;
        tileArray[i + 22][22].isEmpty = false;
    }
}