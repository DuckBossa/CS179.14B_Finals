#include <iostream>
#include <algorithm>
#include <string>

#include "EntityManager.h"
#include "TextureLoader.h"
#include "Character.h"
#include "Tile.h"



#define FPS 60.0f
#define SPF sf::seconds(1.0f/FPS)


namespace GAME {
	const auto WINDOW_WIDTH = 512;
	const auto WINDOW_HEIGHT = 512;
	const auto LAVA_TIMER = 2.5f;
}

using namespace std;

TextureLoader tl;
EntityManager em;


void Init() {
	sf::Texture* maptex = tl.getTexture("Art/Maps/sample.png");
	if (maptex != nullptr) {
		cout << "FOUND" << "\n";
		const sf::Image temps = maptex->copyToImage();
		for (int x = 0; x < temps.getSize().x; x++) {
			for (int y = 0; y < temps.getSize().y; y++) {
				sf::Color temp = temps.getPixel(x, y);
				if (temp == sf::Color::Black) {
					cout << "FOUND BLACK " << x << "," << y <<"\n";
					em.addMapTile(new  NormalTile(TILE_SIZE, sf::Vector2f(x*TILE_SIZE,y*TILE_SIZE), "Art/Tiles/Tar_tile_32.png"));
				}
				else if (temp == sf::Color::White) {
					cout << "FOUND WHITE " << x << "," << y << "\n";
				}
			}
		}
		
	}
	else {
		cout << "ERROR" << "\n";
	}

	em.addPlayer(new War(10,7,2,7,3,10,10,sf::Vector2f(50,50),"Art/Characters/1.png"));
}


int main() {
	sf::RenderWindow window(sf::VideoMode(GAME::WINDOW_WIDTH, GAME::WINDOW_HEIGHT), "Fight Me");
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
