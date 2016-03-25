#include "Tile.h"
#include "Character.h"
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
		
		if (auto e = dynamic_cast<Character*>(collided)) {
			e->resetGravity();
			cout << "COLLIDE Y" << endl;
		}
	}
	else {
		collided->setCollision(false, false);
	}

}



//added 9:12 pm 25/03/2016


void NormalTile::update(float dt) {}
void NormalTile::DoSomethingOnCollision(Entity* collided) {
	//NOTHING? WHAT DOES HAPPEN HERE?
}

void LavaTile::update(float dt) {}
void LavaTile::DoSomethingOnCollision(Entity* collided){
	if (auto e = dynamic_cast<Character*>(collided)) {
			e->takeDamage(5);
		}
}

void DestructibleTile::update(float dt) {
}
void DestructibleTile::DoSomethingOnCollision(Entity* collided){
	tileDurability--;
	if(tileDurability <= 0){
		toDelete = true;
	}
}

void TrampolineTile::update(float dt) {}
void TrampolineTile::DoSomethingOnCollision(Entity* collided){
	if (auto e = dynamic_cast<Character*>(collided)) {
			e->boosted();
		}
}

void TarTile::update(float dt) {}
void TarTile::DoSomethingOnCollision(Entity* collided){
	if (auto e = dynamic_cast<Character*>(collided)) {
			e->slow();
	}
}
/*
void TeleportationTile::update(float dt) {}
void TeleportationTile::DoSomethingOnCollision(Entity* collided){}

void TrapTile::update(float dt) {}
void TrapTile::DoSomethingOnCollision(Entity* collided){}

void PermeableTile::update(float dt) {}
void PermeableTile::DoSomethingOnCollision(Entity* collided){}
*/
