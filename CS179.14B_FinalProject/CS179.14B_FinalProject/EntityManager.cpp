#include "EntityManager.h"
#include "GameMessage.h"
#include <cassert>
#include <algorithm>
void EntityManager::addPlayer(Character* p) {
	other_players.push_back(p);
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
	{
		sf::Packet packet;
		sf::IpAddress remote_address;
		unsigned short remote_port;
		if (socket->receive(packet, remote_address, remote_port) == sf::Socket::Done) {
			assert(packet.getDataSize() >= sizeof(Message));
			auto msg = reinterpret_cast<const Message*>(packet.getData());
			switch (msg->type) {
			case MessageType::Status: {
				auto pos_data = reinterpret_cast<const StatusMessage*>(msg->data);
				auto it = std::find_if(other_players.begin(), other_players.end(), [pos_data](const Character *p) {
					return p->getId() == pos_data->id;
				});
				if (it == other_players.end()) {
					other_players.emplace_back(new War(10, 7, 2, 7, 3, 10, 10, sf::Vector2f(pos_data->stat.px,pos_data->stat.py), "Art/Characters/1.png", pos_data->id));
				}
				else {
					it[0]->update(sf::Vector2f(pos_data->stat.px, pos_data->stat.py), sf::Vector2f(pos_data->stat.vx, pos_data->stat.vy),pos_data->stat.face);
				}
				break;
			}
			}
		}

	}

	main_player->update(dt);
	for (auto e : other_players) {
		e->update(dt);
	}
	for (auto e : map) {
		e->update(dt);
	}
	for (auto e : sobjects) {
		e->update(dt);
	}

	{
		uint8_t buffer[sizeof(Message) + sizeof(StatusMessage)];
		auto msg = reinterpret_cast<Message*>(buffer);
		msg->type = MessageType::Status;
		msg->size = sizeof(StatusMessage);
		auto sm = reinterpret_cast<StatusMessage*>(msg->data);
		sm->stat.px = main_player->getPosition().x;
		sm->stat.py = main_player->getPosition().y;
		sm->stat.vx = main_player->getVel().x;
		sm->stat.vy = main_player->getVel().y;
		sm->stat.face = main_player->getFace();
		sm->id = main_player->getId();
		sm->stat.hp = main_player->getHealth();
		sm->order = -1; //CHANGE THIS
		if (socket->send(buffer, sizeof(buffer), address, port) == !sf::Socket::Done) {
			cout << "Not sending data" << endl;
		}
		else {
			cout << "sent success!" << endl;
		}
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
	for (auto e : other_players) {
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
		t->DoSomethingOnCollision(p);
	}



	p->setCollision(colX, colY);
}

bool EntityManager::collide(SObject* t, Character* p) {
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
	return collided;
}

void EntityManager::collide(Weapon* w, Character* c) {

}

void EntityManager::resolveCollisions(float dt) {
	
	for (auto t : map) {
		collide(t, main_player);
		for (auto p : other_players) {
			collide(t, p);
		}
	}

	for (int i = 0; i < sobjects.size(); ++i) {
		if (collide(sobjects[i], main_player)) {
			sobjects.erase(sobjects.begin() + i);
			--i;
		}
		for (auto p : other_players) {
			collide(sobjects[i], p);
		}
		
	}
	
	/* for (auto s : sobjects) {
		if (collide(s, main_player)) {
			std::cout << "Colliding" << std::endl;
		}
		for (auto p : other_players) {
			collide(s, p);
		}
	} */
}
