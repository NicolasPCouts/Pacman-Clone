#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(std::vector<sf::Texture> textures);
	Animation(std::vector<sf::Texture> textures, bool loop);
	sf::Texture* GetTexture();
	void Reset();
private:
	bool loop = true;
	std::vector<sf::Texture> textures;
	int currentTexture = 0;
};