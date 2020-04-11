#pragma once
#include <SFML\Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	sf::Vector2f GetPosition() { return body.getPosition(); }
	bool CheckCollision(Collider& other);
private:
	sf::RectangleShape& body;
};

