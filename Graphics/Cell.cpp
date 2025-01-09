#include "Cell.h"

Cell::Cell()
{
	parent = nullptr;
}

Cell::Cell(int r, int c, Cell* p)
{
	row = r;
	col = c;
	parent = p;
	if (p == nullptr)
		g = 0;
	else
		g = p->getG() + 1;
}

double Cell::calculateH(int x_target, int y_target) {
	return sqrt(pow(x_target - row, 2) + pow(y_target - col, 2));
}

