/***********************************************************************
 * File: Trigger.cpp
 * Author: B11115029白安睿 B11115046黃健嘉
 * Create Date: 2023/5/28
 * Editor: B11115029白安睿 B11115046黃健嘉
 * Update Date: 2023/6/11
 * Description: The implement of Trigger.h
 * ***********************************************************************/
#include "Trigger.h"

 /**
 * Intent: Initialize the Trrigger
 * Pre: None
 * Post: The Trigger will be initialize to specified value
 */
Trigger::Trigger()
{
	this->icon = "¢â";
	this->exp = 10;
}

/**
 * Intent: Set trigger's position, icon and exp
 * Pre: Two integer name x and y
 * Post: The position of x will be set to input x,the position of y will be set to input y, and the icon and exp will be initialized
 */
Trigger::Trigger(int x, int y)
{
	this->icon = "¢â";
	this->exp = 10;
	this->pos.x = x;
	this->pos.y = y;
}

/**
 * Intent: Set trigger
 * Pre: A Trigger class
 * Post: The trigger will be set to input trigger
 */
Trigger::Trigger(const Trigger& ref)
{
	// Set icon, exp and position
	this->icon = ref.icon;
	this->exp = ref.exp;
	this->pos = ref.pos;
}

/**
 * Intent: Update the trigger and hero when the hero move
 * Pre: A hero's reference
 * Post: The hero's exp will be update when they at the same position
 */
void Trigger::update(Hero& hero)
{
	// If the hero and trigger are in the same position
	if (this->pos.x == hero.getPos().x && this->pos.y == hero.getPos().y)
	{
		hero.gainEXP(this->exp); // Update the hero's exp
	}
}

/**
 * Intent: Set the position of trigger
 * Pre: A Position
 * Post: Set the position of trigger
 */
void Trigger::setPos(const Position& pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

/**
 * Intent: Set the position of trigger
 * Pre: Two integers name x and y
 * Post: The position of x will be set to input x,the position of y will be set to input y
 */
void Trigger::setPos(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}

/**
 * Intent: Get the trigger's position
 * Pre: None
 * Post: Return the position of trigger
 */
Position Trigger::getPos() const
{
	return this->pos;
}

/**
 * Intent: Get the trigger's icon
 * Pre: None
 * Post: Return the icon of trigger
 */
string Trigger::getIcon() const
{
	return this->icon;
}

/**
 * Intent: Get the total amount of exp obtained by the hero
 * Pre: None
 * Post: Return the total amount of exp obtained by the hero
 */
int Trigger::getExpAmount() const
{
	return this->exp;
}
