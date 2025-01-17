#include "Ghost.h"

Ghost::Ghost(int c, int r, int clr) {
    row = r;
    col = c;
    color = clr;
    g = 0;
    prev_state = COIN;
}

Cell* Ghost::runAS(int maze[HEIGHT][WIDTH], int targetRow, int targetCol) {
    GhostCompareCells comparator(targetRow, targetCol);
    priority_queue<Cell*, vector<Cell*>, GhostCompareCells> grays(comparator);
    grays.push(new Cell(getRow(), getCol(), nullptr));

    Cell* to_go_to = nullptr;
    try {
		while (!to_go_to) {
			to_go_to = ASIteration(grays, maze, targetRow, targetCol);
		}
    } catch (GameOver& e) {
        printf("Game over!");
        return to_go_to;
    }
    return to_go_to;
}

Cell* Ghost::ASIteration(std::priority_queue<Cell*, std::vector<Cell*>, GhostCompareCells>& grays, int maze[HEIGHT][WIDTH], int targetRow, int targetCol) {
    if (grays.empty()) {
        throw GameOver("");
        return nullptr;
    }

    Cell* pCurrent = grays.top();
    grays.pop();

    int row = pCurrent->getRow();
    int col = pCurrent->getCol();
    int target = PACMAN;

    if (maze[row][col] != START) {
        maze[row][col] = BLACK;
    }

    Cell* go_on = nullptr;
    // Check neighbors
    if (maze[row + 1][col] == SPACE || maze[row + 1][col] == COIN || maze[row + 1][col] == target || isGhost(maze[row + 1][col]))
        go_on = GhostCheckNeighbor(row + 1, col, pCurrent, target, maze, grays);
    if (!go_on && (maze[row - 1][col] == SPACE || maze[row - 1][col] == COIN || maze[row - 1][col] == target || isGhost(maze[row - 1][col])))
        go_on = GhostCheckNeighbor(row - 1, col, pCurrent, target, maze, grays);                                
    if (!go_on && (maze[row][col - 1] == SPACE || maze[row][col - 1] == COIN || maze[row][col - 1] == target || isGhost(maze[row][col - 1])))
        go_on = GhostCheckNeighbor(row, col - 1, pCurrent, target, maze, grays);                               
    if (!go_on && (maze[row][col + 1] == SPACE || maze[row][col + 1] == COIN || maze[row][col + 1] == target || isGhost(maze[row][col + 1])))
        go_on = GhostCheckNeighbor(row, col + 1, pCurrent, target, maze, grays);

    return go_on;
}

Cell* Ghost::GhostCheckNeighbor(int row, int col, Cell* pCurrent, int target, int maze[HEIGHT][WIDTH], std::priority_queue<Cell*, std::vector<Cell*>, GhostCompareCells>& grays) {
    if (maze[row][col] == target) {
        return GhostRestorePath(pCurrent);
    }

    if (maze[row][col] == SPACE || maze[row][col] == COIN || isGhost(maze[row][col])) {
        Cell* pc = new Cell(row, col, pCurrent);
        maze[row][col] = GRAY;
        grays.push(pc);
    }
    return nullptr;
}

Cell* Ghost::GhostRestorePath(Cell* pc) {
    while (pc->getParent() && pc->getParent()->getParent() != nullptr) {
        pc = pc->getParent();
    }
    return pc; // Return the next step
}