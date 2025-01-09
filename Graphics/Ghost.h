#pragma once
#include "Definitions.h"
#include "Cell.h"
#include <queue>
#include <vector>
#include <iostream>

class GhostCompareCells {
private:
    int targetRow, targetCol; // Target position for comparison
public:
    GhostCompareCells(int tRow, int tCol) : targetRow(tRow), targetCol(tCol) {}

    bool operator()(Cell* pn1, Cell* pn2) {
        int h1 = pn1->calculateH(targetRow, targetCol) + pn1->getG();
        int h2 = pn2->calculateH(targetRow, targetCol) + pn2->getG();
        return h1 > h2;
    }
};

class Ghost {
private:
    int row, col, g;
    int color;
    int prev_state;

public:
    Ghost(int c, int r, int clr);
    int getRow() { return row; }
    int getCol() { return col; }
    int getColor() { return color; }
    int getPrev() { return prev_state; }
    void setPrev(int state) { prev_state = state; }
    void setRow(int r) { row = r; }
    void setCol(int c) { col = c; }
    int getG() { return g; }
	bool isGhost(int t) { return t == GHOST_RED || t == GHOST_GREEN || t == GHOST_BLUE; }

    Cell* runAS(int maze[HEIGHT][WIDTH], int targetRow, int targetCol);
    Cell* ASIteration(std::priority_queue<Cell*, std::vector<Cell*>, GhostCompareCells>& grays, int maze[HEIGHT][WIDTH], int targetRow, int targetCol);
    Cell* GhostCheckNeighbor(int row, int col, Cell* pCurrent, int target, int maze[HEIGHT][WIDTH], std::priority_queue<Cell*, std::vector<Cell*>, GhostCompareCells>& grays);
    Cell* GhostRestorePath(Cell* pc);
};
