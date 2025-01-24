#pragma once
#include "Definitions.h"
#include "Cell.h"
#include <queue>
#include <vector>
#include <iostream>
#include <unordered_set>  



class PacmanCompareCells {
private:
    int targetRow, targetCol; // Target position for comparison
public:
    PacmanCompareCells(int tRow, int tCol) : targetRow(tRow), targetCol(tCol) {}

    bool operator()(Cell* pn1, Cell* pn2) {
        int h1 = pn1->calculateH(targetRow, targetCol);
        int h2 = pn2->calculateH(targetRow, targetCol);
        return h1 > h2;
    }
};

class Pacman {
private:
    int row, col;

public:
    Pacman(int c, int r );
    int getRow() { return row; }
    int getCol() { return col; }
    void setRow(int r) { row = r; }
    void setCol(int c) { col = c; }
    bool isTarget(const vector<int>& v, int t);
	double Distance(double x1, double y1, double x2, double y2) { return sqrt(pow(x2 - x1, 2)) + sqrt(pow(y2 - y1, 2)); }
	void cloneMaze(int source[HEIGHT][WIDTH], int target[HEIGHT][WIDTH]) { for (int i = 0; i < HEIGHT; i++) { for (int j = 0; j < WIDTH; j++) { target[i][j] = source[i][j]; } } }

    Cell* runBFS(int maze[HEIGHT][WIDTH], int curRow, int curCol);
    Cell* BFSIteration(queue<Cell*>& grays, int maze[HEIGHT][WIDTH], vector<int> targets, bool forH);
    Cell* PacmanCheckNeighbor(int row, int col, Cell * pCurrent, vector<int> targets, int maze[HEIGHT][WIDTH], queue<Cell*>&grays, bool forH);
    Cell* PacmanRestorePath(Cell* pc);
};
