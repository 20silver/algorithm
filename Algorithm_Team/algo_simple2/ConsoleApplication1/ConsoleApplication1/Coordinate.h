#pragma once

#include <cstdlib>

class Coordinate
{
public :
	int row;
	int col;

	Coordinate(int row, int col);
	int hashCode() const;

	int getRow() { return row; }
	int getCol() { return col; }
	void setRow(int r) { this->row = r; }
	void setCol(int c) { this->col = c; }

	bool equals(Coordinate);

    bool operator==(const Coordinate& other) const;
    bool operator<(const Coordinate& other) const;

};

