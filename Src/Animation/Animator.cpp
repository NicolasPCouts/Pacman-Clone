#include "Animator.h"

Animator::Animator(sf::RectangleShape* body)
{
	this->body = body;
}

void Animator::SetAnimationClip(Animation* anim) 
{
	if(currentClip != NULL)
		currentClip->Reset();

	currentClip = anim;
}

void Animator::Update()
{
	if (currentClip != NULL)
	{
		sf::Texture* t = currentClip->GetTexture();
		if(t != NULL)
			body->setTexture(t);
	}
}
