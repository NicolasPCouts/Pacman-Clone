#include "GameManager.h"
GameManager* gameManager = new GameManager();

int main()
{
    gameManager->StartGameManager();

    gameManager->Update();

    delete gameManager;
    return 0;
}
