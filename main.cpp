#include <GL/glut.h>
#include <bits/stdc++.h>
#include <climits>
#include <iostream>
#include <math.h>

using namespace std;

void Simpleline(int x1, int y1, int x2, int y2)
{
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int x = x1;
  int y = y1;
  int p;

  // Calculate slope safely (avoid division by zero)
  float slope;
  if ((x2 - x1) == 0)
    slope = (y2 - y1);
  else
    slope = (y2 - y1) / (x2 - x1);
    
  glBegin(GL_POINTS);

  // Case 1: Slope < 1 (more horizontal line)
  if (abs(slope) < 1)
  {
    // Draw left to right
    if (x1 > x2)
    {
      std::swap(x1, x2);
      std::swap(y1, y2);
    }

    dx = x2 - x1;
    dy = abs(y2 - y1);
    p = 2 * dy - dx;
    x = x1;
    y = y1;

    int yStep = (y2 > y1) ? 1 : -1;

    while (x <= x2)
    {
      glVertex2i(x, y);
      x++;

      if (p >= 0)
      {
        y += yStep;
        p += 2 * (dy - dx);
      }
      else
      {
        p += 2 * dy;
      }
    }
  }

  // Case 2: Slope >= 1 (more vertical line)
  else
  {
    // Draw bottom to top
    if (y1 > y2)
    {
      std::swap(x1, x2);
      std::swap(y1, y2);
    }

    dx = abs(x2 - x1);
    dy = y2 - y1;
    p = 2 * dx - dy;
    x = x1;
    y = y1;

    int xStep = (x2 > x1) ? 1 : -1;

    while (y <= y2)
    {
      glVertex2i(x, y);
      y++;

      if (p >= 0)
      {
        x += xStep;
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

//todo : DDA
// #include <GL/freeglut.h>
// #include <math.h>
// using namespace std;

// void displayPixel(float x, float y)
// {
//   glPointSize(4);
//   glColor3f(0.3, 1, 0.6);
//   glBegin(GL_POINTS);
//   glVertex2i(x, y);
//   glEnd();
// }

// void simpleLine(float x1, float y1, float x2, float y2)
// {

//   // step 1
//   float dx = x2 - x1;
//   float dy = y2 - y1;

//   // setp 2
//   float steps = (abs(dx) > abs(dy)) ? dx : dy;

//   // step 3;
//   float xInc = dx / steps;
//   float yInc = dy / steps;

//   // step 4;
//   float x = x1;
//   float y = y1;

//   for (int i = 0; i < steps; i++)
//   {
//     displayPixel(round(x), round(y));
//     x += xInc;
//     y += yInc;
//   }
// }

// void dotedLine(float x1, float y1, float x2, float y2)
// {

//   // step 1
//   float dx = x2 - x1;
//   float dy = y2 - y1;

//   // setp 2
//   float steps = (abs(dx) > abs(dy)) ? dx : dy;

//   // step 3;
//   float xInc = dx / steps;
//   float yInc = dy / steps;

//   // step 4;
//   float x = x1;
//   float y = y1;

//   displayPixel(round(x), round(y));
//   for (int i = 0; i < steps; i++)
//   {
//     x += xInc;
//     y += yInc;
//     if (i % 6 == 0)
//     {
//       displayPixel(round(x), round(y));
//     }
//   }
// }

// void thickLine(float x1, float y1, float x2, float y2)
// {

//   // step 1
//   float dx = x2 - x1;
//   float dy = y2 - y1;

//   // setp 2
//   float steps = (abs(dx) > abs(dy)) ? dx : dy;

//   // step 3;
//   float xInc = dx / steps;
//   float yInc = dy / steps;

//   // step 4;
//   float x = x1;
//   float y = y1;

//   for (int i = 0; i <= steps; i++)
//   {
//     glPointSize(20);
//     glColor3f(0, 0.6, 1);
//     glBegin(GL_POINTS);
//     glVertex2i(round(x), round(y));
//     glEnd();
//     x += xInc;
//     y += yInc;
//   }
// }

// void dashLine(float x1, float y1, float x2, float y2)
// {
//   int count = 1;

//   // step 1
//   float dx = x2 - x1;
//   float dy = y2 - y1;

//   // setp 2
//   float steps = (abs(dx) > abs(dy)) ? dx : dy;

//   // step 3;
//   float xInc = dx / steps;
//   float yInc = dy / steps;

//   // step 4;
//   float x = x1;
//   float y = y1;
//   displayPixel(x, y);

//   for (int i = 0; i <= steps; i++)
//   {
//     x += xInc;
//     y += yInc;
//     count++;
//     if (count <= 10)
//       displayPixel(round(x), round(y));
//     else if (count >= 10 and count < 15)
//       continue;
//     else
//     {
//       count = 1;
//       continue;
//     }
//   }
// }

// void init()
// {
//   glClearColor(0.0, 0.0, 0.0, 1.0); // black background
//   gluOrtho2D(0, 600, 0, 400);
// }

// void display()
// {
//   glClear(GL_COLOR_BUFFER_BIT);

//   // simpleLine(10, 10, 300, 300);
//   // dotedLine(10, 10, 300, 300);
//   // thickLine(10, 10, 300, 300);
//   dashLine(10, 10, 300, 300);

//   glFlush();
// }
// int main(int argc, char **argv)
// {
//   glutInit(&argc, argv);
//   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//   glutInitWindowPosition(0, 0);
//   glutInitWindowSize(400, 400);
//   glutCreateWindow("DDA");

//   init();

//   glutDisplayFunc(display);
//   glutMainLoop();
//   return 0;
// }
