#include <iostream>
#include <algorithm>
#include <string>
#include <SFML/Network.hpp>
#include "EntityManager.h"
#include "TextureLoader.h"
#include "Character.h"
#include "Tile.h"
#include "SObject.h"
#include "Game.h"
#include "GameMessage.h"
#include <boost/asio.hpp>

#define FPS 60.0f
#define SPF sf::seconds(1.0f/FPS)


using namespace std;

TextureLoader tl;
EntityManager* em;
sf::RenderWindow* window;

bool Init(ID player_id) {
	sf::Texture* maptex = tl.getTexture("Art/Maps/sample3.png");
	vector<sf::Vector2f> summon_loc;
	sf::Image map;
	if (map.loadFromFile("Art/Maps/sample3.png")) {
		for (int x = 0; x < map.getSize().x; x++) {
			for (int y = 0; y < map.getSize().y; y++) {
				const sf::Color temp = map.getPixel(x, y);
				int b = (int)temp.b;
				int r = (int)temp.r;
				int g = (int)temp.g;
				if (temp == sf::Color::Black) {
					em->addMapTile(new  NormalTile(TILE_SIZE, sf::Vector2f(x*TILE_SIZE, y*TILE_SIZE), "Art/Tiles/Tar_tile_32.png"));
				}
				else if (g == 150 && b == 150) {/*SObjects Spawn*/
					if (x%2 == 0) { // this is temporary
						// em->addSObject(new ExplodingBarrel(SOBJECT_SIZE, sf::Vector2f(TILE_SIZE*x - SOBJECT_SIZE, TILE_SIZE*y - SOBJECT_SIZE)));
						em->addSObject(new PoisonousBarrel(SOBJECT_SIZE, sf::Vector2f(TILE_SIZE*x - SOBJECT_SIZE, TILE_SIZE*y - SOBJECT_SIZE)));
					} else {
						em->addSObject(new HealBarrel(SOBJECT_SIZE, sf::Vector2f(TILE_SIZE*x - SOBJECT_SIZE, TILE_SIZE*y - SOBJECT_SIZE)));
					}
				}
				else if (temp == sf::Color::Blue) {/*Player Spawn*/
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
		em->setMain(new War(10, 7, 2, 7, 3, 10, summon_loc[0], "Art/Characters/1.png", player_id));
	}
	cout << "Connected. Client id: " << player_id << endl;

	return true;
}



int main() {
	sf::Clock clock;
	sf::Time lag = sf::seconds(0);
	sf::UdpSocket socket;
	string ip;
	cout << "IP Address: ";
	cin >> ip;
	const unsigned short port = 8080;
	ID player_id;
	const unsigned short listen_port = port + 1;


	sf::IpAddress server_address(ip);
	socket.bind(listen_port);
	cout << "Connecting to Server...";
	{
		uint8_t buffer[sizeof(Message) + sizeof(ID)];
		auto msg = reinterpret_cast<Message*>(buffer);
		msg->type = MessageType::Connect;
		msg->size = 0;
		if (socket.send(buffer, sizeof(Message), server_address, port) != sf::Socket::Done) {
			cerr << "Cannot connect to server." << endl;
			system("pause");
			return -1;
		}


		size_t recv_size;
		sf::IpAddress recv_addr;
		unsigned short  recv_port;
		socket.setBlocking(true);
		if (socket.receive(buffer, sizeof(buffer), recv_size, recv_addr, recv_port) != sf::Socket::Done) {
			cerr << "Cannot receive from server." << endl;
			system("pause");
			return -1;
		}
		assert(recv_size == sizeof(buffer));
		assert(msg->type == MessageType::Connect);
		assert(msg->size == sizeof(ID));
		player_id = *reinterpret_cast<ID*>(msg->data);

	}
	cout << "Connected to Server!" << endl;
	socket.setBlocking(false);
	em = new EntityManager(&socket, ip.c_str(), port);
	bool success = Init(player_id);
	


	while (window->isOpen() && success) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					em->handleMouse(1, *window);
				}
				if (event.mouseButton.button == sf::Mouse::Right) {
					em->handleMouse(2, *window);
				}
			}
		}
		//input
		em->handleInput();
		//update entities
		em->update(SPF.asSeconds());
		//collision detection
		em->logic(SPF.asSeconds());
		//render
		window->clear();
		em->render(*window);
		window->display();

		const auto elapsed = clock.getElapsedTime() + lag;
		if (elapsed < SPF) {
			sf::sleep(SPF - elapsed);
			lag = sf::seconds(0);
		}
		else {
			lag = elapsed - SPF;
		}
		clock.restart();
	}
	window->close();
	if (!success) {
		cout << "Failed to connect to server" << endl;
	}
	return 0;
}
