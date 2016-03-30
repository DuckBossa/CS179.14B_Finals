#pragma once
#include "Entities.h"
class Weapon : public Entity
{


public:

	//sf::Vector2i &texPosSize,const sf::Vector2i &initPosTex = sf::Vector2i(0,0)
	Weapon(string file_name, int weapon_width, int weapon_height) : Entity(file_name, sf::Vector2i(weapon_width, weapon_height))
	{

	}

	void fire(sf::Vector2f player_pos);
};