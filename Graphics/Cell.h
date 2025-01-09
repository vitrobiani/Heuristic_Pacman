#pragma once
#include "Definitions.h"
class Cell
{
private:
	int row, col, g;
	Cell* parent;
public:
	Cell();
	Cell(int r, int c, Cell* p);
	int getRow() { return row; }
	int getCol() { return col; }
	int getG() { return g; }
	Cell* getParent() { return parent; }
	double calculateH(int x_target, int y_target);
};

//class CompareCells {
//public:
//	bool operator() (Cell* pn1, Cell* pn2) {
//		if (isAS)
//			return pn1->calculateH() + pn1->getG() > pn2->calculateH() + pn2->getG();
//		else
//			return pn1->calculateH() > pn2->calculateH();
//
//	}
//
//};

