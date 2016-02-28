#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <algorithm>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


#define FPS 60.0f
#define SPF sf::seconds(1.0f/FPS)

const auto TILE_SIZE = 32.0f;
const auto WINDOW_WIDTH = 800;
const auto WINDOW_HEIGHT = 600;
const float GRAV = 9.8f / FPS;

using namespace std;


namespace Keys {
	const auto UP = 0x1A;     	// W
	const auto DOWN = 0x16;		// S
	const auto LEFT = 0x04;  	// A
	const auto RIGHT = 0x07; 	// D
}


bool isKeyDown(int key) {
	auto state = GetAsyncKeyState(MapVirtualKey(key, MAPVK_VSC_TO_VK_EX));
	return state >> 15 != 0;
}

class Entity {

public:
	virtual void update(float dt) = 0;
	virtual void render(sf::RenderTarget &g) = 0;
	virtual sf::Rect<float> bounds() = 0;
	void move(const sf::Vector2f &amount) {
		pos += amount;
	}
	void setPos(const sf::Vector2f &newPos) {
		pos = newPos;
	}
	//virtual sf::Vector2f getPosition() const = 0;
	virtual ~Entity() {}

protected:
	sf::Vector2f pos;
	sf::Vector2i s_size;
	sf::RectangleShape rect;
	string tex;
};




class Tile : public Entity {
protected:

public:
	Tile(float size, const sf::Color &color, const sf::Vector2f &init_pos) {
		rect = sf::RectangleShape(sf::Vector2f(size, size));
		rect.setFillColor(color);
		rect.setPosition(init_pos + sf::Vector2f(size / 2.0f, size / 2.0f));
		rect.setOrigin(sf::Vector2f(size / 2.0f, size / 2.0f));
		pos = init_pos;
	}

	void render(sf::RenderTarget &g) override {
		g.draw(rect);
	}
	void virtual DoSomethingOnCollision(Entity* collided) = 0;


	void resolveColision(Entity* collided) {
		sf::Rect<float> inter;
		if (collided->bounds().intersects(bounds(), inter)) {
			sf::Rect<float> temp_bounds = collided->bounds();
			if (pos.y > inter.top) {
				//getAnimatedSprite().move(0,axis.y*((other.top + other.height) - inter.top));
				collided->move(sf::Vector2f(0, temp_bounds.top + temp_bounds.height - inter.top));
			}
			else if (pos.y <= inter.top) {
				//(0,axis.y*(other.top - (inter.top + inter.height)));
				collided->move(sf::Vector2f(0, temp_bounds.top - (inter.top + inter.height)));
			}

			if (pos.x > inter.left) {
				//getAnimatedSprite().move(axis.x*((other.left + other.width) - inter.left), 0);
				collided->move(sf::Vector2f(temp_bounds.left + temp_bounds.width, 0));
			}
			else if (pos.x <= inter.left) {
				//getAnimatedSprite().move(axis.x*(other.left - (inter.left + inter.width)),0);
				collided->move(sf::Vector2f(temp_bounds.left - (inter.left + inter.width), 0));
			}
			DoSomethingOnCollision(collided);
		}

	}

	sf::Rect<float> bounds() {
		return rect.getGlobalBounds();
	}


};

class NormalTile : public Tile {

public:
	NormalTile(float size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, color, init_pos) {}
	void update(float dt) override {} //Do Nothing
	void DoSomethingOnCollision(Entity* collided) override {}

};

class LavaTile : public Tile {
public:
	LavaTile(float size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, color, init_pos) {}
	void update(float dt) override {}
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



class EntityManager {
public:
	std::vector<Tile*> map;
	std::vector<Character*> players;
	std::vector<Entity*> sobjects;

	void addPlayer(Entity* p) {
		players.push_back(dynamic_cast<Character*>(p));
	}

	void addMapTile(Entity* t) {
		map.push_back(dynamic_cast<Tile*>(t));
	}

	void addSObject(Entity* so) {
		sobjects.push_back(so);
	}

	void handleInput() {
		
	}

	void update(float dt) {

	}

	void logic() {
		for (auto e : map) {
			for (auto c : players) {
				e->resolveColision(c);
			}
		}
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
		em.handleInput();
		//update entities
		em.update(SPF.asSeconds());
		//collision detection
		em.logic();
		//render
		window.clear();
		sf::Texture tex;
		sf::Sprite img;
		if (tex.loadFromFile("sample.png")) {
			img.setTexture(tex);
			window.draw(img);
		}
		//em.render(window);
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
