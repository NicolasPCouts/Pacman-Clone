#include "GameState.h"

#include "../../Entity/Pacman/Pacman.h"
#include "../../Entity/Enemy/Enemy.h"
#include "../../Entity/Enemy/Blinky.h"
#include "../../Entity/Enemy/Pinky.h"
#include "../../Entity/Enemy/Inky.h"
#include "../../Entity/Enemy/Clyde.h"

#include "../../Debugger/Debug.h"

#include "SFML/Audio.hpp"
#include "../../Audio/AudioAssets.h"
#include "../../Entity/Snack/Snack.h"

//test
#include <sstream>

Sounds lastSoundPlayed = Sounds::None;

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states, GameManager* gameManager)
	: State(window, states, gameManager)
{

    CreateMapColliders();
    pacman = new Pacman(1, 1, this);
    enemys[0] = new Blinky(sf::Vector2i(3, 6), this);
    enemys[1] = new Pinky(sf::Vector2i(3, 1), this);
    enemys[2] = new Inky(sf::Vector2i(5, 6), this);
    enemys[3] = new Clyde(sf::Vector2i(18, 1), this);
    CreateSnacks();

    audioManager.PlaySound(AUDIO_GAME_START, false, VOLUME);
    LoadMap();
}

GameState::~GameState() 
{
    delete pacman;
    for (auto const& x : enemys)
        delete x;

    delete window;
    DeleteSnacks();
}

void GameState::Update(const float& deltaTime)
{
    //Logic
    pacman->Update(deltaTime);
    for (auto const& x : enemys)
    {
        if (x != NULL)
            x->Update(deltaTime);
    }

    //render
    Draw();
}

void GameState::Draw()
{
    window->clear();
    window->draw(mapSprite);

    for (auto const& x : SnackList)
        x->Draw(*window);

    pacman->Draw(*window);

    for (int i = 11; i <= 16; i++)
    {
        DrawCube(*window, sf::Vector2i(i, 13), this);
        DrawCube(*window, sf::Vector2i(i, 14), this);
        DrawCube(*window, sf::Vector2i(i, 15), this);

    }

    for (auto const& x : enemys)
    {
        if (x != NULL)
            x->Draw(*window);
    }

    window->display();
}


void GameState::LoadMap()
{
    if (mapTexture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(0, 0, 226, 248)))
    {
        mapTexture.setSmooth(false);
        mapSprite.setTexture(mapTexture);
        mapSprite.setScale((window->getView().getSize().x) / (mapSprite.getLocalBounds().width * gameManager->aspectRatio), window->getView().getSize().y / mapSprite.getLocalBounds().height);
        mapSprite.move(0, 1);
    }
    else
    {
        std::cout << "texture not loaded correctly" << std::endl;
    }
}

void GameState::CreateMapColliders()
{
    for (int i = 0; i < NumberOfTilesX; i++)
    {
        tileArray[i][0].isEmpty = false;
        tileArray[i][NumberOfTilesY - 1].isEmpty = false;
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
        tileArray[NumberOfTilesX - 1][i].isEmpty = false;
    }
    for (int i = 19; i < 30; i++)
    {
        tileArray[0][i].isEmpty = false;
        tileArray[NumberOfTilesX - 1][i].isEmpty = false;
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

        tileArray[i][13].tileTypes.clear();
        tileArray[i][14].tileTypes.clear();
        tileArray[i][15].tileTypes.clear();

        tileArray[i][13].tileTypes.push_back(sTile::GhostHouse);
        tileArray[i][14].tileTypes.push_back(sTile::GhostHouse);
        tileArray[i][15].tileTypes.push_back(sTile::GhostHouse);
    }
    tileArray[13][12].isEmpty = false;
    tileArray[14][12].isEmpty = false;
    tileArray[13][12].tileTypes.clear();
    tileArray[14][12].tileTypes.clear();
    tileArray[13][12].tileTypes.push_back(sTile::GhostHouse);
    tileArray[14][12].tileTypes.push_back(sTile::GhostHouse);
}

void GameState::CreateSnacks()
{
    //BIG SNACKS
    sf::Vector2i bigSnackPosArray[4]{ sf::Vector2i(1,3), sf::Vector2i(26,3), sf::Vector2i(1,23), sf::Vector2i(26,23) };
    for (const auto& snackPos : bigSnackPosArray)
    {
        tileArray[snackPos.x][snackPos.y].isEmpty = false;
        tileArray[snackPos.x][snackPos.y].tileTypes.clear();
        tileArray[snackPos.x][snackPos.y].tileTypes.push_back(sTile::Snack);
        Snack* s = new Snack(Snack::BigSnack, sf::Vector2i(snackPos.x, snackPos.y), this);
        SnackList.push_back(s);
    }

    //SMALL SNACKS
    for (int x = 0; x < NumberOfTilesX; x++)
    {
        for (int y = 0; y < NumberOfTilesY; y++)
        {
            if (tileArray[x][y].isEmpty)
            {
                tileArray[x][y].isEmpty = false;
                tileArray[x][y].tileTypes.clear();
                tileArray[x][y].tileTypes.push_back(sTile::Snack);
                Snack* s = new Snack(Snack::SmallSnack, sf::Vector2i(x, y), this);
                SnackList.push_back(s);
            }
        }
    }
}


int GameState::FindSnackID(sf::Vector2i snackPos)
{
    for (int i = 0; i < SnackList.size(); i++)
    {
        if (SnackList[i]->gridPos == snackPos)
        {
            return i;
        }
    }
    return -1;
}

void GameState::DeleteSnack(sf::Vector2i snackPos)
{
    int id = FindSnackID(snackPos);
    if (id != -1)
    {
        delete SnackList[id];
        SnackList.erase(SnackList.begin() + id);
    }
}

void GameState::DeleteSnacks()
{
    for (auto const& x : SnackList)
        delete x;

    SnackList.clear();
}

void GameState::ScareEnemys()
{
    for (Enemy* e : enemys)
        if (e != NULL)	e->Scare();

    audioManager.PlaySound(AUDIO_POWER_SNACK, true, VOLUME);
    lastSoundPlayed = Sounds::PowerSnack;
}

void GameState::StopPowerSnackSound()
{
    if (lastSoundPlayed == Sounds::PowerSnack)
    {
        audioManager.StopSound();
        lastSoundPlayed = Sounds::None;
    }
}

Enemy* GameState::FindEnemyByPosition(sf::Vector2i pos)
{
    for (Enemy* e : enemys)
    {
        if (e == NULL) continue;
        if (e->gridPos == pos)
            return e;
    }

    return NULL;
}