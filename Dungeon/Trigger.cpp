/*****************************************************************//**
 * File: Trigger.cpp
 * Author: B11115029白安睿 B11115046黃健嘉
 * Create Date: 2023/??/??
 * Editor: B11115029白安睿 B11115046黃健嘉
 * Update Date: 2023/06/11
 * Description: Implementing the functions in Trigger class
 *********************************************************************/
#include "Trigger.h"

// Default constructor
Trigger::Trigger()
{
	// Initialize icon and exp
	this->icon = "¢â";
	this->exp = 10;
}

// Give the initial position to build the constructor
Trigger::Trigger(int x, int y)
{
	// Initialize icon and exp and set initial position
	this->icon = "¢â";
	this->exp = 10;
	this->pos.x = x;
	this->pos.y = y;
}

// Copy constructor
Trigger::Trigger(const Trigger& ref)
{
	// Set icon, exp and position
	this->icon = ref.icon;
	this->exp = ref.exp;
	this->pos = ref.pos;
}

/**
 * Intent: If the hero and trigger are in the same position, update the hero's exp
 * Pre: 
 * Post: Update hero's exp
 * pram: Hero& hero
 */
void Trigger::update(Hero& hero)
{
	if (this->pos.x == hero.getPos().x && this->pos.y == hero.getPos().y)
	{
		hero.gainEXP(this->exp);
	}
}

/**
 * Intent: Set the position of trigger
 * Pre: 
 * Post: Set the position of trigger
 * pram: const Position& pos
 */
void Trigger::setPos(const Position& pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

/**
 * Intent: Another method to set the position of trigger
 * Pre: 
 * Post: Set the position of trigger
 * pram1: int x
 * pram2: int y
 */
void Trigger::setPos(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}

/**
 * Intent: Get the trigger's position
 * Pre: 
 * Post: Return the trigger's position
 */
Position Trigger::getPos() const
{
	return this->pos;
}

/**
 * Intent: Get the trigger's symbol
 * Pre: 
 * Post: Return the trigger's symbol
 */
string Trigger::getIcon() const
{
	return this->icon;
}

/**
 * Intent: Get the trigger's position
 * Pre: 
 * Post: Return the 
 */
int Trigger::getExpAmount() const
{
	return this->exp;
}
