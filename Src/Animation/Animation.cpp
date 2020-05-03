#include "Animation.h"

Animation::Animation(std::vector<sf::Texture> textures)
{
	this->textures = textures;
}

sf::Texture* Animation::GetTexture()
{
	sf::Texture* textToReturn = &textures[currentTexture];

	if (currentTexture == textures.size())
		currentTexture = 0;
	else
		currentTexture++;

	return textToReturn;
}
