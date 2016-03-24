#pragma once

#include "Entities.h"

const auto TILE_SIZE = 32.0f;

class Tile : public Entity {
protected:

public:
	Tile(float size, const sf::Vector2f &init_pos, std::string file_name) : Entity(file_name,sf::Vector2i(TILE_SIZE,TILE_SIZE)) {
		setPos(init_pos + sf::Vector2f(size / 2.0f, size / 2.0f));
		setOrigin(sf::Vector2f(size / 2.0f, size / 2.0f));
	}

	void virtual DoSomethingOnCollision(Entity* collided) = 0;


	void resolveColision(Entity* collided);

};
