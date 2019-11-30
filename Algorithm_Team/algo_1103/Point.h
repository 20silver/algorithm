//
// Created by ÀÌ¿¬°æ on 30/11/2019.
//

#ifndef POINT_H
#define POINT_H


class Point {
public:
	int row;
	int col;

	Point();
	Point(int row, int col);
	int hashCode() const;

	int getRow() { return this->row; }
	int getCol() { return this->col; }
	void setRow(int r) { this->row = r; }
	void setCol(int c) { this->col = c; }
	void set(int r, int c) { this->row = r; this->col = c; }

	bool operator==(const Point& other) const;
};


#endif
