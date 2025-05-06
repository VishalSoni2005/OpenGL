// /*//! Chit No.15
// instructions: first left click to select center and second left click to select radius*/
// #include <GL/glut.h>
// #include <stdlib.h>
// #include <cmath>

// // Removed redefinition of M_PI as it is already defined in <cmath>

// int xc, yc, r;
// bool flag = true; //* this flag is for two taking two points
// // Function to implement Bresenham's circle drawing algorithm
// void drawCircle(int xc, int yc, int r)
// {
//   int x = 0, y = r;
//   int d = 3 - 2 * r;

//   glBegin(GL_POINTS);
//   while (x <= y)
//   {
//     glVertex2i(xc + x, yc + y);
//     glVertex2i(xc + y, yc + x);
//     glVertex2i(xc - x, yc + y);
//     glVertex2i(xc - y, yc + x);
//     glVertex2i(xc - x, yc - y);
//     glVertex2i(xc - y, yc - x);
//     glVertex2i(xc + x, yc - y);
//     glVertex2i(xc + y, yc - x);
//     if (d < 0)
//     {
//       d = d + 4 * x + 6;
//     }
//     else
//     {
//       d = d + 4 * (x - y) + 10;
//       y--;
//     }
//     x++;
//   }
//   glEnd();
// }

// void draw(int x, int y, int r)
// {

//   drawCircle(x, y, r);
//   drawCircle(x, y, r + 40);

//   float inc = 2 * 3.14 / 6;
//   for (int i = 0; i <= 6; i++)
//   {
//     int angleInc = inc * i;
//     int j = xc + (2 * r * cos(angleInc));
//     int k = yc + (2 * r * sin(angleInc));
//     drawCircle(j, k, r);
//   }

//   glFlush();
// }

// void myMouse(int button, int state, int x, int y)
// {
//   if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN)
//   {
//     if (flag == true)
//     {
//       xc = x;
//       yc = 600 - y;
//       flag = false;
//     }
//     else
//     {

//       r = abs(xc - x);
//       draw(xc, yc, r);
//       glutPostRedisplay();
//       flag = false;
//     }
//   }
// }

// void display()
// {
//   glClear(GL_COLOR_BUFFER_BIT);
//   glColor3f(0.0, 0.0, 0.0); // Set color to black
//   glutMouseFunc(myMouse);
//   glFlush();
// }
// void init()
// {
//   glClearColor(1.0, 1.0, 1.0, 0.0); // Set background color to white
//   glPointSize(2.0);                 // Set point size for better visibility
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   gluOrtho2D(0, 600, 0, 600); // Set the viewing area
// }

// int main(int argc, char **argv)
// {
//   glutInit(&argc, argv);
//   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//   glutInitWindowSize(600, 600);
//   glutInitWindowPosition(0, 0);
//   glutCreateWindow("bresenham's circle");
//   init();
//   glutDisplayFunc(display);
//   glutMainLoop();
//   return 0;
// }

//! chit one
// #include <GL/freeglut.h>
// #include <iostream>
// #include <cmath>
// using namespace std;

// int centerX = -1, centerY = -1, radius = -1;

// void axes()
// {
//   glBegin(GL_LINES);
//   glColor3f(0, 0, 0);
//   glVertex2i(300, 0);
//   glVertex2i(300, 600);
//   glVertex2i(0, 300);
//   glVertex2i(600, 300);
//   glEnd();
// }

// void plot(int xc, int yc, int x, int y)
// {
//   glVertex2i(xc + x, yc + y);
//   glVertex2i(xc - x, yc + y);
//   glVertex2i(xc + x, yc - y);
//   glVertex2i(xc - x, yc - y);
//   glVertex2i(xc + y, yc + x);
//   glVertex2i(xc - y, yc + x);
//   glVertex2i(xc + y, yc - x);
//   glVertex2i(xc - y, yc - x);
// }

// void circle(int xc, int yc, int r)
// {
//   int x = 0, y = r;
//   int p = 3 - 2 * r;

//   glBegin(GL_POINTS);
//   while (y >= x)
//   {
//     plot(xc, yc, x, y);
//     x++;
//     if (p < 0)
//       p += 4 * x + 6;
//     else
//     {
//       y--;
//       p += 4 * (x - y) + 10;
//     }
//   }
//   glEnd();
// }

// bool firstClick = true;

