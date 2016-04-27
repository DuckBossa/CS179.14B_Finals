#pragma once
#include "Entities.h"
#include "Weapon.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

const float GRAV = 10.0f; // 9.8f / FPS;

namespace Keys {
	const auto UP = 0x11;     	// W
	const auto DOWN = 0x1F;		// S
	const auto LEFT = 0x1E;  	// A
	const auto RIGHT = 0x20; 	// D
}

namespace CHARACTERS {
	const auto BASE_SPEED = 32.0f;
	const auto SPRITE_WIDTH = 32;
	const auto SPRITE_HEIGHT = 48;
	const auto JUMP_RATE = -300.0f;
	const auto HEALTHBAR_HEIGHT = 5;
	const auto BOOST_JUMP = 2*JUMP_RATE;
	typedef uint32_t ID;
	enum Face {
		UP = 0, FRONT = 1, LEFT = 2, RIGHT = 3, NONE = 4
	};
}

using namespace CHARACTERS;

class Character : public Entity {
private:
	ID id;
	int str, agi, intel, pdef, mdef, currhealth, maxhealth, seq;
	CHARACTERS::Face currface;
	sf::Vector2f vel;
	sf::Vector2f acc;
	sf::View view;
	Weapon* weap;
public:
	Character(const int &str, const int &agi, const int &intel, const int &pdef, const int &mdef,
		int currhealth, int maxhealth, const sf::Vector2f &startPos, string file_name,ID id) : 
		Entity(file_name,sf::Vector2i(CHARACTERS::SPRITE_WIDTH,CHARACTERS::SPRITE_HEIGHT)), str(str), agi(agi), intel(intel), pdef(pdef),
		mdef(mdef), currhealth(currhealth), maxhealth(maxhealth), id(id) {
		sprt.setPosition(startPos);
		sprt.setOrigin(sf::Vector2f(CHARACTERS::SPRITE_WIDTH / 2.0f, CHARACTERS::SPRITE_HEIGHT / 2.0f));
		view.setSize(sf::Vector2f(512, 512));
		view.setCenter(sprt.getPosition());
		currface = CHARACTERS::Face::NONE;
		seq;
		setCollision(false, false);
	}
	virtual void Attack() = 0;
	virtual void SAttack() = 0;
	bool isKeyDown(const int &key);
	void resetGravity();
	void handleInput();
	void handleMouse(int key, sf::RenderWindow &win);
	void takeDamage(int damage);
	void heal(int heal);
	void slow();
	void boosted();
	void update(float dt) override;
	void render(sf::RenderTarget &g) override;
	sf::Vector2f getVel() const;
	sf::Rect<float> getXColBox() const;
	sf::Rect<float> getYColBox() const;
	sf::Rect<float> bounds() const;
};


class War : public Character {
public:
	War(const int &str, const int &agi, const int &intel, const int &pdef, const int &mdef,
		int currhealth, int maxhealth, const sf::Vector2f &startPos, string file_name,ID id) : 
		Character(str, agi, intel, pdef, mdef, currhealth, maxhealth, startPos, file_name,id) {}
	void Attack() override;
	void SAttack() override;
};
