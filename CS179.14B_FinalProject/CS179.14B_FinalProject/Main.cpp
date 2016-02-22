#include <SFML\Graphics.hpp>

#include <iostream>
#include <algorithm>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <sstream>
#include <memory>

const auto WINDOW_WIDTH = 800;
const auto WINDOW_HEIGHT = 600;


//Vector2 enhancemens
template<typename T>
sf::T operator%(const Vector2<T> &lhs, const Vector2<T> &rhs) {
	return lhs.x * rhs.y - rhs.x * lhs.y;
}

template<typename T>
T length(const Vector2<T> &rhs) {
	return std::sqrt(rhs.x * rhs.x + rhs.y * rhs.y);
}


class Entity {
public:
	virtual void update() = 0;
	virtual void render(sf::RenderTarget &g) = 0;
	virtual sf::Vector2f getPosition() const = 0;
	virtual ~Entity() {}

protected:
	sf::Vector2f pos;
	sf::Vector2i size;
};



int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fight Me");


	while (window.isOpen())	{
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}
	return 0;
}