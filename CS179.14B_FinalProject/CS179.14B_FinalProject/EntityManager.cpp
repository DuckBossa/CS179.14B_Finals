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
		for (auto p : players) {
			sf::Rect<float> interX;
			sf::Rect<float> interY;
			bool colX = false;
			bool colY = false;
			bool collided = false;
			//Y
			if (t->bounds().intersects(p->getYColBox(), interY)) {
				cout << "enter Y\n";
				cout << p->getPosition().x << " ? " << endl;
				cout << p->getYColBox().left << " ???? " << endl;
				if (t->getPosition().y > interY.top) {
					p->move(sf::Vector2f(0, -interY.height));
					p->resetGravity();
					cout << "1\n";
				}
				else if (t->getPosition().y <= interY.top) {
					p->move(sf::Vector2f(0, interY.height));
					cout << "2\n";
				}
				t->DoSomethingOnCollision(p);
				collided = true;
				colY = true;
			}
			
			//X
			if (t->bounds().intersects(p->getXColBox(), interX)) {
				cout << "enter X\n";
				if (t->getPosition().x > interX.left + interX.width) {
					p->move(sf::Vector2f(-interX.width, 0));
					cout << "3\n";
				}
				else if (t->getPosition().x < interX.left) {
					p->move(sf::Vector2f(interX.width, 0));
					cout << "4\n";
				}
				colX = true;
				if (!collided) {
					t->DoSomethingOnCollision(p);
				}
			}
			p->setCollision(colX, colY);
		}
	}
}

