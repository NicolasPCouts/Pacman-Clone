#include "AudioManager.h"

#include <iostream>


void AudioManager::PlaySound(std::string path, bool loop, int volume)
{
    if (!buffer.loadFromFile(path))
        std::cout << "Cannot load audio file >> " << path << std::endl;
    else
    {
        sound.setBuffer(buffer);
        sound.setLoop(loop);
        sound.setVolume(volume);
        sound.play();
    }
}

void AudioManager::StopSound() 
{
    sound.stop();
}