#include "Creature.h"

Creature::Creature()
{
	this->pos.x = 2;
	this->pos.y = 2;
	this->icon = 'C';
	this->power = 5;
}

void Creature::setPos(Position pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

void Creature::setPos(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}

void Creature::setIcon(char& icon)
{
	this->icon = icon;
}

Position Creature::getPos()
{
	return this->pos;
}

char Creature::getIcon()
{
	return this->icon;
}