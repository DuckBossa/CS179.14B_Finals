#pragma once
#include "Character.h"
#include "Tile.h"
#include "TextureLoader.h"
//#include "SObjects"
#include <vector>


class EntityManager {
public:
	std::vector<Tile*> map;
	std::vector<Character*> players;
	std::vector<Entity*> sobjects;
	sf::Sprite bg;

	EntityManager() {
		bg.setTexture(*tl.getTexture("Art/Maps/bg_temp.png"));
	}
	void addPlayer(Character* p);
	void addMapTile(Tile* t);
	void addSObject(Entity* so);
	void handleInput();
	void update(float dt);
	void logic(float dt);
	void render(sf::RenderTarget &g);

};
