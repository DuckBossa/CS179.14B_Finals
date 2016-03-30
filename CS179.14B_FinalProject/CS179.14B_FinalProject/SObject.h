#pragma once
#include "Entities.h"

const auto SOBJECT_SIZE = 32;

class SObject : public Entity {
protected:
	
public:
	SObject(int size, const sf::Vector2f &init_pos, std::string file_name) : Entity(file_name,sf::Vector2i(SOBJECT_SIZE,SOBJECT_SIZE)) {
		setPos(init_pos + sf::Vector2f(size / 2.0f, size / 2.0f));
		setOrigin(sf::Vector2f(size / 2.0f, size / 2.0f));
	}

	void virtual DoSomethingOnCollision(Entity* collided) = 0;


	void resolveColision(Entity* collided);

};


class HealBarrel : public SObject {
protected:
	bool toDelete = false;
public:
	HealBarrel(const int &size, const sf::Vector2f &init_pos, string file_name) : SObject(size, init_pos, "HealBarrel") {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;

};

class ExplodingBarrel : public SObject {
protected:
	int barrelDurability = 3;
	bool toDelete = false;
public:
	ExplodingBarrel(const int &size, const sf::Color &color, const sf::Vector2f &init_pos) : SObject(size, init_pos, "ExplodingBarrel") {}
	void update(float dt) override;
	void DoSomethingOnCollision(Entity* collided) override;
};