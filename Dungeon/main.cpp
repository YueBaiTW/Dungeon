#include "main.h"

using namespace std;

Hero hero;
Creature* creature;
Potion* potion;
Sword* sword;
Ghost* ghost;
Rock* rock;

vector<Trigger*> triggers;
vector<Creature*> creatures;
vector<Item*> items;

string** board;
int** used;

const string wall = "\u2588 ";
const string road = "　";

int row = 0, col = 0;

int level = 0;

const double timeLog = 0.033;

vector<pair<int, int>> dir = {
	{0, 1},   // 下
	{0, -1},  // 上
	{-1, 0},  // 左
	{1, 0}    // 右
};

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
	srand(time(NULL));
	row = 19;
	col = 19;

	bool gKeyState[validInput::INVALID];
	for (int i = 0; i < validInput::INVALID; i++)
	{
		gKeyState[i] = false;
	}
	system("CLS");
	cout << "Welcome to Round 1" << endl;
	if (level == 0)
	{
		setupBoard(row, col);
		printBoard();
	}
	clock_t startT, endT;
	startT = clock();
	endT = clock();

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
	if (level == 1)
	{
		row = 21;
		col = 21;
		setupBoard(row, col);
		printBoard();
	}
	system("CLS");
	cout << "Welcome to Round 2" << endl;
	cout << "Press Any Key to Start the Round" << endl;
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

		//if (gKeyState[validInput::ESave])
		//{
		//	saveMap();
		//	gKeyState[validInput::ESave] = false;
		//}
		//else if (gKeyState[validInput::ELoad]) {
		//	loadMap();
		//	gKeyState[validInput::ELoad] = false;
		//}
	}
	if (level == 2)
	{
		row = 25;
		col = 25;
		setupBoard(row, col);
		printBoard();
	}
	system("CLS");
	cout << "Welcome to Round 3" << endl;
	cout << "Press Any Key to Start the Round" << endl;
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

		//if (gKeyState[validInput::ESave])
		//{
		//	saveMap();
		//	gKeyState[validInput::ESave] = false;
		//}
		//else if (gKeyState[validInput::ELoad]) {
		//	loadMap();
		//	gKeyState[validInput::ELoad] = false;
		//}
	}
	level++;
	system("pause");
	return 0;
}

void keyUpdate(bool key[])
//==================================================================
{
	if (creatures[0]->getHP() == 0)
	{
		level++;
		return;
	}
	else if (hero.getHP() == 0)
	{
		cout << "You Lose..." << endl;
		system("Pause");
	}
	for (int i = 0; i < validInput::INVALID; i++)
	{
		key[i] = false;
	}
	char input = _getch();
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

void isPositionValid(Position& pos)
{
	if (board[pos.y][pos.x] != road && board[pos.y][pos.x] != "Ｔ" && board[pos.y][pos.x] != "Ｃ" && board[pos.y][pos.x] != "Ｐ" && board[pos.y][pos.x] != "Ｓ" && board[pos.y][pos.x] != "Ｒ")
	{
		throw exception("Invalid Location");
	}
}

void isInputValid(bool key[])
{
	bool allInvalid = true;
	for (int i = 0; i < validInput::INVALID; i++)
	{
		if (key[i])
		{
			allInvalid = false;
			break;
		}
	}
	if (allInvalid)
	{
		throw exception("Invalid Input");
	}
}

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

void update(bool key[])
//==================================================================
{
	// 清除版面
	system("CLS");

	Position delta;

	// 是否有input
	bool hasInput = false;
	if (key[validInput::EW])
	{
		delta -= Position(0, 1);
		hasInput = true;
	}
	else if (key[validInput::ES])
	{
		delta += Position(0, 1);
		hasInput = true;
	}
	else if (key[validInput::EA])
	{
		delta = delta - Position(1, 0);
		hasInput = true;
	}
	else if (key[validInput::ED])
	{
		delta = delta + Position(1, 0);
		hasInput = true;
	}
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

	// Manipulate update of two triggers using while loop

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
	printBoard();
}

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

void ghostMove(int row, int col)
{
	board[ghost->getPos().y][ghost->getPos().x] = "　";
	vector<vector<bool>> validFlags(row);
	for (int i = 0; i < row; i++) {
		validFlags[i].resize(col);
		for (int j = 0; j < col; j++) {
			validFlags[i][j] = board[i][j] == wall ? false : true;
		}
	}

	auto getRandomPos = [&row, &col]() {
		return Position((int)(rand() % col), (int)(rand() % row));
	};

	auto getValidRandomPos = [&validFlags, &getRandomPos]() {
		while (true) {
			Position pos = getRandomPos();
			if (validFlags[pos.y][pos.x]) {
				return pos;
			}
		}
	};

	Position gPos = getValidRandomPos();
	validFlags[gPos.y][gPos.x] = false;
	ghost->setPos(gPos);
}

void setupBoard(int row, int col)
{
	setUsed();
	setMaze();
	generateMaze(1, 1);

	vector<vector<bool>> validFlags(row);
	for (int i = 0; i < row; i++) {
		validFlags[i].resize(col);
		for (int j = 0; j < col; j++) {
			validFlags[i][j] = board[i][j] == wall ? false : true;
		}
	}

	auto getRandomPos = [&row, &col]() {
		return Position((int)(rand() % col), (int)(rand() % row));
	};

	auto getValidRandomPos = [&validFlags, &getRandomPos]() {
		while (true) {
			Position pos = getRandomPos();
			if (validFlags[pos.y][pos.x]) {
				return pos;
			}
		}
	};
	triggers.clear();
	creatures.clear();
	items.clear();
	validFlags[hero.getPos().y][hero.getPos().x] = false;

	creature = new Creature();
	Position cPos = getValidRandomPos();
	validFlags[cPos.y][cPos.x] = false;
	creature->setPos(cPos);
	creatures.push_back(creature);

	ghost = new Ghost();
	Position gPos = getValidRandomPos();
	validFlags[gPos.y][gPos.x] = false;
	ghost->setPos(gPos);
	creatures.push_back(ghost);

	rock = new Rock();
	Position rPos = getValidRandomPos();
	validFlags[rPos.y][rPos.x] = false;
	rock->setPos(rPos);
	creatures.push_back(rock);

	for (int i = 0; i < 2; i++) {
		Trigger* trigger = new Trigger();
		Position tPos = getValidRandomPos();
		validFlags[tPos.y][tPos.x] = false;
		trigger->setPos(tPos);
		triggers.push_back(trigger);
	}

	potion = new Potion();
	Position pPos = getValidRandomPos();
	validFlags[pPos.y][pPos.x] = false;
	potion->setPos(pPos);
	items.push_back(potion);

	sword = new Sword();
	Position sPos = getValidRandomPos();
	validFlags[sPos.y][sPos.x] = false;
	sword->setPos(sPos);
	items.push_back(sword);
}

void printBoard()
{
	ghostMove(row, col);
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

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	drawInfo();
}

void saveMap()
{
	system("CLS");
	cout << "Input file name for saving or Exit to leave saving." << std::endl;
	cout << "Input: ";
	string input;
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
