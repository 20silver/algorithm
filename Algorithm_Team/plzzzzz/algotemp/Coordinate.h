#pragma once
#include <cstdlib>

class Coordinate
{
public:
	int row;
	int col;

	// 생성자
	Coordinate() { row = NULL; col = NULL; };
	Coordinate(int row, int col);

	// Coordinate 객체가 가지는 고유한 해쉬코드
	int hashCode() const { return (row * 1000 + col); };

	// 연산자 오버로딩
	Coordinate& operator=(Coordinate& coord);
	bool operator==(const Coordinate& coord) const;
	bool operator<(const Coordinate& coord) const;

	// Setter 메소드와 Getter 메소드
	void set(int r, int c) { row = r; col = c; };
	int getX() { return row; };
	int getY() { return col; };
};