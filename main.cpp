//! two
// left click on two diagonal points
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void displayPoint(int x, int y)
{
  glColor3f(1, 1, 0);
  glPointSize(3);
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void SimpleLine(int x1, int y1, int x2, int y2)
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

      // Middle Square
      mx = (xst + xend) / 2;
      my = (yst + yend) / 2;
      SimpleLine(mx, yend, xst, my);
      SimpleLine(xst, my, mx, yst);
      SimpleLine(mx, yst, xend, my);
      SimpleLine(xend, my, mx, yend);

      // innermost square
      int mx1 = (mx + xst) / 2;
      int my1 = (my + yend) / 2;
      int my2 = (my + yst) / 2;
      int mx2 = (mx + xend) / 2;
      SimpleLine(mx1, my1, mx1, my2);
      SimpleLine(mx1, my2, mx2, my2);
      SimpleLine(mx2, my2, mx2, my1);
      SimpleLine(mx2, my1, mx1, my1);
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
// IDPSC
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

//! one
// #include <GL/freeglut.h>
// #include <iostream>
// #include <cmath>
// #include <math.h>
// using namespace std;

// void breLine(int x1, int y1, int x2, int y2)
// {
//   int dx = abs(x2 - x1);
//   int dy = abs(y2 - y1);
//   int x = x1, y = y1;

//   int sx = (x2 > x1) ? 1 : -1;
//   int sy = (y2 > y1) ? 1 : -1;

//   glBegin(GL_POINTS);

//   if (dx > dy)
//   { // slope < 1
//     int p = 2 * dy - dx;
//     for (int i = 0; i <= dx; i++)
//     {

//       x += sx;
//       if (p >= 0)
//       {
//         y += sy;
//         p += 2 * (dy - dx);
//       }
//       else
//       {
//         p += 2 * dy;
//       }
//     }
//   }

//   else
//   { // slope >= 1
//     int p = 2 * dx - dy;
//     for (int i = 0; i <= dy; i++)
//     {
//       glVertex2i(x, y);
//       y += sy;
//       if (p >= 0)
//       {
//         x += sx;
//         p += 2 * (dx - dy);
//       }
//       else
//       {
//         p += 2 * dx;
//       }
//     }
//   }

//   glEnd();
//   glFlush();
// }

// void dottedLine(int x1, int y1, int x2, int y2)
// {
//   int dx = abs(x2 - x1);
//   int dy = abs(y2 - y1);
//   int x = x1, y = y1;

//   int sx = (x2 > x1) ? 1 : -1;
//   int sy = (y2 > y1) ? 1 : -1;

//   glBegin(GL_POINTS);

//   if (dx > dy)
//   { // slope < 1
//     int p = 2 * dy - dx;
//     for (int i = 0; i <= dx; i++)
//     {
//       if (i % 5 == 0) // plot every 5th point
//         glVertex2i(x, y);

//       x += sx;
//       if (p >= 0)
//       {
//         y += sy;
//         p += 2 * (dy - dx);
//       }
//       else
//       {
//         p += 2 * dy;
//       }
//     }
//   }
//   else
//   { // slope >= 1
//     int p = 2 * dx - dy;
//     for (int i = 0; i <= dy; i++)
//     {
//       if (i % 5 == 0) // plot every 5th point
//         glVertex2i(x, y);

//       y += sy;
//       if (p >= 0)
//       {
//         x += sx;
//         p += 2 * (dx - dy);
//       }
//       else
//       {
//         p += 2 * dx;
//       }
//     }
//   }

//   glEnd();
//   glFlush();
// }

// void breDashedLine(int x1, int y1, int x2, int y2)
// {
//   int dx = abs(x2 - x1);
//   int dy = abs(y2 - y1);
//   int x = x1, y = y1;
//   int sx = (x2 > x1) ? 1 : -1;
//   int sy = (y2 > y1) ? 1 : -1;

//   glBegin(GL_POINTS);
//   if (dx > dy)
//   {
//     int p = 2 * dy - dx;
//     for (int i = 0; i <= dx; i++)
//     {
//       if ((i / 5) % 2 == 0) // dash for 5 pixels, skip for 5
//         glVertex2i(x, y);
//       x += sx;
//       if (p >= 0)
//       {
//         y += sy;
//         p += 2 * (dy - dx);
//       }
//       else
//       {
//         p += 2 * dy;
//       }
//     }
//   }
//   else
//   {
//     int p = 2 * dx - dy;
//     for (int i = 0; i <= dy; i++)
//     {
//       if ((i / 5) % 2 == 0)
//         glVertex2i(x, y);
//       y += sy;
//       if (p >= 0)
//       {
//         x += sx;
//         p += 2 * (dx - dy);
//       }
//       else
//       {
//         p += 2 * dx;
//       }
//     }
//   }
//   glEnd();
//   glFlush();
// }

// void breDashedDotLine(int x1, int y1, int x2, int y2)
// {
//   int dx = abs(x2 - x1);
//   int dy = abs(y2 - y1);
//   int x = x1, y = y1;
//   int sx = (x2 > x1) ? 1 : -1;
//   int sy = (y2 > y1) ? 1 : -1;

//   glBegin(GL_POINTS);
//   if (dx > dy)
//   {
//     int p = 2 * dy - dx;
//     for (int i = 0; i <= dx; i++)
//     {
//       int pattern = i % 15;
//       if (pattern < 5 || pattern == 7) // dash (0–4), skip (5–6), dot (7), skip (8–14)
//         glVertex2i(x, y);

//       x += sx;
//       if (p >= 0)
//       {
//         y += sy;
//         p += 2 * (dy - dx);
//       }
//       else
//       {
//         p += 2 * dy;
//       }
//     }
//   }
//   else
//   {
//     int p = 2 * dx - dy;
//     for (int i = 0; i <= dy; i++)
//     {
//       int pattern = i % 15;
//       if (pattern < 5 || pattern == 7)
//         glVertex2i(x, y);

//       y += sy;
//       if (p >= 0)
//       {
//         x += sx;
//         p += 2 * (dx - dy);
//       }
//       else
//       {
//         p += 2 * dx;
//       }
//     }
//   }
//   glEnd();
//   glFlush();
// }

// void init()
// {
//   // CCOPS => ClearColor, Otho2D, PointSize
//   glClearColor(0, 0, 0, 1.0); // sets the background color to light gray.
//   gluOrtho2D(0, 600, 0, 600);       // set 2d plain
//   glPointSize(3.0);                 // set the point size
//   glColor3f(1, 0, 0);
// }
// void quadrant() {

// }
// void display()
// {
//   glClear(GL_COLOR_BUFFER_BIT);
//   breLine(300, 0, 300, 600);
//   // breLine(0, 300, 600, 300);

//   breLine(50, 50, 50, 500);
//   dottedLine(500, 50, 500, 500);
//   breDashedLine(50, 500, 500, 50);
//   breDashedDotLine(50, 50, 500, 500);
//   glFlush();
// }

// int main(int argc, char **argv)
// {
//   // IDPSC
//   glutInit(&argc, argv);
//   glutInitDisplayMode(GLUT_SINGLE);
//   glutInitWindowPosition(0, 0);
//   glutInitWindowSize(600, 600);
//   glutCreateWindow("Bres Algo");

//   init();
//   glutDisplayFunc(display);
//   glutMainLoop();
//   return 0;
// }