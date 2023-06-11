#include "Potion.h"

Potion::Potion()
{
	this->healPoint = 10;
	this->icon = "¢Þ";
	this->pos.x = 1;
	this->pos.y = 1;
	this->name = "Potion";
}

void Potion::setHealPoint(int healPoint)
{
	this->healPoint = healPoint;
}

int Potion::getHealPoint()
{
	return this->healPoint;
}

void Potion::update(Hero& hero)
{
	if (hero.getPos().x == this->pos.x && hero.getPos().y == this->pos.y)
	{
		hero.heal(this->healPoint);
	}
}
