#pragma once
#include "Character.h"
#include "Weapon.h"
#include "Tile.h"
#include "TextureLoader.h"
#include "SObject.h"
#include "boost/asio.hpp"
#include <vector>


class EntityManager {
public:
	std::vector<Tile*> map;
	Character* main_player;
	std::vector<Character*> others;
	std::vector<SObject*> sobjects;
	sf::Sprite bg;

	EntityManager() {
		bg.setTexture(*tl.getTexture("Art/Maps/bg_temp.png"));
	}
	void addPlayer(Character* p);
	void setMain(Character* p);
	void addMapTile(Tile* t);
	void addSObject(SObject* so);
	void handleInput();
	void handleMouse(int key, sf::RenderWindow &g);
	void update(float dt);
	void logic(float dt);
	void render(sf::RenderTarget &g);
	void resolveCollisions(float dt);
	void collide(Tile* t, Character* p);
	void collide(SObject* t, Character* p);
	void collide(Weapon* w, Character* p);
};


