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
protected:
	float timer = 0;
public:
	LavaTile(const int &size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, init_pos, "lava") {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;
};

class DestructibleTile : public Tile {
protected: 
	int tileDurability = 2;
	bool toDelete = false;
public:
	DestrucTile(const int &size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, init_pos, "destructible") {}
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