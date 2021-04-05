#include "GameManager.h"
#include <Windows.h>
GameManager* gameManager = new GameManager();

int main()
{
#ifdef NDEBUG
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
#endif

    gameManager->StartGameManager();

    gameManager->Update();

    delete gameManager;
    return 0;
}
