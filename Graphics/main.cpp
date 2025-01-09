
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "glut.h"
#include <queue>
#include <vector>
#include "Cell.h"
#include <iostream>
#include "Definitions.h"
#include "Node.h"
#include "Edge.h"
#include "CompareNodes.h"
#include "Pacman.h"
#include "Ghost.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int maze[HEIGHT][WIDTH] = {0};
Pacman* p = new Pacman(14, 7);
vector<Ghost*> ghosts = {   
							new Ghost(3, HEIGHT - 2, GHOST_RED),
							new Ghost(1, HEIGHT - 2, GHOST_GREEN),
							new Ghost(1, HEIGHT - 4, GHOST_BLUE),
						};

bool isAS = false;
bool setGridlines = false;
bool flag = false;

void SetupMaze() {
	int i, j;
	for (i = 0; i < HEIGHT; i++)
		for (j = 0; j < WIDTH; j++)
			maze[i][j] = COIN;


#pragma region Maze_Layout
	// upper and lower walls
	for (i = 0; i < WIDTH; i++) {
		maze[0][i] = WALL;
		maze[HEIGHT - 1][i] = WALL;
	}

	// upper side walls 
	for (i = 0; i < 10; i++) {
		maze[HEIGHT - i][WIDTH - 1] = WALL;
		maze[HEIGHT - i][0] = WALL;
	}

	// lower side walls
	for (i = 0; i < 12; i++) {
		maze[i][0] = WALL;
		maze[i][WIDTH - 1] = WALL;
	}

	// horizontal walls for blank corridor cubes
	for (i = 0; i < 6; i++) {
		for ( j = 11; j < 16; j++) 
			maze[j][i] = WALL; 
		for ( j = 17; j < 22; j++) 
			maze[j][i] = WALL; 
		for ( j = 11; j < 16; j++) 
			maze[j][WIDTH - 1 - i] = WALL;
		for ( j = 17; j < 22; j++) 
			maze[j][WIDTH - 1 - i] = WALL;
	}

	// horizontal batton walls
	for (i = 2; i < 12; i++) {
		maze[2][i] = WALL;
		maze[2][WIDTH - 1 - i] = WALL;
		maze[3][i] = WALL;
		maze[3][WIDTH - 1 - i] = WALL;
	}

	// vertical batton walls
	for (i = 2; i < 7; i++) {
		maze[i][7] = WALL;
		maze[i][8] = WALL;
		maze[i][WIDTH - 8] = WALL;
		maze[i][WIDTH - 9] = WALL;

	// horizontal walls lower patach
		maze[i][13] = WALL;
		maze[i][14] = WALL;
	}

	// vertical walls lower patach
	for (i = 10; i < 18; i++) {
		maze[5][i] = WALL;
		maze[6][i] = WALL;
	}

	// vertical walls upper patach
	for (i = 8; i < 13; i++) {
		maze[i][13] = WALL;
		maze[i][14] = WALL;
	}

	// horizontal walls upper patach
	for (i = 10; i < 18; i++) {
		maze[11][i] = WALL;
		maze[12][i] = WALL;
	}

	// straight blocks beween patachs
	for (i = 7; i < 12; i++) {
		maze[8][i] = WALL;
		maze[9][i] = WALL;
		maze[8][WIDTH - 1 - i] = WALL;
		maze[9][WIDTH - 1 - i] = WALL;
	}
	
	// nibits
	for (i = 1; i < 3; i++) {
		maze[5][i] = WALL;
		maze[6][i] = WALL;
		maze[5][WIDTH - 1 - i] = WALL;
		maze[6][WIDTH - 1 - i] = WALL;
	}

	// vertical walls for hooks
	for (i = 2; i < 6; i++) {
		maze[8][i] = WALL;
		maze[9][i] = WALL;
		maze[8][WIDTH - 1 - i] = WALL;
		maze[9][WIDTH - 1 - i] = WALL;
	}

	// horizontal walls for hooks
	for (i = 5; i < 8; i++) {
		maze[i][4] = WALL;
		maze[i][5] = WALL;
		maze[i][WIDTH - 5 ] = WALL;
		maze[i][WIDTH - 6] = WALL;
	}

	// vertical walls near ghost box
	for (i = 11; i < 15; i++) {
		maze[i][7] = WALL;
		maze[i][8] = WALL;
		maze[i][WIDTH - 8] = WALL;
		maze[i][WIDTH - 9] = WALL;
	}

	// vertical wall for side patachs
	for (i = 17; i < 25; i++) {
		maze[i][7] = WALL;
		maze[i][8] = WALL;
		maze[i][WIDTH - 8] = WALL;
		maze[i][WIDTH - 9] = WALL;
	}

	// horizontal wall for side patachs
	for (i = 8; i < 12; i++) {
		maze[20][i] = WALL;
		maze[21][i] = WALL;
		maze[20][WIDTH - 1 - i] = WALL;
		maze[21][WIDTH - 1 - i] = WALL;
	}

	// vertical walls upper upper patach
	for (i = 20; i < 23; i++) {
		maze[i][13] = WALL;
		maze[i][14] = WALL;
	}

	// horizontal walls upper upper patach
	for (i = 10; i < 18; i++) {
		maze[24][i] = WALL;
		maze[23][i] = WALL;
	}

	// upper thin blocks
	for (i = 2; i < 6; i++) {
		maze[23][i] = WALL;
		maze[24][i] = WALL;
		maze[23][WIDTH - 1 - i] = WALL;
		maze[24][WIDTH - 1 - i] = WALL;
	}

	for (i = 2; i < 6; i++) {
		maze[26][i] = WALL;
		maze[27][i] = WALL;
		maze[28][i] = WALL;
		maze[26][WIDTH - 1 - i] = WALL;
		maze[27][WIDTH - 1 - i] = WALL;
		maze[28][WIDTH - 1 - i] = WALL;
	}

	for (i = 7; i < 12; i++) {
		maze[26][i] = WALL;
		maze[27][i] = WALL;
		maze[28][i] = WALL;
		maze[26][WIDTH - 1 - i] = WALL;
		maze[27][WIDTH - 1 - i] = WALL;
		maze[28][WIDTH - 1 - i] = WALL;
	}

	for (i = 26; i < 30; i++) {
		maze[i][13] = WALL;
		maze[i][14] = WALL;
	}

	// ghost box
	for (i = 10; i < 18; i++) {
		maze[14][i] = WALL;
		maze[18][i] = WALL;
	}
	for (i = 15; i < 18; i++) {
		maze[i][10] = WALL;
		maze[i][17] = WALL;
	}

	// no coins in ghost box and around it
	for (i = 9; i < 19; i++) {
		maze[13][i] = SPACE;
		maze[19][i] = SPACE;
	}
	for (i = 14; i < 19; i++) {
		maze[i][9] = SPACE;
		maze[i][18] = SPACE;
	}
	for (i = 11; i < 17; i++) {
		maze[15][i] = SPACE;
		maze[17][i] = SPACE;
	}
	for (i = 16; i < 17; i++) {
		maze[i][11] = SPACE;
		maze[i][16] = SPACE;
	}
	maze[18][13] = SPACE;
	maze[18][14] = SPACE;
#pragma endregion


	maze[p->getRow()][p->getCol()] = PACMAN;
	
    for (auto& g: ghosts) {
		maze[g->getRow()][g->getCol()] = g->getColor();
    }
}

