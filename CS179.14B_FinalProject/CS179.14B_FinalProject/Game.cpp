#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <algorithm>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


#define FPS 60.0
#define SPF sf::seconds(1.0/FPS)

namespace Keys {
	const auto UP = 0x1A;     	// W
	const auto DOWN = 0x16;		// S
	const auto LEFT = 0x04;  	// A
	const auto RIGHT = 0x07; 	// D
}

const auto TILE_SIZE = 32.0f;
const auto WINDOW_WIDTH = 800;
const auto WINDOW_HEIGHT = 600;

using namespace std;

bool isKeyDown(int key) {
	auto state = GetAsyncKeyState(MapVirtualKey(key, MAPVK_VSC_TO_VK_EX));
	return state >> 15 != 0;
}

class Entity {
public:
	virtual void update() = 0;
	virtual void render(sf::RenderTarget &g) = 0;
//	virtual sf::Vector2f getPosition() const = 0;
	virtual ~Entity() {}

protected:
	sf::Vector2f pos;
	sf::Vector2i s_size;
};

class EntityManager {
public:
	std::vector<Entity*> map;
	std::vector<Entity*> players;
	std::vector<Entity*> sobjects;

	void addPlayer(Entity* p) {
		players.push_back(p);
	}

	void addMapTile(Entity* t) {
		map.push_back(t);
	}

	void addSObject(Entity* so) {
		sobjects.push_back(so);
	}


	void update() {
		//
	}

	void logic() {
		//collision
	}

	void render(sf::RenderTarget &g) {
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


}em;


class Tile : public Entity {
protected:
	sf::RectangleShape rect;
public:
	Tile(float size, const sf::Color &color,const sf::Vector2f &init_pos) :rect(sf::Vector2f(size, size)) {
		rect.setFillColor(color);
		rect.setPosition(init_pos);
		pos = init_pos;
	}

	void render(sf::RenderTarget &g) override {
		g.draw(rect);
	}
	void virtual DoSomethingOnCollision(Entity* collided) = 0;
};

class NormalTile : public Tile{

public:
	NormalTile(float size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, color,init_pos) {}
	void update() override {} //Do Nothing
	void DoSomethingOnCollision(Entity* collided) override{}

};

class LavaTile : public Tile {
public:
	LavaTile(float size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, color, init_pos) {}
	void update() override {} //Do Nothing
	void DoSomethingOnCollision(Entity* collided) override {}
};


class Character : public Entity {
private:
	int str, agi, intel, pdef, mdef, currhealth, maxhealth;
	sf::Vector2f vel;
	sf::Vector2f acc;
public:
	virtual void Attack() = 0;
	virtual void SAttack() = 0;
	void handleInput() {
		vel.x = vel.y = 0.0;

		if ( isKeyDown(Keys::UP)) {
			//jump
		} 
		if (isKeyDown(Keys::DOWN)) {
			//drop down?
		}
		if (isKeyDown(Keys::LEFT)) {
			//move left
		}
		if (isKeyDown(Keys::RIGHT)) {
			//move right
		}
	}
};




int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fight Me");
	sf::Clock clock;
	sf::Time lag = sf::seconds(0);
	for (int i = 0; i < WINDOW_WIDTH / TILE_SIZE; i++) {
		em.addMapTile(new NormalTile(TILE_SIZE,sf::Color::Magenta,sf::Vector2f(i * TILE_SIZE,WINDOW_HEIGHT - TILE_SIZE)));
	}


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//input
		character->handleInput();
		//update entities
		em.update();
		//collision detection
		em.logic();
		//render
		window.clear();
		em.render(window);
		window.display();

		const auto elapsed = clock.getElapsedTime() + lag;
		if (elapsed < SPF) {
			sf::sleep(SPF-elapsed);
			lag = sf::seconds(0);
		}
		else {
			lag = elapsed - SPF;
		}
		clock.restart();
	}
	return 0;
}
