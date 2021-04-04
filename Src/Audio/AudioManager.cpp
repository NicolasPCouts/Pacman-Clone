#include "AudioManager.h"

#include <iostream>

AudioManager::AudioManager()
{
    munchSoundBuffer.loadFromFile(AUDIO_MUNCH);
    munchSound.setBuffer(munchSoundBuffer);

    powerSnackBuffer.loadFromFile(AUDIO_POWER_SNACK);
    powerSnackSound.setBuffer(powerSnackBuffer);

    eatGhostBuffer.loadFromFile(AUDIO_EAT_GHOST);
    eatGhostSound.setBuffer(eatGhostBuffer);

    deathBuffer.loadFromFile(AUDIO_DEATH_1);
    deathSound.setBuffer(deathBuffer);

    gameStartBuffer.loadFromFile(AUDIO_GAME_START);
    gameStartSound.setBuffer(gameStartBuffer);

    sirenBuffer.loadFromFile(AUDIO_SIREN);
    sirenSound.setBuffer(sirenBuffer);

    retreatingBuffer.loadFromFile(AUDIO_RETREATING);
    retreatingSound.setBuffer(retreatingBuffer);
}

void AudioManager::PlaySound(Sounds soundType, bool loop, int volume)
{
    //new way
    switch (soundType)
    {
    case Sounds::PowerSnack:
        powerSnackSound.setLoop(loop);
        powerSnackSound.setVolume(volume);
        powerSnackSound.play();
        break;
    case Sounds::EatGhost:
        eatGhostSound.setLoop(loop);
        eatGhostSound.setVolume(volume);
        eatGhostSound.play();
        break;
    case Sounds::Death:
        deathSound.setLoop(loop);
        deathSound.setVolume(volume);
        deathSound.play();
        break;
    case Sounds::Munch:
        munchSound.setLoop(loop);
        munchSound.setVolume(volume);
        munchSound.play();
        break;
    case Sounds::GameStart:
        gameStartSound.setLoop(loop);
        gameStartSound.setVolume(volume);
        gameStartSound.play();
        break;
    case Sounds::Siren:
        sirenSound.setLoop(loop);
        sirenSound.setVolume(volume);
        sirenSound.play();
        break;
    case Sounds::Retreating:
        retreatingSound.setLoop(loop);
        retreatingSound.setVolume(volume);
        retreatingSound.play();
        break;
    }

}

void AudioManager::StopSound(Sounds soundType)
{
    switch (soundType)
    {
    case Sounds::PowerSnack:
        powerSnackSound.stop();
        break;
    case Sounds::EatGhost:
        eatGhostSound.stop();
        break;
    case Sounds::Death:
        deathSound.stop();
        break;
    case Sounds::Munch:
        munchSound.stop();
        break;
    case Sounds::GameStart:
        gameStartSound.stop();
        break;
    case Sounds::Siren:
        sirenSound.stop();
        break;
    case Sounds::Retreating:
        retreatingSound.stop();
        break;
    case Sounds::None:
        gameStartSound.stop();
        munchSound.stop();
        deathSound.stop();
        eatGhostSound.stop();
        powerSnackSound.stop();
        sirenSound.stop();
        retreatingSound.stop();
        break;
    }
}

bool AudioManager::IsPlayingAudio(Sounds soundType)
{
    switch (soundType)
    {
    case Sounds::PowerSnack:
        return powerSnackSound.getStatus() == powerSnackSound.Playing;
        break;
    case Sounds::EatGhost:
        return eatGhostSound.getStatus() == eatGhostSound.Playing;
        break;
    case Sounds::Death:
        return deathSound.getStatus() == deathSound.Playing;
        break;
    case Sounds::Munch:
        return munchSound.getStatus() == munchSound.Playing;
        break;
    case Sounds::GameStart:
        return gameStartSound.getStatus() == gameStartSound.Playing;
        break;
    case Sounds::Siren:
        return sirenSound.getStatus() == sirenSound.Playing;
        break;
    case Sounds::Retreating:
        return retreatingSound.getStatus() == retreatingSound.Playing;
        break;
    }
}