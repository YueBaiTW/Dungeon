/***********************************************************************
 * File: main.cpp
 * Author: B11115029 白安睿
 * Create Date: 2023/
 * Editor: B11115029 白安睿
 * Update Date: 2023/
 * Description: The main process of the game.
 * ***********************************************************************/
#include "main.h"

using namespace std;

//declare necessary object
Hero hero;
Creature* creature;
Potion* potion;
Sword* sword;
Ghost* ghost;
Rock* rock;

//declare the array to manage the object
vector<Trigger*> triggers;
vector<Creature*> creatures;
vector<Item*> items;

//2D dynamic board
string** board;

//2D dynamic to check the board
int** used;

//the wall and road
const string wall = "\u2588 ";
const string road = "　";

//row and column
int row = 0, col = 0;

//game level
int level = 0;

//time log
const double timeLog = 0.033;

//4 directions
vector<pair<int, int>> dir = {
	{0, 1},   // down
	{0, -1},  // up
	{-1, 0},  // left
	{1, 0}    // right
};

//input enum
enum validInput
{
	EW = 0,
	ES = 1,
	EA = 2,
	ED = 3,
	ESPACE = 4,
	EESC = 5,
	ESave = 6,
	ELoad = 7,
	INVALID,
};


int main()
{
	//initialize time,row and column
	srand(time(NULL));
	row = 19;
	col = 19;

	//set all input to false
	bool gKeyState[validInput::INVALID];
	for (int i = 0; i < validInput::INVALID; i++)
	{
		gKeyState[i] = false;
	}

	//clean screen
	system("CLS");
	cout << "Welcome to Round 1" << endl;
	if (level == 0)
	{
		//initialize game
		setupBoard(row, col);
		printBoard();
	}
	clock_t startT, endT;
	startT = clock();
	endT = clock();

	//when level is 0
	while (!gKeyState[validInput::EESC] && level == 0)
	{
		// Compute the time lap
		double timeFrame = (double)(endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop
		if (timeFrame >= timeLog)
		{
			update(gKeyState);
			startT = clock();
		}

		// Update the key
		keyUpdate(gKeyState);
		endT = clock();

		if (gKeyState[validInput::ESave])
		{
			saveMap();
			gKeyState[validInput::ESave] = false;
		}
		else if (gKeyState[validInput::ELoad]) {
			loadMap();
			gKeyState[validInput::ELoad] = false;
		}
	}

	//if next level,then set the board again,the map is bigger
	if (level == 1)
	{
		row = 21;
		col = 21;
		setupBoard(row, col);
		printBoard();
	}
	//clean the screen and output the messsage
	system("CLS");
	cout << "Welcome to Round 2" << endl;
	cout << "Press Any Key to Start the Round" << endl;

	//when game level is 1
	while (!gKeyState[validInput::EESC] && level == 1)
	{
		// Compute the time lap
		double timeFrame = (double)(endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop
		if (timeFrame >= timeLog)
		{
			update(gKeyState);
			startT = clock();
		}

		// Update the key
		keyUpdate(gKeyState);
		endT = clock();

		if (gKeyState[validInput::ESave])
		{
			saveMap();
			gKeyState[validInput::ESave] = false;
		}
		else if (gKeyState[validInput::ELoad]) {
			loadMap();
			gKeyState[validInput::ELoad] = false;
		}
	}

	//if next level,then set board again,the map is bigger
	if (level == 2)
	{
		row = 25;
		col = 25;
		setupBoard(row, col);
		printBoard();
	}

	//clean the screen and output the messsage
	system("CLS");
	cout << "Welcome to Round 3" << endl;
	cout << "Press Any Key to Start the Round" << endl;

	//if level 2
	while (!gKeyState[validInput::EESC] && level == 2)
	{
		// Compute the time lap
		double timeFrame = (double)(endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop
		if (timeFrame >= timeLog)
		{
			update(gKeyState);
			startT = clock();
		}

		// Update the key
		keyUpdate(gKeyState);
		endT = clock();

		if (gKeyState[validInput::ESave])
		{
			saveMap();
			gKeyState[validInput::ESave] = false;
		}
		else if (gKeyState[validInput::ELoad]) {
			loadMap();
			gKeyState[validInput::ELoad] = false;
		}
	}
	cout << "You Win!" << endl;
	system("pause");
	return 0;
}

// Intent: Update the input key
// Pre: a bool array which include the valid input
// Post: the specified key will be set to true
void keyUpdate(bool key[])
//==================================================================
{
	//if creature's HP is 0,then next level
	if (creatures[0]->getHP() == 0)
	{
		level++;
		return;
	}

	//if hero's HP is 0,then you lose
	else if (hero.getHP() == 0)
	{
		cout << "You Lose..." << endl;
		system("Pause");
	}

	//set all key to false before read the input
	for (int i = 0; i < validInput::INVALID; i++)
	{
		key[i] = false;
	}

	//read the input without enter
	char input = _getch();

	//set the specified key to true
	switch (input)
	{
	case 'w':
		key[validInput::EW] = true;
		break;
	case 's':
		key[validInput::ES] = true;
		break;
	case 'a':
		key[validInput::EA] = true;
		break;
	case 'd':
		key[validInput::ED] = true;
		break;
	case ' ':
		key[validInput::ESPACE] = true;
		break;
	case 27:
		key[validInput::EESC] = true;
		break;
	case '1':
		key[validInput::ESave] = true;
		break;
	case '2':
		key[validInput::ELoad] = true;
		break;
	default:
		break;
	}
}

// Intent: check the move position is valid or not
// Pre: A position reference named pos
// Post: if the position is invalid,then throw the exception message
void isPositionValid(Position& pos)
{
	//you can't step on wall
	if (board[pos.y][pos.x] != road && board[pos.y][pos.x] != "Ｔ" && board[pos.y][pos.x] != "Ｃ" && board[pos.y][pos.x] != "Ｐ" && board[pos.y][pos.x] != "Ｓ" && board[pos.y][pos.x] != "Ｒ")
	{
		throw exception("Invalid Location");
	}
}

// Intent: Check the input key is valid or not
// Pre: a bool array which store the valid key status
// Post: if the key is invalid,then throw the exception message
void isInputValid(bool key[])
{
	//check all valid key
	bool allInvalid = true;
	for (int i = 0; i < validInput::INVALID; i++)
	{
		if (key[i])
		{
			allInvalid = false;
			break;
		}
	}
	//if there aren't any valid key,then throw the message
	if (allInvalid)
	{
		throw exception("Invalid Input");
	}
}

// Intent: Draw the game information
// Pre: None.
// Post: The important information will be printed
void drawInfo()
{
	cout << "--------------------------------------------------------" << endl;
	cout << "The hero is level " << hero.getLevel() << "(" << hero.getExp() << "/" << hero.getMaxExp() << " to level up)" << endl;
	cout << "Hero's HP: " << hero.getHP() << " / " << hero.getHPLimit() << endl;
	cout << "Hero's Attack Power: " << hero.getPower() << endl;
	cout << "--------------------------------------------------------" << endl;
	for (int i = 0; i < creatures.size(); i++)
	{
		cout << creatures[i]->getName() << "'s HP: " << creatures[i]->getHP() << " / " << creatures[i]->getHPLimit() << "\nAttack Damage: " << creatures[i]->getPower() << endl;
	}
	cout << "--------------------------------------------------------" << endl;
	cout << "Use wsad key to move Hero " << hero.getIcon() << endl;
	cout << "Every time you step on a trigger T, the hero gets 10 exp." << endl;
	cout << "Every time you step on a sword S, the hero gets 10 attack power." << endl;
	cout << "Every time you step on a potion P, the hero gets 10 points heal." << endl;
	cout << "(ESC) Exit (1) Save (2) Load" << endl;
	cout << "--------------------------------------------------------" << endl;
}

// Intent: Update the game
// Pre: a bool array which include all valid input
// Post: The whole game will be updated
void update(bool key[])
//==================================================================
{
	// clean the screen
	system("CLS");

	Position delta;

	// check there's input or not
	bool hasInput = false;

	//if key w is been pressed,then set delta
	if (key[validInput::EW])
	{
		delta -= Position(0, 1);
		hasInput = true;
	}
	//if key s is been pressed,then set delta
	else if (key[validInput::ES])
	{
		delta += Position(0, 1);
		hasInput = true;
	}
	//if key a is been pressed,then set delta
	else if (key[validInput::EA])
	{
		delta = delta - Position(1, 0);
		hasInput = true;
	}
	//if key d is been pressed,then set delta
	else if (key[validInput::ED])
	{
		delta = delta + Position(1, 0);
		hasInput = true;
	}

	//check the input valid or not
	else
	{
		try
		{
			isInputValid(key);
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}

	//check the input move is valid or not,if valid,then move the hero
	if (hasInput)
	{
		try
		{
			isPositionValid(delta + hero.getPos());
			board[hero.getPos().y][hero.getPos().x] = road;
			hero.move(delta);
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}

	// update all object
	for (int i = 0; i < triggers.size(); i++) {
		triggers[i]->update(hero);
	}

	for (int i = 0; i < creatures.size(); i++)
	{
		creatures[i]->update(hero);
	}

	for (int i = 0; i < items.size(); i++)
	{
		items[i]->update(hero);
	}

	//print the board
	printBoard();
}

// Intent: Generate a maze. Given the starting coordinates (x, y), this function generates a maze using a recursive algorithm.
// Pre: 'x' and 'y' are valid coordinates within the maze boundaries.
// Post: The maze is generated with paths and walls based on the recursive algorithm.
void generateMaze(int x, int y)
{
	// Set the current position as nothing (path) and mark it as used
	board[y][x] = road;
	used[y][x] = 1;

	// Shuffle the direction array randomly
	random_shuffle(dir.begin(), dir.end());

	// Iterate through the directions
	for (int i = 0; i < 4; i++)
	{
		int newX = 0, newY = 0;
		newX = x + dir[i].first * 2;
		newY = y + dir[i].second * 2;

		// Check if the new position is within the maze boundaries and not used
		if (newX > 0 && newX < row - 1 && newY > 0 && newY < col - 1 && used[newY][newX] == 0)
		{
			int passX = 0, passY = 0;
			passX = x + dir[i].first;
			passY = y + dir[i].second;

			// Set the passed position as nothing (path) and mark it as used
			board[passY][passX] = road;
			used[passY][passX] = 1;

			// Recursively generate the maze from the new position
			generateMaze(newX, newY);
		}
	}
}

// Intent: Initialize the used board
// Pre: None.
// Post: the used board will be set based on row and column
void setUsed()
{
	used = new int* [row];
	for (int i = 0; i < row; i++) {
		used[i] = new int[col];
		for (int j = 0; j < col; j++) {
			//set the edge to 1,represent can't use
			if (i == 0 || i == row - 1 || j == 0 || j == col - 1)
			{
				used[i][j] = 1;
			}
			else
			{
				used[i][j] = 0;
			}
		}
	}
}

// Intent: Dynamic generate the game board
// Pre: None
// Post: the game board will be set based on row and column 
void setMaze()
{
	board = new string * [row];
	for (int i = 0; i < row; i++)
	{
		board[i] = new string[col];
		for (int j = 0; j < col; j++)
		{
			board[i][j] = wall;
		}
	}
}

// Intent: Ghost move.
// Pre: row and column
// Post: The ghost will move randomly on valid lattice
void ghostMove(int row, int col)
{
	//make a valid flag array to check the lattice valid or not
	board[ghost->getPos().y][ghost->getPos().x] = "　";
	vector<vector<bool>> validFlags(row);
	for (int i = 0; i < row; i++) 
	{
		validFlags[i].resize(col);
		for (int j = 0; j < col; j++) 
		{
			validFlags[i][j] = board[i][j] == wall ? false : true;
		}
	}

	//get random position
	auto getRandomPos = [&row, &col]() {
		return Position((int)(rand() % col), (int)(rand() % row));
	};

	//get a valid random position
	auto getValidRandomPos = [&validFlags, &getRandomPos]() 
	{
		while (true) 
		{
			Position pos = getRandomPos();
			if (validFlags[pos.y][pos.x]) 
			{
				return pos;
			}
		}
	};

	//ghost go to new position
	Position gPos = getValidRandomPos();
	validFlags[gPos.y][gPos.x] = false;
	ghost->setPos(gPos);
}

// Intent: Initialize the game board
// Pre: row and column
// Post: The game board will be initialized and put the object on
void setupBoard(int row, int col)
{
	//initialize the necessary array and generate the game board
	setUsed();
	setMaze();
	generateMaze(1, 1);

	//make a valid flag array to check the lattice valid or not
	vector<vector<bool>> validFlags(row);
	for (int i = 0; i < row; i++)
	{
		validFlags[i].resize(col);
		for (int j = 0; j < col; j++) 
		{
			validFlags[i][j] = board[i][j] == wall ? false : true;
		}
	}

	//get a random position
	auto getRandomPos = [&row, &col]() 
	{
		return Position((int)(rand() % col), (int)(rand() % row));
	};

	//get a valid random position
	auto getValidRandomPos = [&validFlags, &getRandomPos]() 
	{
		while (true) 
		{
			Position pos = getRandomPos();
			if (validFlags[pos.y][pos.x]) 
			{
				return pos;
			}
		}
	};

	//clear all object
	triggers.clear();
	creatures.clear();
	items.clear();
	validFlags[hero.getPos().y][hero.getPos().x] = false;

	//put creature randomly
	creature = new Creature();
	Position cPos = getValidRandomPos();
	validFlags[cPos.y][cPos.x] = false;
	creature->setPos(cPos);
	creatures.push_back(creature);

	//put ghost randomly
	ghost = new Ghost();
	Position gPos = getValidRandomPos();
	validFlags[gPos.y][gPos.x] = false;
	ghost->setPos(gPos);
	creatures.push_back(ghost);

	//put rock randomly
	rock = new Rock();
	Position rPos = getValidRandomPos();
	validFlags[rPos.y][rPos.x] = false;
	rock->setPos(rPos);
	creatures.push_back(rock);

	//put triggers randomly
	for (int i = 0; i < 2; i++) {
		Trigger* trigger = new Trigger();
		Position tPos = getValidRandomPos();
		validFlags[tPos.y][tPos.x] = false;
		trigger->setPos(tPos);
		triggers.push_back(trigger);
	}

	//put potion randomly
	potion = new Potion();
	Position pPos = getValidRandomPos();
	validFlags[pPos.y][pPos.x] = false;
	potion->setPos(pPos);
	items.push_back(potion);

	//put sword randomly
	sword = new Sword();
	Position sPos = getValidRandomPos();
	validFlags[sPos.y][sPos.x] = false;
	sword->setPos(sPos);
	items.push_back(sword);
}

// Intent: Print the game board
// Pre: None
// Post: The game board with object will be printed
void printBoard()
{
	//move the ghost
	ghostMove(row, col);

	//set the specified lattice with object's position
	for (int i = 0; i < triggers.size(); i++)
	{
		board[triggers[i]->getPos().y][triggers[i]->getPos().x] = triggers[i]->getIcon();
	}

	for (int i = 0; i < creatures.size(); i++)
	{
		board[creatures[i]->getPos().y][creatures[i]->getPos().x] = creatures[i]->getIcon();
	}

	for (int i = 0; i < items.size(); i++)
	{
		board[items[i]->getPos().y][items[i]->getPos().x] = items[i]->getIcon();
	}
	board[hero.getPos().y][hero.getPos().x] = hero.getIcon();

	//print the board
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	//print the information behind the board
	drawInfo();
}

// Intent: Save the map
// Pre: None
// Post: The information of game will be stored into input file name
void saveMap()
{
	//clean the board
	system("CLS");
	cout << "Input file name for saving or Exit to leave saving." << std::endl;
	cout << "Input: ";
	string input;
	//read the input
	cin >> input;
	if (input.compare("Exit") == 0)
	{
		return;
	}
	ofstream saveFile(input);

	saveFile << row << " " << col << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == wall)
			{
				saveFile << 'W' << " ";
			}
			else
			{
				saveFile << 'R' << " ";
			}
		}
		saveFile << endl;
	}

	saveFile << hero.getPos() << " " << hero.getHP() << " " << hero.getHPLimit() << " " << hero.getLevel() << " " << hero.getExp() << " " << hero.getMaxExp() << " " << hero.getPower() << endl;
	saveFile << creatures.size() << endl;
	for (int i = 0; i < creatures.size(); i++)
	{
		saveFile << creatures[i]->getName() << " " << creatures[i]->getPos() << " " << creatures[i]->getHP() << " " << creatures[i]->getHPLimit() << " " << creatures[i]->getPower() << endl;
	}
	saveFile << triggers.size() << endl;
	for (int i = 0; i < triggers.size(); i++) {
		saveFile << triggers[i]->getPos() << endl;
	}
	saveFile << items.size() << endl;
	for (int i = 0; i < items.size(); i++)
	{
		saveFile << items[i]->getName() << " " << items[i]->getPos() << endl;
	}
	saveFile.close();
}

void loadMap()
{
	system("CLS");
	cout << "Input file name for loading or Exit to leave saving." << std::endl;
	cout << "Input: ";
	string input;
	cin >> input;
	if (input.compare("Exit") == 0)
	{
		return;
	}
	ifstream saveFile;
	saveFile.open(input);
	creatures.clear();
	triggers.clear();
	items.clear();
	saveFile >> row >> col;
	setMaze();
	char readin;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			saveFile >> readin;
			if (readin == 'W')
			{
				board[i][j] = wall;
			}
			else if (readin == 'R')
			{
				board[i][j] = road;
			}
		}
	}
	Position hPos;
	int hHP = 0, hLimitHp = 0, hLevel = 0, hCurrExp = 0, hMaxExp = 0, hPower = 0;
	saveFile >> hPos >> hHP >> hLimitHp >> hLevel >> hCurrExp >> hMaxExp >> hPower;
	hero.setPos(hPos);
	hero.setHP(hHP);
	hero.setHPLimit(hLimitHp);
	hero.setLevel(hLevel);
	hero.setExp(hCurrExp);
	hero.SetMaxExp(hMaxExp);
	hero.setPower(hPower);
	int creatureSize = 0;
	saveFile >> creatureSize;
	for (int i = 0; i < creatureSize; i++)
	{
		string creatureName;
		Position cPos;
		int power = 0, hp = 0, limitHP = 0;
		saveFile >> creatureName;
		if (creatureName == "Creature")
		{
			creature = new Creature();
			saveFile >> cPos;
			creature->setPos(cPos);
			saveFile >> hp >> limitHP >> power;
			creature->setHP(hp);
			creature->setHPLimit(limitHP);
			creature->setPower(power);
			creatures.push_back(creature);

		}
		else if (creatureName == "Ghost")
		{
			ghost = new Ghost();
			saveFile >> cPos;
			ghost->setPos(cPos);
			saveFile >> hp >> limitHP >> power;
			ghost->setHP(hp);
			ghost->setHPLimit(limitHP);
			ghost->setPower(power);
			creatures.push_back(ghost);
		}
		else if (creatureName == "Rock")
		{
			rock = new Rock();
			saveFile >> cPos;
			rock->setPos(cPos);
			saveFile >> hp >> limitHP >> power;
			rock->setHP(hp);
			rock->setHPLimit(limitHP);
			rock->setPower(power);
			creatures.push_back(rock);
		}
	}
	int triggerSize = 0;
	saveFile >> triggerSize;
	for (int i = 0; i < triggerSize; i++)
	{
		Trigger* trigger = new Trigger();
		Position tPos;
		saveFile >> tPos;
		trigger->setPos(tPos);
		triggers.push_back(trigger);
	}
	int itemSize = 0;
	string itemName;
	saveFile >> itemSize;
	for (int i = 0; i < itemSize; i++)
	{
		saveFile >> itemName;
		Position iPos;
		if (itemName == "Sword")
		{
			sword = new Sword();
			saveFile >> iPos;
			sword->setPos(iPos);
			items.push_back(sword);
		}
		if (itemName == "Potion")
		{
			potion = new Potion();
			saveFile >> iPos;
			potion->setPos(iPos);
			items.push_back(potion);
		}
	}
}
