#include "Tile.h"
#include "Character.h"


//added 9:12 pm 25/03/2016
void NormalTile::update(float dt) {}
void NormalTile::DoSomethingOnCollision(Entity* collided) {
	//NOTHING? WHAT DOES HAPPEN HERE?
}

void LavaTile::update(float dt) {
	
	if(! timer >= damageTimer){
		timer += dt;
	}
}
void LavaTile::DoSomethingOnCollision(Entity* collided){
	if (auto e = dynamic_cast<Character*>(collided)) {
		if (timer >= damageTimer){
			timer = 0;
			e->takeDamage(5);
			cout << "LOL\n";
		}
	}
}

void DestructibleTile::update(float dt) {}
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
