#include "AudioManager.h"

#include <iostream>

AudioManager::AudioManager()
{
    if (!buffer.loadFromFile("Resources/Sound/ghost_chase.wav"))
        std::cout << "Cannot load audio file" << std::endl;
    else
    {
        sound.setBuffer(buffer);
        sound.setLoop(true);
        sound.play();
    }
}
