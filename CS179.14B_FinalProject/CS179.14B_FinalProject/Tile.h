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
};


class NormalTile : public Tile {
public:
	NormalTile(const int &size, const sf::Vector2f &init_pos, string file_name) : Tile(size, init_pos, file_name) {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;

};

class LavaTile : public Tile {
protected:
	float timer;
	float damageTimer;
public:
	LavaTile(const int &size, const sf::Color &color, const sf::Vector2f &init_pos, const float &damageTimer) : Tile(size, init_pos, "lava") , damageTimer(damageTimer) {
		timer = 0;
	}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;
};

//added 3:12 25/03/2016
class DestructibleTile : public Tile {
protected:
	int tileDurability;
	bool toDelete;
public:
	DestructibleTile(const int &size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, init_pos, "destructible") {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;
};

class TrampolineTile : public Tile {
public:
	TrampolineTile(const int &size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, init_pos, "trampoline") {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;
};

class TarTile : public Tile {
public:
	TarTile(const int &size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, init_pos, "tar") {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;
};
/*
class TeleportationTile : public Tile {
public:
	TeleportationTile(const int &size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, init_pos, "teleport") {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;
};

class TrapTile : public Tile {
public:
	TrapTile(const int &size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, init_pos, "trap") {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;
};

class PermeableTile : public Tile {
public:
	PermeableTile(const int &size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, init_pos, "permeable") {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;
};
*/
