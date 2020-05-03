#include "Animator.h"

Animator::Animator(sf::RectangleShape* body)
{
	this->body = body;
}

void Animator::SetAnimationClip(Animation* anim) 
{
	totalTime = 0;

	if(currentClip != NULL)
		currentClip->Reset();

	currentClip = anim;
}

void Animator::Update(float deltaTime)
{
	totalTime += deltaTime;

	if (currentClip != NULL)
	{
		if (totalTime >= currentClip->switchTime)
		{
			totalTime -= currentClip->switchTime;

			sf::Texture* t = currentClip->GetTexture();
			if (t != NULL)
				body->setTexture(t);
		}
	}
}