double Distance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void init()
{
	glClearColor(0.7, 0.7, 0.7, 0);// color of window background
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1); // set the coordinates system

	srand(time(0));

	SetupMaze();
}

void ShowMaze() {
	int i, j;
	for(i=0;i<HEIGHT;i++)
		for (j = 0;j < WIDTH;j++)
		{
			//1. set color of cell
			switch (maze[i][j])
			{
			case SPACE:
				glColor3d(1, 1, 1); // white
				break;
			case WALL:
				glColor3d(0, 0, 0); // black
				break;
			case START:
				glColor3d(0.6, 0.6, 1); // blue
				break;
			case PACMAN:
				glColor3d(1, 0, 1); // yellow
				break;
			case PATH:
				glColor3d(1, 0, 1); // magenta
				break;
			case GRAY:
				glColor3d(0, 1, 0); // green
				break;
			case BLACK:
				glColor3d(0.6, 0.6, 0.6); // gray
				break;
			case COIN:
				glColor3d(1, 0.55, 0.2); // orange
				break;
			case GHOST_RED:
				glColor3d(1, 0, 0); // red
				break;
			case GHOST_GREEN:
				glColor3d(0, 1, 0); // green
				break;
			case GHOST_BLUE:
				glColor3d(0, 0, 1); // blue 
				break;
			}
			// show cell
			glBegin(GL_POLYGON);
			glVertex2d(j, i);
			glVertex2d(j, i + 1);
			glVertex2d(j+1, i + 1);
			glVertex2d(j + 1, i );
			glEnd();

			// set grid lines
			if (setGridlines) {
				glColor3d(0, 0, 0); // Set gridline color to black
				glBegin(GL_LINE_LOOP); // Outline the cell
				glVertex2d(j, i);
				glVertex2d(j, i + 1);
				glVertex2d(j + 1, i + 1);
				glVertex2d(j + 1, i);
				glEnd();
			}
		}
}

