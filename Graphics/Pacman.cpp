#include "Pacman.h"
#include<memory>

Pacman::Pacman(int c, int r) {
	row = r;
	col = c;
	g = 0;
}

bool Pacman::isTarget(const vector<int>& v, int t) {
    for (int i = 0; i < v.size(); i++) {
        if (t == v.at(i))
            return true;
    }
    return false;
}


Cell* Pacman::runBFS(int maze[HEIGHT][WIDTH], int curRow, int curCol) {
    int dupMaze[HEIGHT][WIDTH] = {0};
    int dupMaze2[HEIGHT][WIDTH] = {0};
    cloneMaze(maze, dupMaze);
    cloneMaze(maze, dupMaze2);
    queue<Cell*> grays;
    grays.push(new Cell(getRow(), getCol(), nullptr));
    vector<Cell*> ghostCells;

    Cell* to_go_to = nullptr;

    if (curRow == 11 && curCol == 18) {
    }

    int i = 0;
    while (i < BFS_DEPTH && !to_go_to) {
        to_go_to = BFSIteration(grays, maze, ghostTargets);
        i++;
    }
    if (to_go_to == nullptr) {
		queue<Cell*> grays2;
		grays2.push(new Cell(getRow(), getCol(), nullptr));
        vector<int> coins = { COIN };
        while (!to_go_to) {
            to_go_to = BFSIteration(grays2, dupMaze, coins);
        }

        if (curRow == to_go_to->getRow() && curCol == to_go_to->getCol()) {
            if (dupMaze2[curRow + 1][curCol] == COIN) {
                return new Cell(curRow + 1, curCol, nullptr);
            }
            else if (dupMaze2[curRow - 1][curCol] == COIN) {
                return new Cell(curRow - 1, curCol, nullptr);
            }
            else if (dupMaze2[curRow][curCol + 1] == COIN) {
                return new Cell(curRow, curCol + 1, nullptr);
            }
            else if (dupMaze2[curRow][curCol - 1] == COIN) {
                return new Cell(curRow, curCol - 1, nullptr);
            }
        }

        double min = MAX_G;
        double h1 = (maze[curRow + 1][curCol] == WALL) ? MAX_G : Distance(curRow + 1, curCol, to_go_to->getRow(), to_go_to->getCol());
        min = (h1 < min) ? h1 : min;
        double h2 = (maze[curRow - 1][curCol] == WALL) ? MAX_G : Distance(curRow - 1, curCol, to_go_to->getRow(), to_go_to->getCol());
        min = (h2 < min) ? h2 : min;
        double h3 = (maze[curRow][curCol + 1] == WALL) ? MAX_G : Distance(curRow, curCol + 1, to_go_to->getRow(), to_go_to->getCol());
        min = (h3 < min) ? h3 : min;
        double h4 = (maze[curRow][curCol - 1] == WALL) ? MAX_G : Distance(curRow, curCol - 1, to_go_to->getRow(), to_go_to->getCol());
        min = (h4 < min) ? h4 : min;

        if (min == h1) {
            return new Cell(curRow + 1, curCol, nullptr);
        }
        else if (min == h2) {
            return new Cell(curRow - 1, curCol, nullptr);
        }
        else if (min == h3) {
            return new Cell(curRow, curCol + 1, nullptr);
        }
        else if (min == h4) {
            return new Cell(curRow, curCol - 1, nullptr);
        }
    }
    else {
        double max = 0;
        double h1 = (maze[curRow + 1][curCol] == WALL) ? 0 : Distance(curRow + 1, curCol, to_go_to->getRow(), to_go_to->getCol());
        max = (h1 > max) ? h1 : max;
        double h2 = (maze[curRow - 1][curCol] == WALL) ? 0 : Distance(curRow - 1, curCol, to_go_to->getRow(), to_go_to->getCol());
        max = (h2 > max) ? h2 : max;
        double h3 = (maze[curRow][curCol + 1] == WALL) ? 0 : Distance(curRow, curCol + 1, to_go_to->getRow(), to_go_to->getCol());
        max = (h3 > max) ? h3 : max;
        double h4 = (maze[curRow][curCol - 1] == WALL) ? 0 : Distance(curRow, curCol - 1, to_go_to->getRow(), to_go_to->getCol());
        max = (h4 > max) ? h4 : max;

        if (max == 0) {
            return new Cell(curRow, curCol, nullptr);
        }

        if (max == h1) {
            return new Cell(curRow + 1, curCol, nullptr);
        }
        else if (max == h2) {
            return new Cell(curRow - 1, curCol, nullptr);
        }
        else if (max == h3) {
            return new Cell(curRow, curCol + 1, nullptr);
        }
        else if (max == h4) {
            return new Cell(curRow, curCol - 1, nullptr);
        }
    }
    return to_go_to;
}

