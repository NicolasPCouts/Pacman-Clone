#include "GameManager.h"
#include "Entity/Pacman/Pacman.h"
#include "Entity/Enemy/Enemy.h"

#include "Pathfinding/Pathfinding.h"

void GameManager::StartGameManager()
{
    window = new sf::RenderWindow();
    window->create(sf::VideoMode::getFullscreenModes()[0], "Pacman", sf::Style::Resize);
    LoadMap();
    aspectRatio = float(window->getSize().x) / float(window->getSize().y);
    sf::View v(sf::Vector2f(400, 400), sf::Vector2f(800 * aspectRatio, 800));
    window->setView(v);
    LoadMap();

    CreateMapColliders();
    pacman = new Pacman(5, 1);
    enemy = new Enemy(9, 1);
    CreateSnacks();
}

GameManager::~GameManager()
{
    delete pacman;
    delete enemy;
    delete window;
    DeleteSnacks();
}

void GameManager::Update()
{
    deltaTime = clock.restart().asSeconds();
    while (window->isOpen())
    {
        //get input
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                pacman->OnKeyPressed(event.key);
                break;
            case sf::Event::Resized:
                aspectRatio = float(window->getSize().x) / float(window->getSize().y);
                sf::View v(sf::Vector2f(400, 400), sf::Vector2f(800 * aspectRatio, 800));
                window->setView(v);
                break;
            }
        }

        //Logic
        pacman->Update();

        //render
        Draw();
    }
}

void GameManager::Draw()
{
    window->clear();
    window->draw(mapSprite);


    for (auto const& x : SnackList)
        x->Draw(*window);

    pacman->Draw(*window);
    enemy->Draw(*window);


    window->display();
}

void GameManager::LoadMap()
{
    if (mapTexture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(0, 0, 226, 248)))
    {
        mapTexture.setSmooth(false);
        mapSprite.setTexture(mapTexture);
        mapSprite.setScale((window->getView().getSize().x) / (mapSprite.getLocalBounds().width * aspectRatio), window->getView().getSize().y / mapSprite.getLocalBounds().height);
        mapSprite.move(0, 1);
    }
    else
    {
        std::cout << "texture not loaded correctly" << std::endl;
    }
}

void GameManager::CreateMapColliders()
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
    for (int i = 1; i <= 4; i++)
    {
        tileArray[13][i].isEmpty = false;
        tileArray[14][i].isEmpty = false;
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
    for (int i = 0; i <= 5; i++)
    {
        tileArray[i][10].isEmpty = false;
        tileArray[i][11].isEmpty = false;
        tileArray[i][12].isEmpty = false;
        tileArray[i + 22][10].isEmpty = false;
        tileArray[i + 22][11].isEmpty = false;
        tileArray[i + 22][12].isEmpty = false;

        tileArray[i][16].isEmpty = false;
        tileArray[i][17].isEmpty = false;
        tileArray[i][18].isEmpty = false;
        tileArray[i + 22][16].isEmpty = false;
        tileArray[i + 22][17].isEmpty = false;
        tileArray[i + 22][18].isEmpty = false;
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
    for (int i = 11; i <= 16; i++)
    {
        tileArray[i][13].isEmpty = false;
        tileArray[i][14].isEmpty = false;
        tileArray[i][15].isEmpty = false;

        tileArray[i][13].tileType = sTile::EnemyCenter;
        tileArray[i][14].tileType = sTile::EnemyCenter;
        tileArray[i][15].tileType = sTile::EnemyCenter;
    }
}

void GameManager::CreateSnacks()
{
    //BIG SNACKS
    sf::Vector2i bigSnackPosArray[4] { sf::Vector2i(1,3), sf::Vector2i(26,3), sf::Vector2i(1,23), sf::Vector2i(26,23) };
    for (const auto& snackPos : bigSnackPosArray)
    {
        tileArray[snackPos.x][snackPos.y].isEmpty = false;
        tileArray[snackPos.x][snackPos.y].tileType = sTile::Snack;
        Snack* s = new Snack(Snack::BigSnack, sf::Vector2i(snackPos.x, snackPos.y));
        SnackList.push_back(s);
    }

    //SMALL SNACKS
    for (int x = 0; x < numberOfTilesX; x++)
    {
        for (int y = 0; y < numberOfTilesY; y++)
        {
            if (tileArray[x][y].isEmpty)
            {
                tileArray[x][y].isEmpty = false;
                tileArray[x][y].tileType = sTile::Snack;
                Snack* s = new Snack(Snack::SmallSnack, sf::Vector2i(x, y));
                SnackList.push_back(s);
            }
        }
    }
}


int GameManager::FindSnackID(sf::Vector2i snackPos)
{
    for (int i = 0; i < SnackList.size(); i++)
    {
        if(SnackList[i]->gridPos == snackPos)
        {
            return i;
        }
    }
    return -1;
}

void GameManager::DeleteSnack(sf::Vector2i snackPos)
{
    int id = FindSnackID(snackPos);
    if(id != -1)
    {
        delete SnackList[id];
        SnackList.erase(SnackList.begin() + id);
    }
}

void GameManager::DeleteSnacks()
{
    for (auto const& x : SnackList)
        delete x;

    SnackList.clear();
}