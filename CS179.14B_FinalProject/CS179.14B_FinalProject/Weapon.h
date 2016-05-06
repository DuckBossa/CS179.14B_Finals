#pragma once
#include "Entities.h"
#include "Game.h"
//#include "Character.h"

class Weapon : public Entity{
private:
	//Character *wielder;
	//int power;

public:
	int power;

	Weapon(string file_name, int weapon_width, int weapon_height) : 
		Entity(file_name, sf::Vector2i(weapon_width, weapon_height)) 
	{
		//wielder = wielder_input;
		sprt.setOrigin(sf::Vector2f(0, weapon_height / 2.0f));
	}
	~Weapon(){}
	//virtual void fire(sf::Vector2f player_pos) = 0;
	void update(float dt) override;
	//void handleMouse(int key, sf::RenderWindow &win);
	void render(sf::RenderTarget &g) override;
	void attack(sf::Vector2f player_pos);
};

class Sword : public Weapon {
private:
	//Character *chara;

public:

	Sword(): Weapon(GAME::WAR_SWORD_FILE, 24, 12)
	{

	}

	//void update(float dt) override;
	// void fire(sf::Vector2f player_pos) override;
};