Cell* Pacman::BFSIteration(queue<Cell*>& grays, int maze[HEIGHT][WIDTH], vector<int> targets) {
    if (grays.empty()) {
        std::cout << "There is no solution. Grays is empty in pacman.\n";
        return nullptr;
    }

    Cell* pCurrent = grays.front();
    grays.pop();

    int row = pCurrent->getRow();
    int col = pCurrent->getCol();

    if (maze[row][col] != START) {
        maze[row][col] = BLACK;
    }

    Cell* go_on = nullptr;
    // Check neighbors
    if (maze[row + 1][col] == SPACE || maze[row + 1][col] == COIN || isTarget(targets, maze[row + 1][col]) ) 
        go_on = PacmanCheckNeighbor(row + 1, col, pCurrent, targets, maze, grays);
    if (!go_on && (maze[row - 1][col] == SPACE || maze[row - 1][col] == COIN || isTarget(targets, maze[row - 1][col])))
        go_on = PacmanCheckNeighbor(row - 1, col, pCurrent, targets, maze, grays);
    if (!go_on && (maze[row][col - 1] == SPACE || maze[row][col - 1] == COIN || isTarget(targets, maze[row][col - 1])))
        go_on = PacmanCheckNeighbor(row, col - 1, pCurrent, targets, maze, grays);
    if (!go_on && (maze[row][col + 1] == SPACE || maze[row][col + 1] == COIN || isTarget(targets, maze[row][col + 1])))
        go_on = PacmanCheckNeighbor(row, col + 1, pCurrent, targets, maze, grays);

    return go_on;
}

Cell* Pacman::PacmanCheckNeighbor(int row, int col, Cell* pCurrent, vector<int> targets, int maze[HEIGHT][WIDTH], queue<Cell*>& grays) {
    if (isTarget(targets, maze[row][col])) {
        return pCurrent;
    }

    if (maze[row][col] == SPACE || maze[row][col] == COIN) {
        Cell* pc = new Cell(row, col, pCurrent);
        maze[row][col] = GRAY;
        grays.push(pc);
    }
    return nullptr;
}

Cell* Pacman::PacmanRestorePath(Cell* pc) {
    while (pc->getParent() && pc->getParent()->getParent() != nullptr) {
        pc = pc->getParent();
    }
    return pc;
}














