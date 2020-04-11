#include "Collider.h"
#include <iostream>
Collider::Collider(sf::RectangleShape& body) : body(body)
{
}

Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider& other)
{
	float minX = body.getPosition().x;
	float maxX = body.getPosition().x + body.getSize().x;

	float otherMinX = other.GetPosition().x;
	float otherMaxX = other.GetPosition().x + other.body.getSize().x;

	//std::cout << "PacMan min x : " << minX << "   --   Max x : " << maxX << "   --   Position x : " << body.getPosition().x << std::endl;
	//std::cout << "Square min x : " << otherMinX << "   --   Max x : " << otherMaxX << "   --   Position x : " << other.GetPosition().x << std::endl;

	if (maxX > otherMinX && minX < otherMaxX)
		return true;

	return false;
}