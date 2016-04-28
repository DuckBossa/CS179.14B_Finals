#include "Enemy.h"
#include "Game.h"

using namespace ENEMIES;

void Enemy::render(sf::RenderTarget &g) {
	Entity::render(g);
	g.setView(view);
	sf::RectangleShape health(sf::Vector2f(currhealth*2.5, ENEMIES::HEALTHBAR_HEIGHT));
	health.setPosition(sprt.getPosition() + sf::Vector2f(-bounds().width / 2, -bounds().height / 2 - 5));
	health.setFillColor(sf::Color::Green);
	g.draw(health);
}

void Enemy::update(sf::Vector2f pos, sf::Vector2f vel, Face face) {
	setPos(pos);
	currface = face;
}

ID Enemy::getId() const {
	return id;
}
Face Enemy::getFace() const {
	return currface;
}