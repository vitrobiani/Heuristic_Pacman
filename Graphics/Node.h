#pragma once
#include "Definitions.h"
#include <vector>
#include "Edge.h"
using namespace std;

class Edge;

class Node
{
private:
	double x, y, h;
	int color;
	double g; // total cost of shortest path (so far) from the start
	Node* parent;
	vector <Edge*> outgoing; // the list of edges that connect the current node to the adjascent nodes


public:
	Node(); // default contructor
	void SetX(double value) { x = value; }
	void SetY(double value) { y = value; }
	void SetColor(int c) { color = c; }
	void SetG(double value) { g = value; }
	void SetParent(Node* p) { parent = p; }
	void AddEdge(Edge* e) { outgoing.push_back(e); }
	void Show();
	double GetX() { return x; }
	double GetY() { return y; }
	double GetG() { return g; }
	double GetH() { return h; }
	int GetColor() { return color; }
	Node* GetParent() { return parent; }
	vector <Edge*> GetOutgoing() { return outgoing; }
};

