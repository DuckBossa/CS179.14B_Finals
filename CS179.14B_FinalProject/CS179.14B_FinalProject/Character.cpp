#include "Character.h"
#include "Game.h"

using namespace CHARACTERS;

bool Character::isKeyDown(const int &key) {
	auto state = GetAsyncKeyState(MapVirtualKey(key, MAPVK_VSC_TO_VK_EX));
	return state >> 15 != 0;
}

int Character::handleMouse(int key,sf::RenderWindow &win) {
	if (key == 1) {
		//Attack();
		if (sf::Mouse::getPosition(win).x > 0 && sf::Mouse::getPosition(win).x <= GAME::WINDOW_WIDTH/2) {
			cout << "Left Normal" << endl;
			weap->attack(weap->get_left_attack());
			return 1;
		}
		else if (sf::Mouse::getPosition(win).x >  GAME::WINDOW_WIDTH/2 && sf::Mouse::getPosition(win).x <= GAME::WINDOW_WIDTH) {
			cout << "Right Normal" << endl;
			weap->attack(weap->get_right_attack());
			return 2;
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
	return 0;
}

void Character::handleInput(){
	vel.x = 0.0;
	Face temp = Face::NONE;
	if (!isColTile) {
		//cout << "reset" << endl;
		velXMultiplier = 1.0f;
	}
	else {
		//cout << "don't reset" << endl;
	}
	if (isKeyDown(Keys::JUMP) && can_jump) { // jump
		temp = Face::FRONT;
		vel.y = CHARACTERS::JUMP_RATE;
	}
	else if (isKeyDown(Keys::DOWN)) {/*drop down?*/ }
	
	if (isKeyDown(Keys::LEFT)) {
		temp = Face::LEFT;
		vel.x -= CHARACTERS::BASE_SPEED*agi*velXMultiplier;
	}
	if (isKeyDown(Keys::RIGHT)) {
		temp = Face::RIGHT;
		vel.x += CHARACTERS::BASE_SPEED*agi*velXMultiplier;
	}

	if (temp == currface) {
		seq++;
		if (seq > 3) {
			seq = 0;
		}
	} else {
		currface = temp;
		seq = 0;
	}
	
	int frameY = 0;
	
	switch (currface) {
	case UP:
		frameY = 3 * CHARACTERS::SPRITE_HEIGHT;
		break;
	case FRONT:
		frameY = 0;
		break;
	case NONE:
		frameY = 0;
		seq = 0;
		break;
	case LEFT:
		frameY = CHARACTERS::SPRITE_HEIGHT;
		break;
	case RIGHT:
		frameY = 2 * CHARACTERS::SPRITE_HEIGHT;
		break;
	}
	
	sprt.setTextureRect(sf::Rect<int>(seq*CHARACTERS::SPRITE_WIDTH, frameY, CHARACTERS::SPRITE_WIDTH, CHARACTERS::SPRITE_HEIGHT));
}

void Character::update(float dt) {
	if (poison_timer < CHARACTERS::POISON_MAX_TIME) {
		if ((int)poison_timer/CHARACTERS::POISON_FREQ < (int)(poison_timer + dt)/CHARACTERS::POISON_FREQ) {
			takeDamage(CHARACTERS::POISON_DAMAGE);
		}
		poison_timer += dt;
	}
	
	sprt.move(vel*dt);
	
	vel.y += GRAV;
	can_jump = false;
	weap->setPos(sprt.getPosition());
	weap->update(dt);
}

void Character::resetGravity() {
	vel.y = 0;
	can_jump = true;
}

void Character::hit_head() {
	vel.y = 0;
}

void Character::boosted() {
	vel.y += CHARACTERS::BOOST_JUMP;
	can_jump = false;
}

void Character::slow() {
	velXMultiplier = 0.1f;
}

void Character::poison() {
	poison_timer = 0;
}

void Character::takeDamage(int damage){
	currhealth = std::max(0, currhealth - damage);
}
void Character::heal(int heal){
	currhealth = std::min(maxhealth, currhealth + heal);
}

sf::Vector2f Character::getVel() const {
	return vel;
}

void Character::render(sf::RenderTarget &g) {
	Entity::render(g);
	weap->render(g);
	
	sf::RectangleShape health_bar(sf::Vector2f(currhealth*CHARACTERS::HEALTHBAR_WIDTH/maxhealth, CHARACTERS::HEALTHBAR_HEIGHT));
	health_bar.setPosition(sprt.getPosition());
	
	health_bar.move(-CHARACTERS::HEALTHBAR_WIDTH/2, -(health_bar.getGlobalBounds().height + bounds().height)/2 - 5);
	health_bar.setFillColor(sf::Color::Green);
	g.draw(health_bar);
	
	health_bar.setSize(sf::Vector2f((maxhealth - currhealth)*CHARACTERS::HEALTHBAR_WIDTH/maxhealth, CHARACTERS::HEALTHBAR_HEIGHT));
	health_bar.move(currhealth*CHARACTERS::HEALTHBAR_WIDTH/maxhealth, 0);
	health_bar.setFillColor(sf::Color::Red);
	g.draw(health_bar);
}

void Character::update(sf::Vector2f pos, sf::Vector2f vel, Face face) {
	setPos(pos);
	// currface = face;
	this->vel = vel;
}

void Character::setCollision(bool tile) {
	isColTile = tile;
}

ID Character::getId() const{
	return id;
}
playerChar Character::getType() const {
	return type;
}

Face Character::getFace() const {
	return currface;
}

int Character::getHealth() const {
	return currhealth;
}

int Character::get_strength() const {
	return str;
}

Weapon* Character::get_weapon() const {
	return weap;
}

void War::Attack() {}
void War::SAttack() {}

void Famine::Attack() {}
void Famine::SAttack() {}

void Death::Attack() {}
void Death::SAttack() {}

void Pestilence::Attack() {}
void Pestilence::SAttack() {}

void John::Attack() {}
void John::SAttack() {}

void Luke::Attack() {}
void Luke::SAttack() {}

void Matthew::Attack() {}
void Matthew::SAttack() {}

void Mark::Attack() {}
void Mark::SAttack() {}
