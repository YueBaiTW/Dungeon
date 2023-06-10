#include "Sword.h"

Sword::Sword()
{
	this->icon = "��";
	this->pos.x = 1;
	this->pos.y = 1;
	this->power = 5;
}

int Sword::getPower()
{
	return this->power;
}

void Sword::setPower(int power)
{
	this->power = power;
}

void Sword::update(Hero& hero)
{
	if (hero.getPos().x == this->pos.x && hero.getPos().y == this->pos.y)
	{
		hero.getEquipment(this->power);
	}
}
