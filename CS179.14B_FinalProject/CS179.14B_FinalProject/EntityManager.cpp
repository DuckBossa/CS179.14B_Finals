#include "EntityManager.h"

void EntityManager::addPlayer(Character* p) {
	others.push_back(p);
}

void EntityManager::addMapTile(Tile* t) {
	map.push_back(t);
}

void EntityManager::addSObject(SObject* so) {
	sobjects.push_back(so);
}

void EntityManager::setMain(Character* p) {
	main_player = std::move(p);
}

void EntityManager::handleInput() {
	main_player->handleInput();
}
void EntityManager::handleMouse(int key, sf::RenderWindow &g) {
	main_player->handleMouse(key, g);
}
void EntityManager::update(float dt) {
	main_player->update(dt);
	for (auto e : others) {
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
	main_player->render(g);
	for (auto e : map) {
		e->render(g);
	}
	for (auto e : others) {
		e->render(g);
	}
	for (auto e : sobjects) {
		e->render(g);
	}
}


void EntityManager::collide(Tile* t, Character* p) {
	sf::Rect<float> interX;
	sf::Rect<float> interY;
	bool colX = false;
	bool colY = false;
	bool colYTop = false;
	//Y
	if (t->bounds().intersects(p->getYColBox(), interY)) {
		if (t->getPosition().y > interY.top) {
			p->move(sf::Vector2f(0, -interY.height));
			colYTop = true;
			p->resetGravity();
		}
		else if (t->getPosition().y <= interY.top) {
			p->move(sf::Vector2f(0, interY.height));
		}
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
	}

	if (colYTop) {
		static int x = 0;
		t->DoSomethingOnCollision(p);
		cout << x++ << endl;
	}



	p->setCollision(colX, colY);
}

void EntityManager::collide(SObject* t, Character* p) {
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
		//t->DoSomethingOnCollision(p);
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
	}


	p->setCollision(colX, colY);
}

void EntityManager::collide(Weapon* w, Character* c) {

}

void EntityManager::resolveCollisions(float dt) {
	
	for (auto t : map) {
		collide(t, main_player);
		for (auto p : others) {
			collide(t, p);
		}
	}

	for (auto s : sobjects) {
		collide(s, main_player);
		for (auto p : others) {
			collide(s, p);
		}
	}
}

