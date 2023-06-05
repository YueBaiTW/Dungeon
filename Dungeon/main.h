#include <iostream>
#include <math.h>		// pow() and sqrt()
#include <ctime>		// for time loop function
#include <conio.h>		// _getch() <= to read input without enter "ENTER" key
#include <algorithm>	// for max and min function
#include <vector>
#include <random>
#include "Position.h"
#include "Trigger.h"

// Check whether the location is a valid one i.e. not a wall
bool isPositionValid(Position& loc);

// clip algroithm
float clip(float n, float minimun, float maximum);

// Check whether two position is close enough�A�Q�� call-by-reference �N�p��o�쪺��V�^��
bool canSee(Position cPos, Position hPos, Position& pos2);

void generateMaze(int,int);

void setMaze();

void setUsed();

void printBoard();