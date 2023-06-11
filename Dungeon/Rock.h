/***********************************************************************
 * File: Rock.h
 * Author: B11115029白安睿 B11115046黃健嘉
 * Create Date: 2023/5/28
 * Editor: B11115029白安睿 B11115046黃健嘉
 * Update Date: 2023/6/11
 * Description: Declare a Rock class inheritance to creature,which has position,icon,
 * ***********************************************************************/
#pragma once
#include "Creature.h"

class Rock:public Creature
{
public:
	Rock(); //Default constructor
	void update(Hero& hero) override; //Update the hero's HP
};
