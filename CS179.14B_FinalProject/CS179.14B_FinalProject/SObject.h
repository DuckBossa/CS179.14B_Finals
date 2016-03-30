#pragma once
#include "Entities.h"

const auto SOBJECT_SIZE = 16;

class SObject : public Entity {
protected:
	bool toDelete;
public:
	SObject(int size, const sf::Vector2f &init_pos, std::string file_name) : Entity(file_name, sf::Vector2i(SOBJECT_SIZE, SOBJECT_SIZE)), toDelete(false) {
		setPos(init_pos + sf::Vector2f(size / 2.0f, size / 2.0f));
		setOrigin(sf::Vector2f(size / 2.0f, size / 2.0f));
	}
	void virtual DoSomethingOnCollision(Entity* collided) = 0;

};


class HealBarrel : public SObject {

public:
	HealBarrel(const int &size, const sf::Vector2f &init_pos, string file_name) : SObject(size, init_pos, file_name) {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;

};

class ExplodingBarrel : public SObject {
protected:
	int barrelDurability = 3;
public:
	ExplodingBarrel(const int &size, const sf::Vector2f &init_pos, string file_name) : SObject(size, init_pos, file_name) {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;
};