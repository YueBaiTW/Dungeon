/***********************************************************************
 * File: Rock.cpp
 * Author: B11115029白安睿 B11115046黃健嘉
 * Create Date: 2023/5/28
 * Editor: B11115029白安睿 B11115046黃健嘉
 * Update Date: 2023/6/11
 * Description: The implement of Rock.h
 * ***********************************************************************/
#include "Rock.h"

/**
 * Intent: If the hero and rock are in the same position, update the hero's HP
 * Pre: 
 * Post: Update hero's HP
 * pram: Hero& hero
 */
Rock::Rock()
{
	this->hp = 0;
	this->hpLimit = 0;
	this->icon = "¢à";
	this->name = "Rock";
	this->orgIcon = "¢à";
	this->pos.x = 1;
	this->pos.y = 1;
	this->power = 25;
}

/**
 * Intent: If the hero and rock are in the same position, update the hero's HP
 * Pre: A hero's reference
 * Post: Update hero's HP
 */
void Rock::update(Hero& hero)
{
	//If the hero and rock are in the same position
	if (this->pos.x == hero.getPos().x && this->pos.y == hero.getPos().y)
	{
		hero.getDamage(this->power); //Update the hero's HP
	}

}