//#include "Pacman.h"
//#include <memory>
//
//Pacman::Pacman(int c, int r) {
//    row = r;
//    col = c;
//    g = 0;
//}
//
//bool Pacman::isTarget(const vector<int>& v, int t) {
//    for (const auto& val : v) {
//        if (t == val)
//            return true;
//    }
//    return false;
//}
//
//Cell* Pacman::runBFS(int maze[HEIGHT][WIDTH], int curRow, int curCol) {
//    int dupMaze[HEIGHT][WIDTH] = {0};
//    int dupMaze2[HEIGHT][WIDTH] = {0};
//    cloneMaze(maze, dupMaze);
//    cloneMaze(maze, dupMaze2);
//    std::queue<std::unique_ptr<Cell>> grays;
//    grays.push(std::make_unique<Cell>(getRow(), getCol(), nullptr));
//    vector<Cell*> ghostCells;
//
//    //Cell* to_go_to = nullptr;
//	std::unique_ptr<Cell> to_go_to = nullptr;
//
//
//    int i = 0;
//    while (i < BFS_DEPTH && !to_go_to) {
//        to_go_to = BFSIteration(grays, maze, ghostTargets);
//        i++;
//    }
//    if (to_go_to == nullptr) {
//        std::queue<std::unique_ptr<Cell>>().swap(grays);
//        grays.push(std::make_unique<Cell>(getRow(), getCol(), nullptr));
//        vector<int> coins = { COIN };
//        while (!to_go_to) {
//            to_go_to = BFSIteration(grays, dupMaze, coins);
//        }
//
//        if (curRow == to_go_to->getRow() && curCol == to_go_to->getCol()) {
//            if (dupMaze2[curRow + 1][curCol] == COIN) {
//                return new Cell(curRow + 1, curCol, nullptr);
//            }
//            else if (dupMaze2[curRow - 1][curCol] == COIN) {
//                return new Cell(curRow - 1, curCol, nullptr);
//            }
//            else if (dupMaze2[curRow][curCol + 1] == COIN) {
//                return new Cell(curRow, curCol + 1, nullptr);
//            }
//            else if (dupMaze2[curRow][curCol - 1] == COIN) {
//                return new Cell(curRow, curCol - 1, nullptr);
//            }
//        }
//
//        double min = MAX_G;
//        double h1 = (maze[curRow + 1][curCol] == WALL) ? 0 : Distance(curRow + 1, curCol, to_go_to->getRow(), to_go_to->getCol());
//        min = std::min(min, h1);
//        double h2 = (maze[curRow - 1][curCol] == WALL) ? 0 : Distance(curRow - 1, curCol, to_go_to->getRow(), to_go_to->getCol());
//        min = std::min(min, h2);
//        double h3 = (maze[curRow][curCol + 1] == WALL) ? 0 : Distance(curRow, curCol + 1, to_go_to->getRow(), to_go_to->getCol());
//        min = std::min(min, h3);
//        double h4 = (maze[curRow][curCol - 1] == WALL) ? 0 : Distance(curRow, curCol - 1, to_go_to->getRow(), to_go_to->getCol());
//        min = std::min(min, h4);
//
//        if (min == 0) {
//            return new Cell(curRow, curCol, nullptr);
//        }
//
//        if (min == h1) {
//            return new Cell(curRow + 1, curCol, nullptr);
//        }
//        else if (min == h2) {
//            return new Cell(curRow - 1, curCol, nullptr);
//        }
//        else if (min == h3) {
//            return new Cell(curRow, curCol + 1, nullptr);
//        }
//        else if (min == h4) {
//            return new Cell(curRow, curCol - 1, nullptr);
//        }
//    }
//    else {
//        double max = 0;
//        double h1 = (maze[curRow + 1][curCol] == WALL) ? 0 : Distance(curRow + 1, curCol, to_go_to->getRow(), to_go_to->getCol());
//        max = std::max(max, h1);
//        double h2 = (maze[curRow - 1][curCol] == WALL) ? 0 : Distance(curRow - 1, curCol, to_go_to->getRow(), to_go_to->getCol());
//        max = std::max(max, h2);
//        double h3 = (maze[curRow][curCol + 1] == WALL) ? 0 : Distance(curRow, curCol + 1, to_go_to->getRow(), to_go_to->getCol());
//        max = std::max(max, h3);
//        double h4 = (maze[curRow][curCol - 1] == WALL) ? 0 : Distance(curRow, curCol - 1, to_go_to->getRow(), to_go_to->getCol());
//        max = std::max(max, h4);
//
//        if (max == 0) {
//            return new Cell(curRow, curCol, nullptr);
//        }
//
//        if (max == h1) {
//            return new Cell(curRow + 1, curCol, nullptr);
//        }
//        else if (max == h2) {
//            return new Cell(curRow - 1, curCol, nullptr);
//        }
//        else if (max == h3) {
//            return new Cell(curRow, curCol + 1, nullptr);
//        }
//        else if (max == h4) {
//            return new Cell(curRow, curCol - 1, nullptr);
//        }
//    }
//    return to_go_to.release();
//}
//
//std::unique_ptr<Cell> Pacman::BFSIteration(std::queue<std::unique_ptr<Cell>>& grays, int maze[HEIGHT][WIDTH], const vector<int>& targets) {
//    if (grays.empty()) {
//        std::cout << "There is no solution. Grays is empty in pacman.\n";
//        return nullptr;
//    }
//
//    std::unique_ptr<Cell> pCurrent = std::move(grays.front());
//    grays.pop();
//
//    int row = pCurrent->getRow();
//    int col = pCurrent->getCol();
//
//    if (maze[row][col] != START) {
//        maze[row][col] = BLACK;
//    }
//
//    std::unique_ptr<Cell> go_on = nullptr;
//    // Check neighbors
//    if (maze[row + 1][col] == SPACE || maze[row + 1][col] == COIN || isTarget(targets, maze[row + 1][col])) 
//        go_on = PacmanCheckNeighbor(row + 1, col, pCurrent.get(), targets, maze, grays);
//    if (!go_on && (maze[row - 1][col] == SPACE || maze[row - 1][col] == COIN || isTarget(targets, maze[row - 1][col])))
//        go_on = PacmanCheckNeighbor(row - 1, col, pCurrent.get(), targets, maze, grays);
//    if (!go_on && (maze[row][col - 1] == SPACE || maze[row][col - 1] == COIN || isTarget(targets, maze[row][col - 1])))
//        go_on = PacmanCheckNeighbor(row, col - 1, pCurrent.get(), targets, maze, grays);
//    if (!go_on && (maze[row][col + 1] == SPACE || maze[row][col + 1] == COIN || isTarget(targets, maze[row][col + 1])))
//        go_on = PacmanCheckNeighbor(row, col + 1, pCurrent.get(), targets, maze, grays);
//
//    return go_on;
//}
//
////Cell* Pacman::BFSIteration(std::queue<std::unique_ptr<Cell>>& grays, int maze[HEIGHT][WIDTH], const vector<int>& targets) {
////    if (grays.empty()) {
////        std::cout << "There is no solution. Grays is empty in pacman.\n";
////        return nullptr;
////    }
////
////    std::unique_ptr<Cell> pCurrent = std::move(grays.front());
////    grays.pop();
////
////    int row = pCurrent->getRow();
////    int col = pCurrent->getCol();
////
////    if (maze[row][col] != START) {
////        maze[row][col] = BLACK;
////    }
////
////    Cell* go_on = nullptr;
////    // Check neighbors
////    if (maze[row + 1][col] == SPACE || maze[row + 1][col] == COIN || isTarget(targets, maze[row + 1][col])) 
////        go_on = PacmanCheckNeighbor(row + 1, col, pCurrent.get(), targets, maze, grays);
////    if (!go_on && (maze[row - 1][col] == SPACE || maze[row - 1][col] == COIN || isTarget(targets, maze[row - 1][col])))
////        go_on = PacmanCheckNeighbor(row - 1, col, pCurrent.get(), targets, maze, grays);
////    if (!go_on && (maze[row][col - 1] == SPACE || maze[row][col - 1] == COIN || isTarget(targets, maze[row][col - 1])))
////        go_on = PacmanCheckNeighbor(row, col - 1, pCurrent.get(), targets, maze, grays);
////    if (!go_on && (maze[row][col + 1] == SPACE || maze[row][col + 1] == COIN || isTarget(targets, maze[row][col + 1])))
////        go_on = PacmanCheckNeighbor(row, col + 1, pCurrent.get(), targets, maze, grays);
////
////    return go_on;
////}
//
//std::unique_ptr<Cell> Pacman::PacmanCheckNeighbor(int row, int col, Cell* pCurrent, const vector<int>& targets, int maze[HEIGHT][WIDTH], std::queue<std::unique_ptr<Cell>>& grays) {
//    if (isTarget(targets, maze[row][col])) {
//        return std::make_unique<Cell>(*pCurrent);
//    }
//
//    if (maze[row][col] == SPACE || maze[row][col] == COIN) {
//        auto pc = std::make_unique<Cell>(row, col, pCurrent);
//        maze[row][col] = GRAY;
//        grays.push(std::move(pc));
//    }
//    return nullptr;
//}
//
////Cell* Pacman::PacmanCheckNeighbor(int row, int col, Cell* pCurrent, const vector<int>& targets, int maze[HEIGHT][WIDTH], std::queue<std::unique_ptr<Cell>>& grays) {
////    if (isTarget(targets, maze[row][col])) {
////        return pCurrent;
////    }
////
////    if (maze[row][col] == SPACE || maze[row][col] == COIN) {
////        auto pc = std::make_unique<Cell>(row, col, pCurrent);
////        maze[row][col] = GRAY;
////        grays.push(std::move(pc));
////    }
////    return nullptr;
////}
//
//Cell* Pacman::PacmanRestorePath(Cell* pc) {
//    while (pc->getParent() && pc->getParent()->getParent() != nullptr) {
//        pc = pc->getParent();
//    }
//    return pc;
//}
