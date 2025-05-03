#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

void breLine(int x1, int y1, int x2, int y2)
{
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int x = x1, y = y1;

  int sx = (x2 > x1) ? 1 : -1;
  int sy = (y2 > y1) ? 1 : -1;

  glBegin(GL_POINTS);

  if (dx > dy)
  { // slope < 1
    int p = 2 * dy - dx;
    for (int i = 0; i <= dx; i++)
    {
      x += sx;
      if (p >= 0)
      {
        y += sy;
        p += 2 * (dy - dx);
      }
      else
      {
        p += 2 * dy;
      }
    }
  }
  else
  { // slope >= 1
    int p = 2 * dx - dy;
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
      {
        p += 2 * dx;
      }
    }
  }

  glEnd();
  glFlush();
}

void dottedLine(int x1, int y1, int x2, int y2)
{
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int x = x1, y = y1;

  int sx = (x2 > x1) ? 1 : -1;
  int sy = (y2 > y1) ? 1 : -1;

  glBegin(GL_POINTS);

  if (dx > dy)
  { // slope < 1
    int p = 2 * dy - dx;
    for (int i = 0; i <= dx; i++)
    {
      if (i % 5 == 0) // plot every 5th point
        glVertex2i(x, y);

      x += sx;
      if (p >= 0)
      {
        y += sy;
        p += 2 * (dy - dx);
      }
      else
      {
        p += 2 * dy;
      }
    }
  }
  else
  { // slope >= 1
    int p = 2 * dx - dy;
    for (int i = 0; i <= dy; i++)
    {
      if (i % 5 == 0) // plot every 5th point
        glVertex2i(x, y);

      y += sy;
      if (p >= 0)
      {
        x += sx;
        p += 2 * (dx - dy);
      }
      else
      {
        p += 2 * dx;
      }
    }
  }

  glEnd();
  glFlush();
}

void breDashedLine(int x1, int y1, int x2, int y2)
{
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int x = x1, y = y1;
  int sx = (x2 > x1) ? 1 : -1;
  int sy = (y2 > y1) ? 1 : -1;

  glBegin(GL_POINTS);
  if (dx > dy)
  {
    int p = 2 * dy - dx;
    for (int i = 0; i <= dx; i++)
    {
      if ((i / 5) % 2 == 0) // dash for 5 pixels, skip for 5
        glVertex2i(x, y);
      x += sx;
      if (p >= 0)
      {
        y += sy;
        p += 2 * (dy - dx);
      }
      else
      {
        p += 2 * dy;
      }
    }
  }
  else
  {
    int p = 2 * dx - dy;
    for (int i = 0; i <= dy; i++)
    {
      if ((i / 5) % 2 == 0)
        glVertex2i(x, y);
      y += sy;
      if (p >= 0)
      {
        x += sx;
        p += 2 * (dx - dy);
      }
      else
      {
        p += 2 * dx;
      }
    }
  }
  glEnd();
  glFlush();
}

void breDashedDotLine(int x1, int y1, int x2, int y2)
{
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int x = x1, y = y1;
  int sx = (x2 > x1) ? 1 : -1;
  int sy = (y2 > y1) ? 1 : -1;

  glBegin(GL_POINTS);
  if (dx > dy)
  {
    int p = 2 * dy - dx;
    for (int i = 0; i <= dx; i++)
    {
      int pattern = i % 15;
      if (pattern < 5 || pattern == 7) // dash (0–4), skip (5–6), dot (7), skip (8–14)
        glVertex2i(x, y);

      x += sx;
      if (p >= 0)
      {
        y += sy;
        p += 2 * (dy - dx);
      }
      else
      {
        p += 2 * dy;
      }
    }
  }
  else
  {
    int p = 2 * dx - dy;
    for (int i = 0; i <= dy; i++)
    {
      int pattern = i % 15;
      if (pattern < 5 || pattern == 7)
        glVertex2i(x, y);

      y += sy;
      if (p >= 0)
      {
        x += sx;
        p += 2 * (dx - dy);
      }
      else
      {
        p += 2 * dx;
      }
    }
  }
  glEnd();
  glFlush();
}

void init()
{
  // CCOPS => ClearColor, Otho2D, PointSize
  glClearColor(0, 0, 0, 1.0); // sets the background color to light gray.
  gluOrtho2D(0, 600, 0, 600); // set 2d plain
  glPointSize(3.0);           // set the point size
  glColor3f(1, 0, 0);
}
void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  breLine(50, 50, 50, 500);
  dottedLine(500, 50, 500, 500);
  breDashedLine(50, 500, 500, 50);
  breDashedDotLine(50, 50, 500, 500);
  glFlush();
}

int main(int argc, char **argv)
{
  // IDPSC
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Bres Algo");

  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}