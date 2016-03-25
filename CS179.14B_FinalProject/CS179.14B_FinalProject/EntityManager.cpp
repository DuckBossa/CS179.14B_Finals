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
	for (auto e : map) {
		for (auto c : players) {
			e->resolveColision(c);
		}
	}
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

