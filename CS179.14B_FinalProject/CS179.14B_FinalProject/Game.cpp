#include <iostream>
#include <algorithm>
#include <string>

#include "EntityManager.h"
#include "TextureLoader.h"
#include "Character.h"
#include "Tile.h"



#define FPS 60.0f
#define SPF sf::seconds(1.0f/FPS)
const auto WINDOW_WIDTH = 800;
const auto WINDOW_HEIGHT = 600;


using namespace std;

TextureLoader tl;
EntityManager em;


void Init() {
	for (int i = 0; i < WINDOW_WIDTH / TILE_SIZE; i++) {
		em.addMapTile(new NormalTile(32, sf::Vector2f(i * TILE_SIZE, WINDOW_HEIGHT - TILE_SIZE), "Art/Tiles/Tar_tile_32.png"));
	}
	em.addPlayer(new War(10,7,2,7,3,10,10,sf::Vector2f(50,400),"Art/Characters/1.png"));
}


int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fight Me");
	sf::Clock clock;
	sf::Time lag = sf::seconds(0);
	Init();

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
		em.logic(SPF.asSeconds());
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
