#include "GameManager.h"
GameManager* gameManager = new GameManager();

#include "Pathfinding/Pathfinding.h"

int main()
{
    gameManager->StartGameManager();

    gameManager->Update();

    delete gameManager;
    return 0;
}
