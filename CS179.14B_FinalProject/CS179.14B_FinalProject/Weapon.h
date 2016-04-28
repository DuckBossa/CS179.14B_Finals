#pragma once
#include "Entities.h"
class Weapon : public Entity{

public:
	Weapon(string file_name, int weapon_width, int weapon_height) : Entity(file_name, sf::Vector2i(weapon_width, weapon_height)){}
	~Weapon(){}
	virtual void fire(sf::Vector2f player_pos) = 0;
	void update(float dt) override;
	int power;
};

class Sword : public Weapon {
	void update(float dt) override;
	void fire(sf::Vector2f player_pos) override;
};