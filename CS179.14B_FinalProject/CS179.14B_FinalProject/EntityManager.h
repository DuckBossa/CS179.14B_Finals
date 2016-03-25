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
	void resolveCollisions(float dt);
};


/*

void Tile::resolveColision(Entity* collided) {
	sf::Rect<float> inter;
	if (bounds().intersects(collided->bounds(), inter)) {
		sf::Rect<float> temp_bounds = collided->bounds();
		bool colX = false;
		bool colY = false;
		if (getPosition().y > inter.top) {
			collided->move(sf::Vector2f(0, -inter.height));
			if (auto e = dynamic_cast<Character*>(collided)) {
				e->resetGravity();
			}
			colY = true;
		}
		else if (getPosition().y <= inter.top) {
			collided->move(sf::Vector2f(0, inter.height));
			colY = true;
		}

		if (colY) {
			//reset inter
		}
		else {
			if (getPosition().x > inter.left + inter.width) {
				collided->move(sf::Vector2f(0,0));
			}
			else if (getPosition().x <= inter.left) {
				collided->move(sf::Vector2f(0, 0));
			}
		}
		collided->setCollision(colX, colY);
		DoSomethingOnCollision(collided);
		

	}
	else {
		collided->setCollision(false, false);
	}

}
*/