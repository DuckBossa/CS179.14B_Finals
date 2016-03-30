#include <iostream>
#include <algorithm>
#include <string>

#include "EntityManager.h"
#include "TextureLoader.h"
#include "Character.h"
#include "Tile.h"
#include "SObject.h"



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
sf::RenderWindow* window;

sf::View view1;
void Init() {
	sf::Texture* maptex = tl.getTexture("Art/Maps/sample3.png");
	vector<sf::Vector2f> summon_loc;
	sf::Image map;
	if (map.loadFromFile("Art/Maps/sample3.png")) {
		for (int x = 0; x < map.getSize().x; x++) {
			for (int y = 0; y < map.getSize().y; y++) {
				const sf::Color temp = map.getPixel(x, y);
				if (temp == sf::Color::Black) {
					em.addMapTile(new  NormalTile(TILE_SIZE, sf::Vector2f(x*TILE_SIZE, y*TILE_SIZE), "Art/Tiles/Tar_tile_32.png"));
				}
				else if (temp == sf::Color::Yellow) {/*SObjects Spawn*/

				}
				else if (temp == sf::Color::Blue) {/*Player Spawn*/
					cout << "in\n";
					summon_loc.push_back(sf::Vector2f(x*TILE_SIZE, y * TILE_SIZE));
				}
			}
		}
		window = new sf::RenderWindow(sf::VideoMode(GAME::WINDOW_WIDTH, GAME::WINDOW_HEIGHT), "Fight Me");
	}
	else {
		cout << "ERROR" << "\n";
	}

	if (!summon_loc.empty()) {
		em.addPlayer(new War(10, 7, 2, 7, 3, 10, 10, summon_loc[0], "Art/Characters/1.png"));
	}

	view1.reset(sf::Rect<float>(50, 50, GAME::WINDOW_WIDTH, GAME::WINDOW_HEIGHT));
}



int main() {
	sf::Clock clock;
	sf::Time lag = sf::seconds(0);
	Init();
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					em.handleMouse(1);
				}
				if (event.mouseButton.button == sf::Mouse::Right) {
					em.handleMouse(2);
				}
			}
		}
		//input
		em.handleInput();
		//update entities
		em.update(SPF.asSeconds());
		//collision detection
		em.logic(SPF.asSeconds());
		//render
		window->clear();
		em.render(*window);
		window->display();

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
	window->close();
	return 0;
}
