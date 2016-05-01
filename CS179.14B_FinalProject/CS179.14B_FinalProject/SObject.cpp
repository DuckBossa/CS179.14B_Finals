#include "SObject.h"
#include "Character.h"

void HealBarrel::update(float dt) {}
void HealBarrel::collide(Entity* collided) {
	--barrelDurability;
	if (auto e = dynamic_cast<Character*>(collided)) {
		e->heal(30);
	}
}

void ExplodingBarrel::update(float dt) {};
void ExplodingBarrel::collide(Entity* collided){
	--barrelDurability;
	if (auto e = dynamic_cast<Character*>(collided)) {
		if(barrelDurability <= 0){
			//EXPLOSION ANIMATION?
			e->takeDamage(1);
		}
	}
}
