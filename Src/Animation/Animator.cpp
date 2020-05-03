#include "Animator.h"

Animator::Animator(Animation* anim, sf::RectangleShape* body)
{
	currentClip = anim;
	this->body = body;
}

void Animator::SetAnimationClip(Animation* anim) 
{
	currentClip = anim;
}

void Animator::Update()
{
	body->setTexture(currentClip->GetTexture());
}
