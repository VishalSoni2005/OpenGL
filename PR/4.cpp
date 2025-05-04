// Chit No.4

/* use two left click to select diagonal points
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
    using namespace std;
int xc, yc, r;
float x01, x2, y01, y2;
int ch;
void displayPoint(int x, int y)
{
  glColor3f(0, 1, 0);
  glPointSize(2);
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void SimpleLine(float x1, float y1, float x2, float y2)
{
  float dx, dy, p;
  int i;
  float incx, incy, inc1, inc2;
  float x, y;
  dx = x2 - x1;
  dy = y2 - y1;
  if (dx < 0)
  {
    dx = -dx;
  }
  if (dy < 0)
  {
    dy = -dy;
  }
  incx = 1;
  if (x2 < x1)
  {
    incx = -1;
  }
  incy = 1;
  if (y2 < y1)
  {
    incy = -1;
  }
  x = x1;
  y = y1;
  if (dx > dy)
  {
    displayPoint(x, y);
    p = 2 * dy - dx;
    inc1 = 2 * (dy - dx);
    inc2 = 2 * dy;
    for (i = 0; i < dx; i++)
    {
      if (p >= 0)
      {
        x = x + incx;
        y = y + incy;
        p = p + inc1;
      }
      else
      {
        x = x + incx;
        p = p + inc2;
      }
      displayPoint(x, y);
    }
  }
  else
  {
    displayPoint(x, y);
    p = 2 * dx - dy;
    inc1 = 2 * (dx - dy);
    inc2 = 2 * dx;
    for (i = 0; i < dy; i++)
    {
      if (p >= 0)
      {
        x = x + incx;
        y = y + incy;
        p = p + inc1;
      }
      else
      {
        p = p + inc2;
        y = y + incy;
      }
      displayPoint(x, y);
    }
  }
  glFlush();
}
void drawCircle(int xc, int yc, int radius)
{
  int x = 0;
  int y = radius;
  int p = 3 - 2 * radius;
  glPointSize(1);
  glBegin(GL_POINTS); // Begin drawing points for the circle
  while (x <= y)
  {
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc - y, yc - x);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc + y, yc - x);
    if (p < 0)
    {
      x++;
      p = p + 4 * x + 6;
    }
    else
    {
      x++;
      y--;
      p = p + 4 * (x - y) + 10;
    }
  }
  glEnd(); // End drawing points for the circle
}


void mouse(int button, int state, int x, int y)
{
  static int xst, yst, pt = 0;
  int xend, yend, mx, my;
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    if (pt == 0)
    {
      xst = x;
      yst = 600 - y;
      pt++;
    }
    else
    {
      xend = x;
      yend = 600 - y;
      // Outside Square
      SimpleLine(xst, yst, xend, yst);
      SimpleLine(xend, yst, xend, yend);
      SimpleLine(xend, yend, xst, yend);
      SimpleLine(xst, yend, xst, yst);
      // Rhombus
      mx = (xst + xend) / 2;
      my = (yst + yend) / 2;
      SimpleLine(mx, yend, xst, my);
      SimpleLine(xst, my, mx, yst);
      SimpleLine(mx, yst, xend, my);
      SimpleLine(xend, my, mx, yend);
      // center of circle
      xc = (xst + xend) / 2;
      yc = my;
      // radius
      r = (abs((yst - my) * xc - (mx - xst) * yc + mx * my - yst * xst)) / sqrt(pow(yst - my, 2) + pow(mx - xst, 2));
      drawCircle(xc, yc, r);
    }
  }

  
  else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {
    pt = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay(); // Request a redraw
  }
  glFlush();
}
void initialize(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(0, 600, 0, 600);
}
void primitives(void)
{
  glColor3f(1, 0, 0);
  glutMouseFunc(mouse);
}
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(600, 600);
  glutCreateWindow("OpenGL - Bresenham's Algorithm");
  initialize();
  glutDisplayFunc(primitives);
  glutMainLoop();
  return 0;
}
