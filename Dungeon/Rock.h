/*****************************************************************//**
 * File: Rock.h
 * Author: B11115029白安睿 B11115046黃健嘉
 * Create Date: 2023/??/??
 * Editor: B11115029白安睿 B11115046黃健嘉
 * Update Date: 2023/06/11
 * Description: Create a class named Rock and inherit to Creature class
 *********************************************************************/
#pragma once
#include "Creature.h"

class Rock:public Creature
{
public:
	Rock(); //Default constructor
	void update(Hero& hero) override; //Update the hero's HP
};
