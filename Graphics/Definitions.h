#pragma once
#include <random>
#include "GameOver.h"


using namespace std;
const int SPACE = 0;
const int WALL = 1;
const int START = 2;
const int PACMAN = 3;
const int PATH = 4;
const int GRAY = 5;
const int BLACK = 6;
const int WHITE = 7;
const int WHITE_TARGET = 8;
const int GRAY_TARGET = 9;
const int COIN = 10;
const int GHOST_RED = 11;
const int GHOST_GREEN = 12;
const int GHOST_BLUE = 13;
const vector<int> ghostTargets = { GHOST_RED, GHOST_GREEN, GHOST_BLUE };

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int IS_FREE = -1;
const int BFS_DEPTH = 250;

const double MAX_G = 10000;
const int MSZ = 75;
const int WIDTH = MSZ;
const int HEIGHT = MSZ;
//const int WIDTH = 28;
//const int HEIGHT = 31;


inline int generateRandomInt(int min, int max) {
    static std::random_device rd;      // Random device
    static std::mt19937 gen(rd());     // Mersenne Twister engine
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
