/***********************************************************************
 * File: Creature.h
 * Author: B11115029 �զw��
 * Create Date: 2023/5/28
 * Editor: B11115029 �զw��
 * Update Date: 2023/6/11
 * Description: Declare a Creature class,which has position,icon,name,power,HP and Limit HP.
 * ***********************************************************************/
#pragma once
#include "Position.h"
#include "Hero.h"
#include <string>

using namespace std;

//creature class 
class Creature {
protected:
	// Creature position
	Position pos;

	// Creature icon
	string icon = "��";

	// Original Creature icon
	string orgIcon = "��";

	// Creature name
	string name;

	// Creature Power
	int power;

	// Creature HP
	int hp;

	// Creature Limit HP
	int hpLimit;

public:
	// Default constructor
	Creature();

	// Set position
	void setPos(Position pos);
	void setPos(int x, int y);

	// Set icon
	void setIcon(string& icon);

	// Get position
	Position getPos();

	// Get Icon
	string getIcon();

	// Set Power
	void setPower(int power);

	// Get Power
	int getPower();

	// Set HP
	void setHP(int hp);

	// Get HP
	int getHP();

	// Set Limit HP
	void setHPLimit(int hpLimit);

	// Get Limit HP
	int getHPLimit();

	// Vitual Function,update the move of hero
	virtual void update(Hero& hero);

	// Get the original Icon
	string getOrgIcon();

	// Get the name
	string getName();
};