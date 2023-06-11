/***********************************************************************
 * File: Item.cpp
 * Author: B11115029 白安睿
 * Create Date: 2023/5/28
 * Editor: B11115029 白安睿
 * Update Date: 2023/6/11
 * Description: The implement of Item.h
 * ***********************************************************************/
#include "Item.h"

// Intent: 
// Pre: 
// Post: 
Item::Item()
{
	this->icon = "";
	this->pos.x = 1;
	this->pos.y = 1;
	this->name = "Item";
}

void Item::setPos(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}

void Item::setPos(Position pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

Position Item::getPos()
{
	return this->pos;
}

void Item::setIcon(string& icon)
{
	this->icon = icon;
}

string Item::getIcon()
{
	return this->icon;
}

void Item::setName(string& name)
{
	this->name = name;
}

string Item::getName()
{
	return this->name;
}

void Item::update(Hero& hero)
{

}
