#include "Weapon.h"
#include "Game.h"

void Weapon::update(float dt)
{

}

void Weapon::render(sf::RenderTarget &g)
{
	Entity::render(g);
}

/*
void Weapon::handleMouse(int key, sf::RenderWindow &win) {
	if (key == 1) {
		//Attack();
		if (sf::Mouse::getPosition(win).x > 0 && sf::Mouse::getPosition(win).x <= GAME::WINDOW_WIDTH / 2) {
			cout << "Left Normal" << endl;
		}
		else if (sf::Mouse::getPosition(win).x >  GAME::WINDOW_WIDTH / 2 && sf::Mouse::getPosition(win).x <= GAME::WINDOW_WIDTH) {
			cout << "Right Normal" << endl;
		}
		key = 0;
	}
	if (key == 2) {
		//SAttack();
		if (sf::Mouse::getPosition(win).x > 0 && sf::Mouse::getPosition(win).x <= GAME::WINDOW_WIDTH / 2) {
			cout << "Left Special" << endl;
		}
		else if (sf::Mouse::getPosition(win).x >  GAME::WINDOW_WIDTH / 2 && sf::Mouse::getPosition(win).x <= GAME::WINDOW_WIDTH) {
			cout << "Right Special" << endl;
		}
		key = 0;
	}
}
*/

//void Weapon::fire(sf::Vector2f player_pos) {}