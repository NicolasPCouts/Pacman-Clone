#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
	float switchTime = 0.05f;
	Animation(std::vector<sf::Texture> textures);
	Animation(std::vector<sf::Texture> textures, bool loop);
	Animation(std::vector<sf::Texture> textures, bool loop, float switchTime);
	sf::Texture* GetTexture();
	void Reset();
private:
	bool loop = true;
	std::vector<sf::Texture> textures;
	int currentTexture = 0;
};