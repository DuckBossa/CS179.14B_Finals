#include <iostream>
#include <algorithm>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


#define FPS 60.0f
#define SPF sf::seconds(1.0f/FPS)

const auto TILE_SIZE = 32.0f;
const auto WINDOW_WIDTH = 800;
const auto WINDOW_HEIGHT = 600;
const float GRAV = 10.0f; // 9.8f / FPS;

using namespace std;

namespace Keys {
	const auto UP = 0x11;     	// W
	const auto DOWN = 0x1F;		// S
	const auto LEFT = 0x1E;  	// A
	const auto RIGHT = 0x20; 	// D
}

namespace CHARACTERS {
	const auto BASE_SPEED = 8.0f;
	const auto SPRITE_WIDTH = 32;
	const auto SPRITE_HEIGHT = 48;
	const auto JUMP_RATE = -200.0f;
}


class TextureLoader {
protected:
	map<string, sf::Texture*> textures;
public:
	TextureLoader() {}
	~TextureLoader() {
		map<string, sf::Texture*>::iterator itr = textures.begin();
		delete itr->second;
		textures.erase(itr);
	}

	sf::Texture* getTexture(string n) {
		sf::Texture* temp = NULL;
		map<string, sf::Texture*>::const_iterator results = textures.find(n);
		if (results != textures.end()) {
			temp = results->second;
		}
		else {
			temp = new sf::Texture();
			if (!temp->loadFromFile(n))
				cout << "SFML could not find texture. Check Path.";
			temp->setSmooth(true);
			textures.insert(pair<string, sf::Texture*>(n, temp));
			return temp;
		}
		return temp;
	}
}tl;




class Tile : public Entity {
protected:

public:
	Tile(float size,const sf::Vector2f &init_pos, string file_name) : Entity(file_name) {
		setPos(init_pos + sf::Vector2f(size / 2.0f, size / 2.0f));
		setOrigin(sf::Vector2f(size / 2.0f, size / 2.0f));
	}

	void virtual DoSomethingOnCollision(Entity* collided) = 0;


