#include "Collider.h"
#include <iostream>

std::vector<Collider*> Collider::activeColliders;

Collider::Collider(sf::RectangleShape& body) : body(body)
{
	Collider::activeColliders.push_back(this);
}

Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider& other)
{
	float minX = body.getPosition().x;
	float maxX = body.getPosition().x + body.getSize().x;
	float minY = body.getPosition().y;
	float maxY = body.getPosition().y + body.getSize().y;

	float otherMinX = other.GetPosition().x;
	float otherMaxX = other.GetPosition().x + other.body.getSize().x;
	float otherMinY = other.GetPosition().y;
	float otherMaxY = other.GetPosition().y + other.body.getSize().y;

	if ((maxX > otherMinX && minX < otherMaxX) 
		&& (maxY > otherMinY && minY < otherMaxY))
		return true;
	else
		return false;
}