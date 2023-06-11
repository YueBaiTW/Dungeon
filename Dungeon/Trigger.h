/***********************************************************************
 * File: Trigger.h
 * Author: B11115029白安睿 B11115046黃健嘉
 * Create Date: 2023/5/28
 * Editor: B11115029白安睿 B11115046黃健嘉
 * Update Date: 2023/6/11
 * Description: Declare a Trigger class,which has position,icon,and exp
 * ***********************************************************************/
#pragma once
 // Include the required library
#include "Hero.h"
#include "Position.h"
#include <string>

using namespace std;

//trigger class
class Trigger
{
private:
	// Trigger position
	Position pos;

	// Trigger icon
	string icon; 

	// Trugger exp
	int exp; 

public:
	// Default constructor
	Trigger(); 

	// Give the initial position to build the constructor
	Trigger(int x, int y); 

	// Copy constructor
	Trigger(const Trigger& ref); 

	// Update hero's exp
	void update(Hero& hero); 

	// Set trigger's position
	void setPos(const Position& pos);
	void setPos(int x, int y);

	// Get the Trigger's position
	Position getPos() const; 

	// Get Trigger's icon
	string getIcon() const;

	// Get the total amount of exp obtained by the hero
	int getExpAmount() const;
};