	void resolveColision(Entity* collided) {
		sf::Rect<float> inter;
		if (bounds().intersects(collided->bounds(), inter)) {
			//cout << "collided\n";
			sf::Rect<float> temp_bounds = collided->bounds();
			bool colX = false;
			bool colY = false;
			if (getPosition().y > inter.top) {
				//getAnimatedSprite().move(0,axis.y*((other.top + other.height) - inter.top));
				collided->move(sf::Vector2f(0, - inter.height));
				colY = true;
			}
			else if (getPosition().y <= inter.top) {
				//(0,axis.y*(other.top - (inter.top + inter.height)));
				//cout << "COLLIDED 2\n";
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




};

class NormalTile : public Tile {

public:
	NormalTile(const float &size, const sf::Vector2f &init_pos,string file_name) : Tile(size, init_pos,file_name) {}
	void update(float dt) override {} //Do Nothing
	void DoSomethingOnCollision(Entity* collided) override {}

};

class LavaTile : public Tile {
public:
	LavaTile(float size, const sf::Color &color, const sf::Vector2f &init_pos) : Tile(size, init_pos,"lava") {}
	void update(float dt) override {}
	void DoSomethingOnCollision(Entity* collided) override {}
};



class Character : public Entity {
private:
	enum Face {
		UP, FRONT, LEFT, RIGHT, NONE
	};
	
	int str, agi, intel, pdef, mdef, currhealth, maxhealth,seq;
	Face currface;
	sf::Vector2f vel;
	sf::Vector2f acc;

public:

	Character(const int &str, const int &agi, const int &intel, const int &pdef, const int &mdef,
		int currhealth, int maxhealth,const sf::Vector2f &startPos, string file_name) : Entity(file_name), str(str), agi(agi), intel(intel), pdef(pdef),
		mdef(mdef), currhealth(currhealth), maxhealth(maxhealth) {
		sprt.setPosition(startPos);
		sprt.setOrigin(sf::Vector2f(CHARACTERS::SPRITE_WIDTH/2.0f,CHARACTERS::SPRITE_HEIGHT/2.0f));
		currface = Face::NONE;
		seq;
	}

	virtual void Attack() = 0;
	virtual void SAttack() = 0;

	bool isKeyDown(const int &key) {
		auto state = GetAsyncKeyState(MapVirtualKey(key, MAPVK_VSC_TO_VK_EX));
		return state >> 15 != 0;
	}


	/*
		public void move(int dir){
		if(!attacking){
			if(dir == Movement.UP.getCode()){
				y-=vy;
			}
			else if(dir == Movement.DOWN.getCode()){
				y+=vy;
			}
			else if(dir == Movement.LEFT.getCode()){
				x-= vx;
			}
			else if(dir == Movement.RIGHT.getCode()){
				x+= vx;
			}
			else if(dir == Movement.ATTACK.getCode()){
				attacking = true;
				seq = 0;
				updateRectangle();
				return;
			}
			if(dir == face){
				seq++;
				if(seq > 3)
					seq = 0;
			}
			else{
				seq = 0;
				face = dir;
			}
		}
		else{
			seq++;
			if(seq > GameWindow.ATTACK_FRAMES){
				seq = 0;
				attacking = false;
			}
		}
		updateRectangle();
	}
	*/



	void handleInput() {
		vel.x = 0.0;
		Face temp =  Face::NONE;
		if (isKeyDown(Keys::UP)) {/*jump*/
			temp = Face::FRONT;
			vel.y = CHARACTERS::JUMP_RATE;
		} 
		else if (isKeyDown(Keys::DOWN)) {/*drop down?*/}
		if (isKeyDown(Keys::LEFT)) {
			temp = Face::LEFT;
			cout << "LEFT";
			vel.x = -CHARACTERS::BASE_SPEED * agi;
		}
		else if (isKeyDown(Keys::RIGHT)) {
			temp = Face::RIGHT;
			cout << "RIGHT";
			vel.x = CHARACTERS::BASE_SPEED * agi;
		}

		if (temp == currface) {
			seq++;
			if (seq > 3) {
				seq = 0;
			}
		}
		else {
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
		sprt.setTextureRect(sf::Rect<int>(seq*CHARACTERS::SPRITE_WIDTH,frameY,CHARACTERS::SPRITE_WIDTH,CHARACTERS::SPRITE_HEIGHT));
	}

	void update(float dt) override {
		if (!isColliding[1]) {
			vel.y += GRAV;
		}
		else {
			vel.y = 0;
		}
		sprt.setPosition(sprt.getPosition() + vel*dt);
	}

	

};

class War : public Character {
public:
	War(const int &str, const int &agi, const int &intel, const int &pdef, const int &mdef,
		int currhealth, int maxhealth,const sf::Vector2f &startPos, string file_name) : Character(str,agi,intel,pdef,mdef,currhealth,maxhealth,startPos,file_name) {

	}
	void Attack() override {}
	void SAttack() override {}
};

class EntityManager {
public:
	std::vector<Tile*> map;
	std::vector<Character*> players;
	std::vector<Entity*> sobjects;
	sf::Sprite bg;

	EntityManager() {
		bg.setTexture(*tl.getTexture("Art/Maps/bg_temp.png"));
	}

	void addPlayer(Entity* p) {
		players.push_back(dynamic_cast<Character*>(p));
	}

	void addMapTile(Entity* t) {
		map.push_back(dynamic_cast<Tile*>(t));
	}

	void addSObject(Entity* so) {
		sobjects.push_back(so);
	}

	void handleInput() {
		for (auto e : players) {
			e->handleInput();
		}
	}
	void update(float dt) {
		for (auto e : players) {
			e->update(dt);
		}
		for (auto e : map) {
			e->update(dt);
		}

		for (auto e : sobjects) {
			e->update(dt);
		}
	}

	void logic() {
		for (auto e : map) {
			for (auto c : players) {
				e->resolveColision(c);
			}
		}
	}

	void render(sf::RenderTarget &g) {
		g.draw(bg);
		for (auto e : map) {
			e->render(g);
		}
		for (auto e : players) {
			e->render(g);
		}
		for (auto e : sobjects) {
			e->render(g);
		}
	}

}em;

void Init() {
	for (int i = 0; i < WINDOW_WIDTH / TILE_SIZE; i++) {
		em.addMapTile(new NormalTile(TILE_SIZE, sf::Vector2f(i * TILE_SIZE, WINDOW_HEIGHT - TILE_SIZE), "Art/Tiles/Tar_tile_32.png"));
	}
	em.addPlayer(new War(10,7,2,7,3,10,10,sf::Vector2f(50,400),"Art/Characters/1.png"));
}


int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fight Me");
	sf::Clock clock;
	sf::Time lag = sf::seconds(0);
	Init();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//input
		em.handleInput();
		//update entities
		em.update(SPF.asSeconds());
		//collision detection
		em.logic();
		//render
		window.clear();
		em.render(window);
		window.display();

		const auto elapsed = clock.getElapsedTime() + lag;
		if (elapsed < SPF) {
			sf::sleep(SPF-elapsed);
			lag = sf::seconds(0);
		}
		else {
			lag = elapsed - SPF;
		}
		clock.restart();
	}
	return 0;
}
