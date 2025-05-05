// //! WORKING CODE OF TWO
// #include <GL/glut.h>
// #include <iostream>
// using namespace std;

// // Bresenham's Line Drawing Algorithm
// void SimpleLine(int x1, int y1, int x2, int y2)
// {
//   int dx = abs(x2 - x1);
//   int dy = abs(y2 - y1);
//   int sx = (x2 > x1) ? 1 : -1;
//   int sy = (y2 > y1) ? 1 : -1;
//   int x = x1, y = y1;

//   glBegin(GL_POINTS);
//   if (dx > dy)
//   {
//     int p = 2 * dy - dx;
//     for (int i = 0; i <= dx; i++)
//     {
//       glVertex2i(x, y);
//       x += sx;
//       if (p < 0)
//         p += 2 * dy;
//       else
//       {
//         y += sy;
//         p += 2 * (dy - dx);
//       }
//     }
//   }
//   else
//   {
//     int p = 2 * dx - dy;
//     for (int i = 0; i <= dy; i++)
//     {
//       glVertex2i(x, y);
//       y += sy;
//       if (p < 0)
//         p += 2 * dx;
//       else
//       {
//         x += sx;
//         p += 2 * (dx - dy);
//       }
//     }
//   }
//   glEnd();
//   glFlush();
// }

// // Setup OpenGL
// void init()
// {
//   glClearColor(0, 0, 0, 1);
//   gluOrtho2D(0, 600, 0, 600);
//   glColor3f(1, 1, 1);
//   glPointSize(1);
// }

// // Mouse callback for drawing pattern
// void mousefn(int button, int state, int x, int y)
// {
//   static int clickCount = 0;
//   static int startX, startY;

//   int clickedX = x;
//   int clickedY = 600 - y; // Convert to OpenGL coordinates

//   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//   {
//     if (clickCount == 0)
//     {
//       startX = clickedX;
//       startY = clickedY;
//       clickCount++;
//     }
//     else
//     {
//       int endX = clickedX;
//       int endY = clickedY;

//       // === Outer Rectangle ===
//       SimpleLine(startX, startY, endX, startY);
//       SimpleLine(endX, startY, endX, endY);
//       SimpleLine(endX, endY, startX, endY);
//       SimpleLine(startX, endY, startX, startY);

//       // === Diamond Shape ===
//       int midX = (startX + endX) / 2;
//       int midY = (startY + endY) / 2;
//       SimpleLine(midX, endY, startX, midY);
//       SimpleLine(startX, midY, midX, startY);
//       SimpleLine(midX, startY, endX, midY);
//       SimpleLine(endX, midY, midX, endY);

//       // === Inner Rectangle ===
//       int innerLeftX = (startX + midX) / 2;
//       int innerTopY = (endY + midY) / 2;
//       int innerBottomY = (startY + midY) / 2;
//       int innerRightX = (endX + midX) / 2;

//       SimpleLine(innerLeftX, innerTopY, innerLeftX, innerBottomY);
//       SimpleLine(innerLeftX, innerBottomY, innerRightX, innerBottomY);
//       SimpleLine(innerRightX, innerBottomY, innerRightX, innerTopY);
//       SimpleLine(innerRightX, innerTopY, innerLeftX, innerTopY);

//       clickCount = 0;
//     }
//   }
//   else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
//   {
//     glClear(GL_COLOR_BUFFER_BIT);
//     glFlush();
//     clickCount = 0;
//   }
// }

// // Display function
// void display()
// {
//   glClear(GL_COLOR_BUFFER_BIT);
//   glFlush();
// }

// int main(int argc, char **argv)
// {
//   glutInit(&argc, argv);
//   glutInitDisplayMode(GLUT_SINGLE);
//   glutInitWindowSize(600, 600);
//   glutInitWindowPosition(100, 100);
//   glutCreateWindow("Pattern Drawing");

//   init();
//   glutDisplayFunc(display);
//   glutMouseFunc(mousefn);
//   glutMainLoop();
//   return 0;
// }

//! code of THREE
#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

int x[10], y[10];
int i = 0, n;
bool flag = true;

void displayPoint(int x, int y)
{
  glColor3f(0, 0, 1);
  glPointSize(2);
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void SimpleLine(float x1, float y1, float x2, float y2)
{
  float dx = x2 - x1;
  float dy = y2 - y1;
  float step = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

  float Xinc = dx / step;
  float Yinc = dy / step;
  float x = x1;
  float y = y1;

  for (int i = 0; i <= step; i++)
  {
    displayPoint(round(x), round(y));
    x += Xinc;
    y += Yinc;
  }
  glFlush();
}

void drawCircle(int xc, int yc, int radius)
{
  int x = 0, y = radius;
  int p = 3 - 2 * radius;

  while (x <= y)
  {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc - y, yc - x);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc + y, yc - x);
    glEnd();

    if (p < 0)
      p += 4 * x++ + 6;
    else
      p += 4 * (x++ - y--) + 10;
  }
  glFlush();
}

void drawPolygon(int x[], int y[], int n)
{
  for (int j = 0; j < n - 1; j++)
  {
    SimpleLine(x[j], y[j], x[j + 1], y[j + 1]);
  }
  SimpleLine(x[n - 1], y[n - 1], x[0], y[0]);
  glFlush();
}

void myDisplay()
{
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void myMouse(int button, int state, int mx, int my)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag)
  {
    x[i] = mx;
    y[i] = 600 - my;
    i++;
  }
  else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && flag)
  {
    n = i;
    drawPolygon(x, y, n);

    double a = sqrt(pow(x[2] - x[1], 2.0) + pow(y[2] - y[1], 2.0));
    double b = sqrt(pow(x[2] - x[0], 2.0) + pow(y[2] - y[0], 2.0));
    double c = sqrt(pow(x[1] - x[0], 2.0) + pow(y[1] - y[0], 2.0));

    double xi = (a * x[0] + b * x[1] + c * x[2]) / (a + b + c);
    double yi = (a * y[0] + b * y[1] + c * y[2]) / (a + b + c);

    double area = 0.5 * abs(x[0] * (y[1] - y[2]) + x[1] * (y[2] - y[0]) + x[2] * (y[0] - y[1]));
    double s = (a + b + c) / 2.0;
    double r = area / s;

    drawCircle(xi, yi, r);
    cout << "Incenter: (" << xi << ", " << yi << "), Radius: " << r << endl;

    flag = false;
    glFlush();
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Triangle with Inscribed Circle");
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 600, 0, 600);

  glutDisplayFunc(myDisplay);
  glutMouseFunc(myMouse);

  glutMainLoop();
  return 0;
}
