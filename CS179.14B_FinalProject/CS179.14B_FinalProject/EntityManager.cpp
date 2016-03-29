#include "EntityManager.h"

void EntityManager::addPlayer(Character* p) {
	players.push_back(p);
}

void EntityManager::addMapTile(Tile* t) {
	map.push_back(t);
}

void EntityManager::addSObject(Entity* so) {
	sobjects.push_back(so);
}

void EntityManager::handleInput() {
	for (auto e : players) {
		e->handleInput();
	}
}

void EntityManager::update(float dt) {
	for (auto e : players) {
		e->update(dt);
	}
	for (auto e : map) {
		e->update(dt);
	}
	for (auto e : sobjects) {
		e->update(dt);
	}
}

void EntityManager::logic(float dt) {
	resolveCollisions(dt);
}

void EntityManager::render(sf::RenderTarget &g) {
	g.draw(bg);
	for (auto e : map) {
		e->render(g);
	}
	for (auto e : players) {
		e->render(g);
	}
	for (auto e : sobjects) {
		e->render(g);
	}
}

void EntityManager::resolveCollisions(float dt) {
	// 1. Check velocity of next frame? (advaned collision)
	// 2. Cancel velocities if collide with tile
	// 3. Nudge if colliding
	for (auto t : map) {
		for (auto p : players){
			sf::Rect<float> inter;
			if (t->bounds().intersects(p->bounds(), inter)) {
				bool colX = false;
				bool colY = false;

				if (t->getPosition().y > inter.top) {
					p->move(sf::Vector2f(0,-inter.height));
					p->resetGravity();
					colY = true;
				}
				else if (t->getPosition().y <= inter.top) {
					p->move(sf::Vector2f(0, inter.height));
					colY = true;
				}
				
				if(colY){
					t->bounds().intersects(p->bounds(), inter);
					p->setCollision(colX, colY);
					t->DoSomethingOnCollision(p);
					continue;
				}
				if (t->getPosition().x > inter.left + inter.width && inter.width > 0) {
					p->move(sf::Vector2f(-inter.width,0));
					colX = true;
				}
				else if (t->getPosition().x < inter.left && inter.width > 0) {
					p->move(sf::Vector2f(inter.width,0));
					colX = true;
				}
				p->setCollision(colX, colY);
				t->DoSomethingOnCollision(p);
			}
			else {
				p->setCollision(false, false);
			}
		}
	}
}

