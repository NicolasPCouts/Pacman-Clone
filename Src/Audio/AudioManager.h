#pragma once

#include "SFML/Audio.hpp"
#include "AudioAssets.h"


//ATTENTION!! I know there is much better ways to do a audio manager, but i am feeling really lazy and i just want to finish this project as soon as possible, so DONT JUDGE ME...thanks
class AudioManager
{
public:
	AudioManager();
	void PlaySound(Sounds soundType, bool loop, int volume);
	void StopSound(Sounds soundType = Sounds::None);
	bool IsPlayingAudio(Sounds soundType);
private:

	sf::SoundBuffer gameStartBuffer;
	sf::Sound gameStartSound;

	sf::SoundBuffer munchSoundBuffer;
	sf::Sound munchSound;

	sf::SoundBuffer powerSnackBuffer;
	sf::Sound powerSnackSound;

	sf::SoundBuffer eatGhostBuffer;
	sf::Sound eatGhostSound;

	sf::SoundBuffer deathBuffer;
	sf::Sound deathSound;

	sf::SoundBuffer sirenBuffer;
	sf::Sound sirenSound;

	sf::SoundBuffer retreatingBuffer;
	sf::Sound retreatingSound;
};

