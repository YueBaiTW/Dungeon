/***********************************************************************
 * File: Rock.h
 * Author: B11115029白安睿 B11115046黃健嘉
 * Create Date: 2023/5/28
 * Editor: B11115029白安睿 B11115046黃健嘉
 * Update Date: 2023/6/11
 * Description: Declare a class named Ghost which inherit from Creature.
 * ***********************************************************************/
#pragma once
#include "Creature.h"

//A Rock class which inherit from Creature
class Rock:public Creature
{
public:
	Rock(); //Default constructor
	void update(Hero& hero) override; //Update the hero's HP
};
