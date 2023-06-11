/***********************************************************************
 * File: main.h
 * Author: B11115029 白安睿
 * Create Date: 2023/5/28
 * Editor: B11115029 白安睿
 * Update Date: 2023/6/11
 * Description: The main Declare of Useful function and function library and Header.
 * ***********************************************************************/
#include <iostream>
#include <math.h>
#include <ctime>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <random>
#include <stdexcept>
#include <fstream>
#include <windows.h>
#include "Position.h"
#include "Trigger.h"
#include "Hero.h"
#include "Position.h"
#include "Creature.h"
#include "Potion.h"
#include "Sword.h"
#include "Ghost.h"
#include "Rock.h"

// check the move position is valid or not
void isPositionValid(Position& pos);

// check the input is valid or not
void isInputValid(bool key[]);

// print the information
void drawInfo();

// update the program
void update(bool key[]);

// update the key after press the key
void keyUpdate(bool key[]);

// generate the maze
void generateMaze(int x, int y);

// initialized the check board
void setUsed();

// initialize the game board
void setMaze();

// the ghost move
void ghostMove(int row, int col);

// initialize the board information
void setupBoard(int row, int col);

// print board
void printBoard();

// save function
void saveMap();

// load function
void loadMap();