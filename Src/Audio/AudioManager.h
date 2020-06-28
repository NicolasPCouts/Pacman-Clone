#pragma once

#include "SFML/Audio.hpp"

class AudioManager
{
public:
	AudioManager();
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

