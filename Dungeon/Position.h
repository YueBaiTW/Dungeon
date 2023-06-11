/***********************************************************************
 * File: Position.h
 * Author: B11115029 �զw��
 * Create Date: 2023/5/28
 * Editor: B11115029 �զw��
 * Update Date: 2023/6/11
 * Description: The class to store the coordinates of 2D vector;
 * ***********************************************************************/
#pragma once
#include <iostream>

class Position {
public:
	//x and y
	int x, y; 

	//Default Constructor
	Position();
	Position(int x, int y);
	Position(const Position& ref);

	// Operator overloading
	Position operator+(const Position& rhs) const;
	Position& operator=(const Position& rhs);
	Position& operator+=(const Position& rhs);
	Position operator-(const Position& rhs) const;
	Position& operator-=(const Position& rhs);
	Position operator*(int scale) const;
	bool operator==(const Position& rhs) const;
	bool operator!=(const Position& rhs) const;
	friend std::ostream& operator<<(std::ostream& oStream, const Position& pos);
	friend std::istream& operator>>(std::istream& iStream, Position& pos);
};