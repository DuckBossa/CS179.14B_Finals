#pragma once
#include "Entities.h"
#include "Weapon.h"
#include "GameMessage.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

const float GRAV = 10.0f; // 9.8f / FPS;

namespace ENEMIES {
	const auto BASE_SPEED = 32.0f;
	const auto SPRITE_WIDTH = 32;
	const auto SPRITE_HEIGHT = 48;
	const auto JUMP_RATE = -300.0f;
	const auto HEALTHBAR_HEIGHT = 5;
	const auto BOOST_JUMP = 2 * JUMP_RATE;
}


class Enemy : public Entity {
private:
	ID id;
	int seq, currhealth;
	Face currface;
	sf::View view;
	Weapon* weap;
public:
	Enemy(const int &str, const int &agi, const int &intel, const int &pdef, const int &mdef,
		int currhealth, int maxhealth, const sf::Vector2f &startPos, string file_name, ID id) :
		Entity(file_name, sf::Vector2i(ENEMIES::SPRITE_WIDTH, ENEMIES::SPRITE_HEIGHT)), id(id) {
		sprt.setPosition(startPos);
		sprt.setOrigin(sf::Vector2f(ENEMIES::SPRITE_WIDTH / 2.0f, ENEMIES::SPRITE_HEIGHT / 2.0f));
		view.setSize(sf::Vector2f(512, 512));
		view.setCenter(sprt.getPosition());
		currface = Face::NONE;
		seq;
		setCollision(false, false);
	}
	void update(sf::Vector2f pos, sf::Vector2f vel, Face face);
	void render(sf::RenderTarget &g) override;
	ID getId() const;
	Face getFace() const;

};