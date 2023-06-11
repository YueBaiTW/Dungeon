/*****************************************************************//**
 * File: Trigger.h
 * Author: B11115029白安睿 B11115046黃健嘉
 * Create Date: 2023/??/??
 * Editor: B11115029白安睿 B11115046黃健嘉
 * Update Date: 2023/06/11
 * Description: Create a class named Trigger
 *********************************************************************/
#pragma once
// Include the required library
#include "Hero.h"
#include "Position.h"
#include <string>

using namespace std;

class Trigger
{
private:
	Position pos; // Save its position
	string icon; // Save its symbol
	int exp; // Save its exp

public:
	Trigger(); // Default constructor
	Trigger(int x, int y); // Give the initial position to build the constructor
	Trigger(const Trigger& ref); // Copy constructor

	void update(Hero& hero); // Update hero's exp
	void setPos(const Position& pos); // Set the Trigger's position
	void setPos(int x, int y); // Another method to set the Trigger's position
	Position getPos() const; // Get the Trigger's position

	// Get Trigger's icon
	string getIcon() const;
	
	// Get the total amount of exp obtained by the hero
	int getExpAmount() const;
};
