#include <GL/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

//! Bresenham's line drawing algorithm
void Simpleline(int x1, int y1, int x2, int y2)
{
	int M, p, dx, dy, x, y, t;
	if ((x2 - x1) == 0)
	{
		M = (y2 - y1);
	}
	else
	{
		M = (y2 - y1) / (x2 - x1);
	}
  
	if (abs(M) < 1)
	{
		if (x1 > x2)
		{
			t = x1;
			x1 = x2;
			x2 = t;

			t = y1;
			y1 = y2;
			y2 = t;
		}
		dx = abs(x2 - x1);
		dy = abs(y2 - y1);

		p = 2 * dy - dx;

		x = x1;
		y = y1;

		glBegin(GL_POINTS);
		while (x <= x2)
		{
			glVertex2f(x, y);
			x = x + 1;

			if (p >= 0)
			{
				if (M < 1)
					y = y + 1;
				else
					y = y - 1;
				p = p + 2 * dy - 2 * dx;
			}
			else
			{
				y = y;
				p = p + 2 * dy;
			}
		}
		glEnd();
	}
	if (abs(M) >= 1)
	{
		if (y1 > y2)
		{
			t = x1;
			x1 = x2;
			x2 = t;

			t = y1;
			y1 = y2;
			y2 = t;
		}
		dx = abs(x2 - x1);
		dy = abs(y2 - y1);

		p = 2 * dx - dy;

		x = x1;
		y = y1;

		glBegin(GL_POINTS);
		while (y <= y2)
		{
			glVertex2f(x, y);
			y = y + 1;

			if (p >= 0)
			{
				if (M >= 1)
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				p = p + 2 * dx - 2 * dy;
			}
			else
			{
				x = x;
				p = p + 2 * dx;
			}
		}
		glEnd();
	}
	glFlush();
}

void drawChessboard(int boardSize)
{
	int squareSize = 600 / boardSize;
	bool isWhite = true;

	for (int i = 0; i <= boardSize; i++)
	{
		Simpleline(0, i * squareSize, boardSize * squareSize, i * squareSize);
		Simpleline(i * squareSize, 0, i * squareSize, boardSize * squareSize);
	}

	for (int r = 0; r < boardSize; r++)
	{
		for (int c = 0; c < boardSize; c++)
		{
			if ((r + c) % 2 == 0)
			{
				glColor3f(1.0f, 1.0f, 1.0f);
			}
			else
			{
				glColor3f(0.0f, 0.0f, 0.0f);
			}

			glBegin(GL_POLYGON);
			glVertex2i(c * squareSize, r * squareSize);
			glVertex2i((c + 1) * squareSize, r * squareSize);
			glVertex2i((c + 1) * squareSize, (r + 1) * squareSize);
			glVertex2i(c * squareSize, (r + 1) * squareSize);
			glEnd();
		}
	}
}

void initOpenGl()
{
	glClearColor(0.7, 0.7, 0.7, 1.0);
	gluOrtho2D(0, 600, 0, 600);
	glPointSize(1.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawChessboard(8);
	glFlush();
	glutSwapBuffers();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Practical_3 SIB64");
	
	initOpenGl();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
