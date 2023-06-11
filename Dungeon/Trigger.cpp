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

void Trigger::update(Hero& hero)
{
	if (this->pos.x == hero.getPos().x && this->pos.y == hero.getPos().y)
	{
		hero.gainEXP(this->exp);
	}
}

void Trigger::setPos(const Position& pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

void Trigger::setPos(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}

Position Trigger::getPos() const
{
	return this->pos;
}

string Trigger::getIcon() const
{
	return this->icon;
}

int Trigger::getExpAmount() const
{
	return this->exp;
}
