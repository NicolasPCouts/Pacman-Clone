#pragma once
#include "../Common.h"

class GameState;

enum Directions {
	Up,
	Down,
	Left,
	Right,
	None
};

enum class Entities {
	NotDefined,
	Pacman,
	Blinky,
	Clyde,
	Inky,
	Pinky,
};

class Entity
{
public:
	Entity(GameState* gameState, Entities entityType);
	float speed = 140;
	sf::Vector2i gridPos;
	Directions currentDir = Directions::None;
	Entities entityType;
	sf::RectangleShape body;
	sf::Texture texture;
	virtual void Update(const float& deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& rw) = 0;
protected:
	GameState* gameState;
	sf::Vector2f GetFinalTilePosition();
	bool IsNeighbourTileAvailable(Directions dir);
	bool IsTeleportTile(sf::Vector2i pos);
	void Teleport(Directions teleportTo);
	virtual void UpdateTileArray(sf::Vector2i newPos) = 0;
	virtual void Move(const float& deltaTime) = 0;
};

Directions GetOppositeDirection(Directions dir);