//void RestorePath(Cell* pc)
//{
//	while (pc != nullptr)
//	{
//		maze[pc->getRow()][pc->getCol()] = PATH;
//		pc = pc->getParent();
//	}
//}
//
//bool CheckNeighbor(int row, int col, Cell* pCurrent, bool isBFS, int target)
//{
//	if (maze[row][col] == target)
//	{
//		if(isBFS)
//			runBFS = false;
//		else
//			runDFS = false;
//		cout << "The solution has been found. \n";
//		printf("The g: %d", pCurrent->getG());
//		RestorePath(pCurrent);
//		return false;
//	}
//	else // maze[row][col] must be SPACE (WHITE)
//	{
//		Cell* pc = new Cell(row, col, pCurrent);
//		maze[row][col] = GRAY;
//		if (isBFS) grays.push(pc);
//		else dfs_grays.push_back(pc);
//		return true;
//	}
//}
//
//void RunBFSIteration(int target) 
//{
//	Cell* pCurrent;
//	int row, col;
//	bool go_on = true;
//
//	if (grays.empty())
//	{
//		runBFS = false;
//		cout << "There is no solution. Grays is empty\n";
//		return;
//	}
//	else // grays is not empty
//	{
//		pCurrent = grays.top();
//		grays.pop(); // extract the first element from grays
//		// 1. paint pCurrent black
//		row = pCurrent->getRow();
//		col = pCurrent->getCol();
//		if (maze[row][col] != START)
//			maze[row][col] = BLACK;
//		// 2. check all the neighbors of pCurrent
//		// go up
//		if (maze[row + 1][col] == SPACE || maze[row + 1][col] == target)
//			go_on = CheckNeighbor(row + 1, col, pCurrent,true, target);
//		// down
//		if(go_on && (maze[row - 1][col] == SPACE || maze[row - 1][col] == target))
//			go_on = CheckNeighbor(row - 1, col, pCurrent,true, target);
//		// left
//		if (go_on && (maze[row ][col- 1] == SPACE || maze[row ][col- 1] == target))
//			go_on = CheckNeighbor(row , col- 1, pCurrent, true, target);
//		// right
//		if (go_on && (maze[row][col +1] == SPACE || maze[row][col + 1] == target))
//			go_on = CheckNeighbor(row, col + 1, pCurrent, true, target);
//		
//	}
//}

// note: pq is passed by reference
void UpdateG(Node* pNeighbor, priority_queue<Node*, vector<Node*>, CompareNodes> &pq)
{
	vector <Node*> tmp;

	while (pq.top() != pNeighbor)
	{
		tmp.push_back(pq.top());
		pq.pop();
	}
	// now pq.top() is pNeighbor
	pq.pop();
	pq.push(pNeighbor);
	while (!tmp.empty())
	{
		pq.push(tmp.back());
		tmp.pop_back();
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	ShowMaze();

	glutSwapBuffers(); // show all
}

void cloneMaze(int source[HEIGHT][WIDTH], int target[HEIGHT][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			target[i][j] = source[i][j];
		}
	}
}

void updateGhostPos(Ghost* g) {
	int clonedMaze[HEIGHT][WIDTH] = { 0 };
	cloneMaze(maze, clonedMaze);
	maze[g->getRow()][g->getCol()] = g->getPrev();
	Cell* c = g->runAS(clonedMaze, p->getRow(), p->getCol());
	if (maze[c->getRow()][c->getCol()] != GHOST_BLUE && maze[c->getRow()][c->getCol()] != GHOST_GREEN && maze[c->getRow()][c->getCol()] != GHOST_RED) {
		g->setPrev(maze[c->getRow()][c->getCol()]);
		maze[c->getRow()][c->getCol()] = g->getColor();
		g->setRow(c->getRow());
		g->setCol(c->getCol());
	}
}

void updatePacmanPos() {
	int clonedMaze[HEIGHT][WIDTH] = { 0 };
	cloneMaze(maze, clonedMaze);
	maze[p->getRow()][p->getCol()] = SPACE;
	Cell* c = p->runBFS(clonedMaze, p->getRow(), p->getCol());

	maze[c->getRow()][c->getCol()] = PACMAN;
	p->setRow(c->getRow());
	p->setCol(c->getCol());
	if (p->getRow() == 16 && p->getCol() == WIDTH - 1) { 
		p->setCol(1);
		maze[c->getRow()][c->getCol()] = SPACE;
		maze[p->getRow()][p->getCol()] = PACMAN;
	}
	if (p->getRow() == 16 && p->getCol() == 0) { 
		p->setCol(WIDTH-2);
		maze[c->getRow()][c->getCol()] = SPACE;
		maze[p->getRow()][p->getCol()] = PACMAN;
	}
}

void idle() {
	if (flag) {
		updatePacmanPos();
		if (rand() % 2 == 0)
			updatePacmanPos();
		for (auto& g : ghosts) {
			updateGhostPos(g);
		}
	}
	Sleep(150);
	glutPostRedisplay(); // indirect call to display
}

void menu(int choice)
{
	switch (choice)
	{
	case 1: 
		glutDisplayFunc(display);
		if (flag) flag = false;
		else flag = true;
		break;
	case 2: 
		if (setGridlines) setGridlines = false;
		else setGridlines = true;
		break;

	}
}

void main(int argc, char* argv[]) 
{
	glutInit(&argc, argv);
	// definitions for visual memory (Frame buffer) and double buffer
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(600, 0);
	glutCreateWindow("BFS - DFS");

	// display is a refresh function
	glutDisplayFunc(display);
	// idle is a update function
	glutIdleFunc(idle);

	// add menu
	glutCreateMenu(menu);
	glutAddMenuEntry("start", 1);
	glutAddMenuEntry("grid", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();

	glutMainLoop();
}