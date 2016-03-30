#include "SObject.h"
#include "Character.h"


void HealBarrel::update(float dt) {}
void HealBarrel::DoSomethingOnCollision(Entity* collided) {
	if (auto e = dynamic_cast<Character*>(collided)) {
		e->heal(30);
		toDelete = true;
	}
	//DISAPPEARS, BUT HOW?
}
void ExplodingBarrel::update(float dt) {}
void ExplodingBarrel::DoSomethingOnCollision(Entity* collided){
	if (auto e = dynamic_cast<Character*>(collided)) {
		barrelDurability--;
		if(barrelDurability <= 0){
			toDelete = true;
			//EXPLOSION ANIMATION?
			e->takeDamage(10);
		}
	}
}
