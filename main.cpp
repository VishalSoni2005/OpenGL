//* bresenham line and circle drawing algo
#include <GL/freeglut.h>
#include <iostream>
using namespace std;

void plotCirclePoints(int xc, int yc, int x, int y)
{
  glVertex2i(xc + x, yc + y);
  glVertex2i(xc - x, yc + y);
  glVertex2i(xc + x, yc - y);
  glVertex2i(xc - x, yc - y);
  glVertex2i(xc + y, yc + x);
  glVertex2i(xc - y, yc + x);
  glVertex2i(xc + y, yc - x);
  glVertex2i(xc - y, yc - x);
}

void drawCircle(int xc, int yc, int r)
{
  int x = 0, y = r;
  int p = 3 - 2 * r;

  glBegin(GL_POINTS);
  while (x <= y)
  {
    plotCirclePoints(xc, yc, x, y);
    x++;
    if (p < 0)
      p = p + 4 * x + 6;
    else
    {
      y--;
      p = p + 4 * (x - y) + 10;
    }
  }
  glEnd();
  glFlush();
}

void line(int x1, int y1, int x2, int y2)
{
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);

  int sx = (x2 > x1) ? 1 : -1;
  int sy = (y2 > y1) ? 1 : -1;

  int x = x1;
  int y = y1;

  int p;

  glBegin(GL_POINTS);

  if (dx > dy)
  {
    p = 2 * dy - dx; // ✅ Corrected
    for (int i = 0; i <= dx; i++)
    {
      glVertex2i(x, y);
      x += sx;
      if (p >= 0)
      {
        y += sy;
        p += 2 * (dy - dx);
      }
      else
        p += 2 * dy;
    }
  }
  else
  {
    p = 2 * dx - dy; // ✅ Corrected
    for (int i = 0; i <= dy; i++)
    {
      glVertex2i(x, y);
      y += sy;
      if (p >= 0)
      {
        x += sx;
        p += 2 * (dx - dy);
      }
      else
        p += 2 * dx;
    }
  }

  glEnd();
  glFlush();
}



void init()
{ //* CCOPS
  glClearColor(0, 0, 0, 1);
  glColor3f(1, 1, 1);
  gluOrtho2D(0, 600, 0, 600);kl
  glPointSize(2);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  drawCircle(300, 300, 100);

  line(0, 0, 500, 500);
  glFlush();
}

int main(int argc, char **argv)
{
  //! IDPSC
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Todays practice");

  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}