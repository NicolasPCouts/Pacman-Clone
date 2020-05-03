#pragma once

#include "Animation.h"
#include <SFML/Graphics.hpp>

class Animator
{
public:
	Animator(sf::RectangleShape* body);
	void SetAnimationClip(Animation* anim);
	void Update();
private:
	Animation* currentClip;
	sf::RectangleShape* body;
};

