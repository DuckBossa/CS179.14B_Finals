#include "EntityManager.h"

void EntityManager::addPlayer(Character* p) {
	players.push_back(p);
}

void EntityManager::addMapTile(Tile* t) {
	map.push_back(t);
}

void EntityManager::addSObject(SObject* so) {
	sobjects.push_back(so);
}

void EntityManager::handleInput() {
	for (auto e : players) {
		e->handleInput();
	}
}
void EntityManager::handleMouse(int key) {
	for (auto e : players) {
		e->handleMouse(key);
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
	sf::RectangleShape x(sf::Vector2f(2000,2000));
	x.setFillColor(sf::Color::White);
	g.draw(x);
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
	for (auto t : map) {
		for (auto p : players) {
			sf::Rect<float> interX;
			sf::Rect<float> interY;
			bool colX = false;
			bool colY = false;
			bool collided = false;
			//Y
			if (t->bounds().intersects(p->getYColBox(), interY)) {
				if (t->getPosition().y > interY.top) {
					p->move(sf::Vector2f(0, -interY.height));
					p->resetGravity();
				}
				else if (t->getPosition().y <= interY.top) {
					p->move(sf::Vector2f(0, interY.height));
				}
				t->DoSomethingOnCollision(p);
				collided = true;
				colY = true;
			}
			
			//X
			if (t->bounds().intersects(p->getXColBox(), interX)) {
				if (t->getPosition().x > interX.left + interX.width) {
					p->move(sf::Vector2f(-interX.width, 0));
				}
				else if (t->getPosition().x < interX.left) {
					p->move(sf::Vector2f(interX.width, 0));
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

