#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <windows.h>

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;

    // Create the main window
    sf::Window window(sf::VideoMode(640, 480), 
    "SFML window with OpenGL", 
    sf::Style::Default, contextSettings);
}