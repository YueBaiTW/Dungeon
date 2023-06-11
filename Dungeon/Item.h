#pragma once
#include "Position.h"
#include "Hero.h"
#include <string>

using namespace std;

class Item
{
protected:
	Position pos;
	string icon;
	string name;
public:
	Item();
	void setPos(int x, int y);
	void setPos(Position pos);
	Position getPos();
	void setIcon(string& icon);
	string getIcon();
	void setName(string& name);
	string getName();
	virtual void update(Hero& hero);
};
