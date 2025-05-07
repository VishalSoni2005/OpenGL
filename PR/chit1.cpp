#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int ch = 1; // Default to Simple Line (1: Simple, 2: Dashed, 3: Solid)
int xStart, yStart;
bool firstClick = true; // Flag to check if it's the first click

// Draw a single point
void displayPoint(int x, int y)
{
  glBegin(GL_POINTS);
  glPointSize(40);
  glVertex2i(x, y);
  glEnd();
}

// Bresenham’s line algorithm with patterns
void drawLine(int x1, int y1, int x2, int y2, int pattern)
{
  int dx = abs(x2 - x1), dy = abs(y2 - y1);
  int incx = (x2 >= x1) ? 1 : -1;
  int incy = (y2 >= y1) ? 1 : -1;
  int x = x1, y = y1;
  int p, inc1, inc2;
  int count = 0;

  displayPoint(x, y); // Draw starting point

  if (dx > dy)
  { // Line is more horizontal
    p = 2 * dy - dx;
    inc1 = 2 * (dy - dx);
    inc2 = 2 * dy;

    for (int i = 0; i < dx; i++)
    {
      x += incx;
      if (p >= 0)
      {
        y += incy;
        p += inc1;
      }
      else
      {
        p += inc2;
      }

      // Apply the pattern logic
      bool draw = false;
      if (pattern == 1)
        draw = true; // Always draw (Simple Line)
      else if (pattern == 2)
        draw = (count % 2 == 0); // Dashed (draw every 2 steps)
      else if (pattern == 3)
        draw = (count % 6 < 3); // Solid (draw 3 steps, skip 3 steps)

      if (draw)
        displayPoint(x, y); // Draw the point if draw is true

      count++;
    }
  }
  else
  { // Line is more vertical
    p = 2 * dx - dy;
    inc1 = 2 * (dx - dy);
    inc2 = 2 * dx;

    for (int i = 0; i < dy; i++)
    {
      y += incy;
      if (p >= 0)
      {
        x += incx;
        p += inc1;
      }
      else
      {
        p += inc2;
      }

      // Apply the pattern logic
      bool draw = false;
      if (pattern == 1)
        draw = true; // Always draw (Simple Line)
      else if (pattern == 2)
        draw = (count % 2 == 0); // Dashed (draw every 2 steps)
      else if (pattern == 3)
        draw = (count % 6 < 3); // Solid (draw 3 steps, skip 3 steps)

      if (draw)
        displayPoint(x, y); // Draw the point if draw is true

      count++;
    }
  }

  glFlush(); // Ensure all points are drawn
}

// Draw axes for the 4 quadrants
void drawAxes()
{
  glColor3f(0.5f, 0.5f, 0.5f); // Grey color for axes

  glBegin(GL_LINES);
  glVertex2i(-300, 0);
  glVertex2i(300, 0); // X-axis
  glVertex2i(0, -300);
  glVertex2i(0, 300); // Y-axis
  glEnd();
}

// Mouse click handler
void mouseCallback(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    x = x - 300; // Convert to Cartesian coordinates
    y = 300 - y; // Convert to Cartesian coordinates

    if (firstClick)
    {
      xStart = x;
      yStart = y;
      firstClick = false; // First point stored
    }
    else
    {
      drawLine(xStart, yStart, x, y, ch); // Draw line between the two points
      firstClick = true;                  // Reset for next line
    }
  }
}

// Keyboard handler
void keyboardCallback(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 's':
    ch = 1;
    break; // Simple Line
  case 'd':
    ch = 2;
    break; // Dashed Line
  case 't':
    ch = 3;
    break; // Solid Line
  }
}

// Initial screen setup
void display()
{
  glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
  drawAxes();                   // Draw the axes (for 4 quadrants)
  glFlush();
}

// OpenGL initialization
void initializeOpenGL()
{
  glClearColor(1.0, 1.0, 1.0, 1.0); // White background
  glColor3f(0.0, 0.0, 0.0);         // Black lines
  gluOrtho2D(-300, 300, -300, 300); // Cartesian coordinate system, with origin at (0,0)
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Bresenham Line with Mouse - 4 Quadrants");

  initializeOpenGL();

  cout << "---- Line Drawing Program ----" << endl;
  cout << "Click two points to draw line\n";
  cout << "Press 's' - Simple Line\n";
  cout << "Press 'd' - Dashed Line\n";
  cout << "Press 't' - Solid Line\n";

  glutDisplayFunc(display);
  glutMouseFunc(mouseCallback);
  glutKeyboardFunc(keyboardCallback);

  glutMainLoop();
  return 0;
}
