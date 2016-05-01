#pragma once
#include "Entities.h"

const auto SOBJECT_SIZE = 16;

class SObject : public Entity {
protected:
	int barrelDurability;
	
public:
	SObject(int size, const sf::Vector2f &init_pos, std::string file_name, int barrelDurability) : Entity(file_name, sf::Vector2i(SOBJECT_SIZE, SOBJECT_SIZE)), barrelDurability(barrelDurability) {
		setPos(init_pos + sf::Vector2f(size / 2.0f, size / 2.0f));
		setOrigin(sf::Vector2f(size / 2.0f, size / 2.0f));
	}
	void virtual collide(Entity* collided) = 0;
	bool is_destroyed() {
		return barrelDurability <= 0;
	}
};

class HealBarrel : public SObject {
public:
	HealBarrel(const int &size, const sf::Vector2f &init_pos, string file_name) : SObject(size, init_pos, file_name, 1) {}
	void update(float dt) override;
	void collide(Entity* collided) override;

};

class ExplodingBarrel : public SObject {
public:
	ExplodingBarrel(const int &size, const sf::Vector2f &init_pos, string file_name) : SObject(size, init_pos, file_name, 10) {}
	void update(float dt) override;
	void collide(Entity* collided) override;
};