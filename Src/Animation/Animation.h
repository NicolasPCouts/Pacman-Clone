#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(std::vector<sf::Texture> textures);
	sf::Texture* GetTexture();
private:
	std::vector<sf::Texture> textures;
	int currentTexture = 0;
};