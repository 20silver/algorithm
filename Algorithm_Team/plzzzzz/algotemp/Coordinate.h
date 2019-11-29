#pragma once
#include <cstdlib>

class Coordinate
{
public:
	int row;
	int col;

	// ������
	Coordinate() { row = NULL; col = NULL; };
	Coordinate(int row, int col);

	// Coordinate ��ü�� ������ ������ �ؽ��ڵ�
	int hashCode() const { return (row * 1000 + col); };

	// ������ �����ε�
	Coordinate& operator=(Coordinate& coord);
	bool operator==(const Coordinate& coord) const;
	bool operator<(const Coordinate& coord) const;

	// Setter �޼ҵ�� Getter �޼ҵ�
	void set(int r, int c) { row = r; col = c; };
	int getX() { return row; };
	int getY() { return col; };
};