#pragma once

#include "SFML/Audio.hpp"

class AudioManager
{
public:
	void PlaySound(std::string path, bool loop, int volume);
	void StopSound();
	bool IsPlayingAudio();
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