// void myMouse(int button, int state, int x, int y)
// {
//   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//   {
//     if (firstClick)
//     {
//       centerX = x;
//       centerY = 600 - y;
//       firstClick = false;
//     }
//     else
//     {
//       int x2 = x;
//       int y2 = 600 - y;
//       radius = sqrt((x2 - centerX) * (x2 - centerX) + (y2 - centerY) * (y2 - centerY));
//       firstClick = true;
//       glutPostRedisplay(); // Triggers display()
//     }
//   }
// }

// void init()
// {
//   glClearColor(1.0, 1.0, 1.0, 0.0);
//   gluOrtho2D(0, 600, 0, 600);
//   glPointSize(2);
// }

// void display()
// {
//   glClear(GL_COLOR_BUFFER_BIT);
//   axes();

//   if (centerX != -1 && radius != -1)
//   {
//     glColor3f(0, 0, 1);
//     circle(centerX, centerY, radius);
//   }

//   glFlush();
// }

// int main(int argc, char **argv)
// {
//   glutInit(&argc, argv);
//   glutInitDisplayMode(GLUT_SINGLE);
//   glutInitWindowSize(600, 600);
//   glutCreateWindow("Circle Drawing");
//   init();
//   glutDisplayFunc(display);
//   glutMouseFunc(myMouse);
//   glutMainLoop();
//   return 0;
// }
// //! draw circle on click
// #include <GL/freeglut.h>
// #include <vector>
// #include <iostream>
// #include <cmath>
// using namespace std;

// vector<pair<int, int>> circlePoints;

// void plot(int xc, int yc, int x, int y)
// {
//   glVertex2i(xc + x, yc + y);
//   glVertex2i(xc - x, yc + y);
//   glVertex2i(xc + x, yc - y);
//   glVertex2i(xc - x, yc - y);
//   glVertex2i(xc + y, yc + x);
//   glVertex2i(xc - y, yc + x);
//   glVertex2i(xc + y, yc - x);
//   glVertex2i(xc - y, yc - x);
// }

// void circle(int xc, int yc, int r) {
//   int p = 3 - 2 * r;
//   int x = 0;
//   int y = r;

//   glBegin(GL_POINTS);
//   plot(xc, yc, x, y);
//   while( y >= x) {
//     x++;

//     if(p < 0) {
//       p = p + 4 * x + 6;
//     }
//     else {
//       y--;
//       p = p + 4 * (x - y) + 10;
//     }
//     plot(xc, yc, x, y);
//   }
//   glEnd();
//   glFlush();
// }

// void init() {
//   glClearColor(1.0, 1.0, 1.0, 1.0);
//   gluOrtho2D(0, 600, 0, 600);
//   glPointSize(2);

// }
// void display() {
//   glClear(GL_COLOR_BUFFER_BIT);
//   glColor3i(0, 1, 1);
//   for(auto&i : circlePoints) {
//     circle(i.first, i.second, 50);
//   }
//   glFlush();
// }
// int clickX = 0, clickY = 0;
// void myMouse(int button, int state, int x, int y) {
//   if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//     int clickX = x;
//     int ClickY = 600 - y;
//     circlePoints.push_back({clickX, ClickY});
//     glutPostRedisplay();
//   }
// }

// int main(int argc, char** argv) {
//   glutInit(&argc, argv);
//   glutInitDisplayMode(GLUT_SINGLE);
//   glutInitWindowPosition(0, 0);
//   glutInitWindowSize(600, 600);
//   glutCreateWindow("Circle Drawing");
//   init();
//   glutDisplayFunc(display);
//   glutMouseFunc(myMouse);
//   glutMainLoop();
//   return 0;
// }

// !translation and Scalling

#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

void line(int x1, int y1, int x2, int y2)
{
  int sx = (x2 > x1) ? 1 : -1;
  int sy = (y2 > y1) ? 1 : -1;

  int p;
  int x = x1, y = y1;

  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  glBegin(GL_POINTS);
  glVertex2i(x, y);

  if (dx > dy)
  {

    p = 2 * dy - dx;
    for (int i = 0; i <= dx; i++)
    {
      glVertex2i(x, y);
      x += sx;
      if (p < 0)
      {
        p += 2 * dy;
      }
      else
      {
        y += sy;
        p += 2 * (dy - dx);
      }
    }
  }

  else
  {
    p = 2 * dx - dy;

    for(int i=0; i<= dy; i++) {
      
    }
  }
}