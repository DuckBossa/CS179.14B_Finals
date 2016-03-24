#include "Tile.h"

void Tile::resolveColision(Entity* collided) {
	sf::Rect<float> inter;
	if (bounds().intersects(collided->bounds(), inter)) {
		sf::Rect<float> temp_bounds = collided->bounds();
		bool colX = false;
		bool colY = false;
		if (getPosition().y > inter.top) {
			collided->move(sf::Vector2f(0, -inter.height));
			colY = true;
		}
		else if (getPosition().y <= inter.top) {
			collided->move(sf::Vector2f(0, inter.height));
			colY = true;
		}
		/*
		if (getPosition().x > inter.left) {
		//getAnimatedSprite().move(axis.x*((other.left + other.width) - inter.left), 0);
		cout << "COLLIDED 3\n";
		collided->move(sf::Vector2f(temp_bounds.left + temp_bounds.width, 0));
		colX = true;
		}
		else if (getPosition().x <= inter.left) {
		//getAnimatedSprite().move(axis.x*(other.left - (inter.left + inter.width)),0);
		cout << "COLLIDED 4\n";
		collided->move(sf::Vector2f(temp_bounds.left - (inter.left + inter.width), 0));
		}
		collided->setCollision(colX, colY);
		DoSomethingOnCollision(collided);
		*/

	}
	else {
		collided->setCollision(false, false);
	}

}


class NormalTile : public Tile {

public:
	NormalTile(const float &size, const sf::Vector2f &init_pos, string file_name) : Tile(size, init_pos, file_name) {}
	void update(float dt) override {} //Do Nothing
	void DoSomethingOnCollision(Entity* collided) override {}

};

class LavaTile : public Tile {
public:
	LavaTile(float size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, init_pos, "lava") {}
	void update(float dt) override {}
	void DoSomethingOnCollision(Entity* collided) override {}
};
