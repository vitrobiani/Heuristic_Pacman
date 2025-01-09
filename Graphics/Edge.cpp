#include "Edge.h"
#include "glut.h"

Edge::Edge()
{
	pn1 = nullptr;
	pn2 = nullptr;
	cost = MAX_COST;
	isPath = false;
}

void Edge::Show()
{
	if (isPath)
		glLineWidth(2);
	else
		glLineWidth(1);

	glColor3d(0, 0, 0);
	glBegin(GL_LINES);
		glVertex2d(pn1->GetX(), pn1->GetY());
		glVertex2d(pn2->GetX(), pn2->GetY());
	glEnd();
}
