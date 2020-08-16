#pragma once
#include "../Common.h"

enum Directions {
	Up,
	Down,
	Left,
	Right,
	None
};

class Entity
{
public:
	float speed = 80;
	sf::Vector2i gridPos;
	Directions currentDir = Directions::None;
	sf::RectangleShape body;
	sf::Texture texture;
	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow& rw) = 0;
protected:
	sf::Vector2f GetFinalTilePosition();
	bool IsNeighbourTileAvailable(Directions dir);
	bool IsTeleportTile(sf::Vector2i pos);
	void Teleport(Directions teleportTo);
	virtual void UpdateTileArray(sf::Vector2i newPos) = 0;
	virtual void Move() = 0;
};

Directions GetOppositeDirection(Directions dir);