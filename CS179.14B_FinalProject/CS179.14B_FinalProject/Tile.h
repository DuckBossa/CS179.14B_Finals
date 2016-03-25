#pragma once

#include "Entities.h"

const auto TILE_SIZE = 32;

class Tile : public Entity {
protected:

public:
	Tile(int size, const sf::Vector2f &init_pos, std::string file_name) : Entity(file_name,sf::Vector2i(TILE_SIZE,TILE_SIZE)) {
		setPos(init_pos + sf::Vector2f(size / 2.0f, size / 2.0f));
		setOrigin(sf::Vector2f(size / 2.0f, size / 2.0f));
	}

	void virtual DoSomethingOnCollision(Entity* collided) = 0;


	void resolveColision(Entity* collided);

};


class NormalTile : public Tile {

public:
	NormalTile(const int &size, const sf::Vector2f &init_pos, string file_name) : Tile(size, init_pos, file_name) {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;

};

class LavaTile : public Tile {
public:
	LavaTile(const int &size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, init_pos, "lava") {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;
};
