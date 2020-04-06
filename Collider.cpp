#include "Collider.h"

Collider::Collider(sf::RectangleShape& body) : body(body)
{
}

Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider& other)
{
	return true;
}