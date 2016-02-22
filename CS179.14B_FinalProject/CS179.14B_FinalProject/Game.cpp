#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <algorithm>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


#define FPS 60.0
#define SPF sf::seconds(1.0/FPS)

const auto TILE_SIZE = 32.0f;
const auto WINDOW_WIDTH = 800;
const auto WINDOW_HEIGHT = 600;

using namespace std;



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

std::vector<Entity*> entities;

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


class Character : public Entity {
private:
	int str, agi, intel, pdef, mdef, currhealth, maxhealth;
	sf::Vector2f vel;
	sf::Vector2f acc;
public:
	virtual void Attack() = 0;
	virtual void SAttack() = 0;
};




int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fight Me");
	sf::Clock clock;
	sf::Time lag = sf::seconds(0);
	for (int i = 0; i < 800 / TILE_SIZE; i++) {
		entities.push_back(new NormalTile(TILE_SIZE,sf::Color::Magenta,sf::Vector2f(i * TILE_SIZE,WINDOW_HEIGHT - TILE_SIZE)));
	}


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//input

		//update entities
		for (const auto e : entities)
			e->update();
		//collision detection

		//render


		window.clear();
		for (const auto e : entities)
			e->render(window);
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