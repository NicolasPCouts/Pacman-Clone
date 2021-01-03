#include "GameState.h"

#include <iostream>

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

#include "../MainMenuState/MainMenuState.h"

//test
#include <sstream>

Sounds lastSoundPlayed = Sounds::None;

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states, GameManager* gameManager)
	: State(window, states, gameManager)
{

    CreateMapCollidersAndSnacks();
    CreatePacmanAndEnemys();
    CreateUI();

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

void GameState::OnPacmanDeath() 
{
    if(lifes == 0)
        states->push(new MainMenuState(window, states, gameManager));
    else
    {
        Restart();
    }
}

void GameState::Restart()
{
    audioManager.StopSound();
    lifes--;

    for (auto const& x : enemys)
        delete x;

    delete pacman;

    CreatePacmanAndEnemys();
    audioManager.PlaySound(AUDIO_GAME_START, false, VOLUME);
}

void GameState::Update(const float& deltaTime)
{
    //Logic
    if(isFreezed == false || entityThatWontFreeze == Entities::Pacman)
        pacman->Update(deltaTime);


    for (auto const& x : enemys)
    {
        if (isFreezed == false || entityThatWontFreeze == x->entityType || x->state == EnemyState::Eaten)
        {
            if (x != NULL)
                x->Update(deltaTime);
        }
    }

    for (auto const& x : SnackList)
    {
        x->Update(deltaTime);
    }

    UpdateUI();

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

    //draw walls colliders
    //for (int i = 0; i < NumberOfTilesX; i++)
    //{
    //    for (int j = 0 ; j < NumberOfTilesY; j++)
    //    {
    //        if(tileArray[i][j].DoesTileHaveType(sTile::TileType::Wall))
    //            DrawCube(*window, sf::Vector2i(i, j), this);
    //    }
    //}

    for (auto const& x : enemys)
    {
        if (x != NULL)
            x->Draw(*window);
    }

    window->draw(lifesText);
    window->draw(scoreText);

    window->display();
}

void GameState::LoadMap()
{
    if (mapTexture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(0, 0, 226, 248)))
    {
        mapTexture.setSmooth(false);
        mapSprite.setTexture(mapTexture);
        mapSprite.setScale((window->getView().getSize().x) / (mapSprite.getLocalBounds().width * gameManager->aspectRatio), (window->getView().getSize().y - 100) / mapSprite.getLocalBounds().height);
        mapSprite.move(0, 1);
    }
    else
    {
        std::cout << "texture not loaded correctly" << std::endl;
    }
}

void GameState::CreateMapCollidersAndSnacks()
{
    int mapDesign[NumberOfTilesY][NumberOfTilesX] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,3,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,3,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,0,1,1,1,1,1,5,1,1,5,1,1,1,1,1,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,1,1,1,5,1,1,5,1,1,1,1,1,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,5,5,5,5,5,5,5,5,5,5,1,1,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,5,1,1,1,2,2,1,1,1,5,1,1,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,5,1,2,2,2,2,2,2,1,5,1,1,0,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,5,5,5,1,2,2,2,2,2,2,1,5,5,5,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,0,1,1,5,1,2,2,2,2,2,2,1,5,1,1,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,5,1,1,1,1,1,1,1,1,5,1,1,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,5,5,5,5,5,5,5,5,5,5,1,1,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,5,1,1,1,1,1,1,1,1,5,1,1,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,5,1,1,1,1,1,1,1,1,5,1,1,0,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,3,0,0,1,1,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,1,1,0,0,3,1},
    {1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
    {1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
    {1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    for (int y = 0; y < NumberOfTilesY; y++)
    {
        for (int x = 0; x < NumberOfTilesX; x++)
        {
            if (mapDesign[y][x] == 0) // small snack
            {
                tileArray[x][y].isEmpty = false;
                tileArray[x][y].tileTypes.push_back(sTile::Snack);
                Snack* s = new Snack(Snack::SmallSnack, sf::Vector2i(x, y), this);
                SnackList.push_back(s);
            }
            else if (mapDesign[y][x] == 1) // wall collider
            {
                tileArray[x][y].isEmpty = false;
                tileArray[x][y].tileTypes.push_back(sTile::Wall);
            }
            else if (mapDesign[y][x] == 2) // ghost house
            {
                tileArray[x][y].isEmpty = false;
                tileArray[x][y].tileTypes.push_back(sTile::GhostHouse);
            }
            else if (mapDesign[y][x] == 3) // big snack
            {
                tileArray[x][y].isEmpty = false;
                tileArray[x][y].tileTypes.push_back(sTile::Snack);
                Snack* s = new Snack(Snack::BigSnack, sf::Vector2i(x, y), this);
                SnackList.push_back(s);
            }
            else if (mapDesign[y][x] == 5) // empty
            {
            }
        }
    }


}

void GameState::CreatePacmanAndEnemys() 
{
    pacman = new Pacman(13, 23, this);
    enemys[0] = new Blinky(sf::Vector2i(13, 12), this);
    enemys[1] = new Pinky(sf::Vector2i(11, 14), this);
    enemys[2] = new Inky(sf::Vector2i(13, 14), this);
    enemys[3] = new Clyde(sf::Vector2i(15, 14), this);
}

void GameState::CreateUI()
{
    font.loadFromFile("Fonts/Dosis-Light.ttf");

    //creating score text
    this->scoreText.setFont(this->font);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setCharacterSize(36);
    this->scoreText.setPosition(10, 800);

    //creating lives text
    this->lifesText.setFont(this->font);
    this->lifesText.setFillColor(sf::Color::White);
    this->lifesText.setCharacterSize(36);
    this->lifesText.setPosition(10, 850);

    UpdateUI();
}

void GameState::UpdateUI() 
{
    this->scoreText.setString("Score : " + std::to_string(score));
    this->lifesText.setString("Lifes : " + std::to_string(lifes));
}

void GameState::FreezeGame(Entities entityThatWontFreeze)
{
    isFreezed = true;
    this->entityThatWontFreeze = entityThatWontFreeze;
}

void GameState::UnfreezeGame()
{
    isFreezed = false;
    this->entityThatWontFreeze = Entities::NotDefined;
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