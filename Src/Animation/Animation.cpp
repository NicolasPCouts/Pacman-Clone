#include "Animation.h"

Animation::Animation(std::vector<sf::Texture> textures)
{
	this->textures = textures;
}

Animation::Animation(std::vector<sf::Texture> textures, bool loop)
{
	this->textures = textures;
	this->loop = loop;
}

void Animation::Reset()
{
	currentTexture = 0;
}

sf::Texture* Animation::GetTexture()
{
	sf::Texture* textToReturn = &textures[currentTexture];

	if (currentTexture == textures.size() - 1)
	{
		if (loop)
			currentTexture = 0;
	}
	else
		currentTexture++;

	return textToReturn;
}
