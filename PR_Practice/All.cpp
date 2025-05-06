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
// #include <GL/glut.h>
// #include <cmath>
// #include <iostream>
// using namespace std;

// int x[10], y[10];
// int i = 0, n;
// bool flag = true;

// void displayPoint(int x, int y)
// {
//   glColor3f(0, 0, 1);
//   glPointSize(2);
//   glBegin(GL_POINTS);
//   glVertex2i(x, y);
//   glEnd();
// }

// void SimpleLine(float x1, float y1, float x2, float y2)
// {
//   float dx = x2 - x1;
//   float dy = y2 - y1;
//   float step = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

//   float Xinc = dx / step;
//   float Yinc = dy / step;
//   float x = x1;
//   float y = y1;

//   for (int i = 0; i <= step; i++)
//   {
//     displayPoint(round(x), round(y));
//     x += Xinc;
//     y += Yinc;
//   }
//   glFlush();
// }

// void drawCircle(int xc, int yc, int radius)
// {
//   int x = 0, y = radius;
//   int p = 3 - 2 * radius;

//   while (x <= y)
//   {
//     glBegin(GL_POINTS);
//     glVertex2i(xc + x, yc + y);
//     glVertex2i(xc + y, yc + x);
//     glVertex2i(xc - x, yc + y);
//     glVertex2i(xc - y, yc + x);
//     glVertex2i(xc - x, yc - y);
//     glVertex2i(xc - y, yc - x);
//     glVertex2i(xc + x, yc - y);
//     glVertex2i(xc + y, yc - x);
//     glEnd();

//     if (p < 0)
//       p += 4 * x++ + 6;
//     else
//       p += 4 * (x++ - y--) + 10;
//   }
//   glFlush();
// }

// void drawPolygon(int x[], int y[], int n)
// {
//   for (int j = 0; j < n - 1; j++)
//   {
//     SimpleLine(x[j], y[j], x[j + 1], y[j + 1]);
//   }
//   SimpleLine(x[n - 1], y[n - 1], x[0], y[0]);
//   glFlush();
// }

// void myDisplay()
// {
//   glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
//   glClear(GL_COLOR_BUFFER_BIT);
// }

// void myMouse(int button, int state, int mx, int my)
// {
//   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag)
//   {
//     x[i] = mx;
//     y[i] = 600 - my;
//     i++;
//   }
//   else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && flag)
//   {
//     n = i;
//     drawPolygon(x, y, n);

//     double a = sqrt(pow(x[2] - x[1], 2.0) + pow(y[2] - y[1], 2.0));
//     double b = sqrt(pow(x[2] - x[0], 2.0) + pow(y[2] - y[0], 2.0));
//     double c = sqrt(pow(x[1] - x[0], 2.0) + pow(y[1] - y[0], 2.0));

//     double xi = (a * x[0] + b * x[1] + c * x[2]) / (a + b + c);
//     double yi = (a * y[0] + b * y[1] + c * y[2]) / (a + b + c);

//     double area = 0.5 * abs(x[0] * (y[1] - y[2]) + x[1] * (y[2] - y[0]) + x[2] * (y[0] - y[1]));
//     double s = (a + b + c) / 2.0;
//     double r = area / s;

//     drawCircle(xi, yi, r);
//     cout << "Incenter: (" << xi << ", " << yi << "), Radius: " << r << endl;

//     flag = false;
//     glFlush();
//   }
// }

// int main(int argc, char **argv)
// {
//   glutInit(&argc, argv);
//   glutInitWindowPosition(0, 0);
//   glutInitWindowSize(600, 600);
//   glutCreateWindow("Triangle with Inscribed Circle");
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   gluOrtho2D(0, 600, 0, 600);

//   glutDisplayFunc(myDisplay);
//   glutMouseFunc(myMouse);

//   glutMainLoop();
//   return 0;
// }

//! TRANSFORMATION AND TRANSLATION
// #include <GL/glut.h>
// #include <iostream>
// using namespace std;

// // Structure for 2D Point
// struct Point2D
// {
//   int x;
//   int y;
// };

// // Define original triangle points
// Point2D originalTriangle[3] = {
//     {200, 200},
//     {300, 400},
//     {400, 200}};

// // Translated triangle
// Point2D translatedTriangle[3];

// // Translation values
// int tx = 100, ty = 50; // You can change these

// // Function to clear screen and draw coordinate axes
// void clearScreenWithAxes()
// {
//   glClear(GL_COLOR_BUFFER_BIT);

//   // Draw axes in gray
//   glColor3f(0.8, 0.8, 0.8);
//   glBegin(GL_LINES);
//   glVertex2i(300, 0);
//   glVertex2i(300, 600); // Y-axis
//   glVertex2i(0, 300);
//   glVertex2i(600, 300); // X-axis
//   glEnd();
// }

// // Draw polygon
// void drawPolygon(Point2D points[], int count, float r, float g, float b)
// {
//   glColor3f(r, g, b);
//   glBegin(GL_LINE_LOOP);
//   for (int i = 0; i < count; i++)
//   {
//     glVertex2i(points[i].x, points[i].y);
//   }
//   glEnd();
// }

// // Display callback
// void display()
// {
//   clearScreenWithAxes();

  // Draw original triangle in black
//   drawPolygon(originalTriangle, 3, 0, 0, 0);

//   // Apply translation
//   for (int i = 0; i < 3; ++i)
//   {
//     translatedTriangle[i].x = originalTriangle[i].x + tx;
//     translatedTriangle[i].y = originalTriangle[i].y + ty;
//   }

//   // Draw translated triangle in red
//   drawPolygon(translatedTriangle, 3, 1, 0, 0);

//   glFlush();
// }

// // Main function
// int main(int argc, char **argv)
// {
//   glutInit(&argc, argv);
//   glutInitWindowSize(600, 600);
//   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//   glutCreateWindow("Fixed Triangle - Translation");

//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   gluOrtho2D(0, 600, 0, 600); // Set 2D coordinate system

//   glClearColor(1, 1, 1, 1); // White background
//   glutDisplayFunc(display);
//   glutMainLoop();
//   return 0;
// }

//! translation and scalling
// #include <iostream>
// #include <GL/freeglut.h>
// using namespace std;

// // Define a 2D point structure
// struct Point2D
// {
//   float x;
//   float y;
// };

// // Original triangle vertices
// Point2D originalTriangle[3] = {
//     {200, 200},
//     {300, 400},
//     {400, 200}};

// // Transformed triangle for translation and scaling
// Point2D translatedTriangle[3];
// Point2D scaledTriangle[3];

// // Translation offsets
// float tx = 100, ty = 50;

// // Scaling factors
// float sx = 1.5, sy = 1.5;

// // Draw triangle using given color
// void drawPolygon(Point2D points[], float r, float g, float b)
// {
//   glColor3f(r, g, b);
//   glBegin(GL_LINE_LOOP);
//   for (int i = 0; i < 3; i++)
//   {
//     glVertex2f(points[i].x, points[i].y);
//   }
//   glEnd();
// }

// // Draw X and Y axes
// void drawAxis()
// {
//   glColor3f(0, 1, 0.2); // Green axes
//   glBegin(GL_LINES);
//   glVertex2i(300, 0);
//   glVertex2i(300, 600); // Y-axis
//   glVertex2i(0, 300);
//   glVertex2i(600, 300); // X-axis
//   glEnd();
// }

// // OpenGL init
// void init()
// {
//   glClearColor(1, 1, 1, 1); // White background
//   glPointSize(2);
//   gluOrtho2D(0, 600, 0, 600); // Set orthographic projection
// }

// // Display function
// void display()
// {
//   glClear(GL_COLOR_BUFFER_BIT);

//   drawAxis(); // Draw coordinate axes

//   // Draw original triangle in black
//   drawPolygon(originalTriangle, 0, 0, 0);

//   // Translation only (red)
//   for (int i = 0; i < 3; i++)
//   {
//     translatedTriangle[i].x = originalTriangle[i].x + tx;
//     translatedTriangle[i].y = originalTriangle[i].y + ty;
//   }
//   drawPolygon(translatedTriangle, 1, 0, 0);

//   // Translation + Scaling (blue)
//   for (int i = 0; i < 3; i++)
//   {
//     scaledTriangle[i].x = originalTriangle[i].x * sx ;
//     scaledTriangle[i].y = originalTriangle[i].y * sy ;
//   }
//   drawPolygon(scaledTriangle, 0, 0, 1);

//   glFlush();
// }

// // Main entry point
// int main(int argc, char **argv)
// {
//   glutInit(&argc, argv);
//   glutInitDisplayMode(GLUT_SINGLE);
//   glutInitWindowSize(600, 600);
//   glutInitWindowPosition(0, 0);
//   glutCreateWindow("Translation and Scaling on Triangle");

//   init();
//   glutDisplayFunc(display);
//   glutMainLoop();
//   return 0;
// }

//! translation and rotation
// #include <GL/freeglut.h>
// #include <iostream>
// #include <cmath>
//     using namespace std;

// struct Point2D
// {
//   float x;
//   float y;
// };

// // Original triangle vertices
// Point2D originalTriangle[3] = {
//     {200, 200},
//     {300, 400},
//     {400, 200}};

// // Rotated triangle vertices
// Point2D rotatedTriangle[3];

// // Rotation angle in degrees
// float angle = 45.0;

// // Convert degrees to radians
// float degToRad(float degree)
// {
//   return degree * 3.14  / 180.0;
// }

// // Draw triangle with specified color
// void drawTriangle(Point2D points[], float r, float g, float b)
// {
//   glColor3f(r, g, b);
//   glBegin(GL_LINE_LOOP);
//   for (int i = 0; i < 3; i++)
//   {
//     glVertex2f(points[i].x, points[i].y);
//   }
//   glEnd();
// }

// // Compute centroid of triangle
// Point2D getCentroid(Point2D tri[])
// {
//   Point2D c;
//   c.x = (tri[0].x + tri[1].x + tri[2].x) / 3.0;
//   c.y = (tri[0].y + tri[1].y + tri[2].y) / 3.0;
//   return c;
// }

// void init()
// {
//   glClearColor(1, 1, 1, 1); // white background
//   glPointSize(2);
//   gluOrtho2D(0, 600, 0, 600);
// }

// void drawAxis()
// {
//   glColor3f(0, 1, 0.2); // green axes
//   glBegin(GL_LINES);
//   glVertex2i(300, 0);
//   glVertex2i(300, 600); // Y-axis
//   glVertex2i(0, 300);
//   glVertex2i(600, 300); // X-axis
//   glEnd();
// }

// void display()
// {
//   glClear(GL_COLOR_BUFFER_BIT);

//   drawAxis();

//   // Draw original triangle (black)
//   drawTriangle(originalTriangle, 0, 0, 0);

//   // Compute centroid
//   Point2D centroid = getCentroid(originalTriangle);

//   // Calculate rotated points
//   float rad = degToRad(angle);
//   for (int i = 0; i < 3; i++)
//   {
//     float x = originalTriangle[i].x - centroid.x;
//     float y = originalTriangle[i].y - centroid.y;

//     rotatedTriangle[i].x = centroid.x + (x * cos(rad) - y * sin(rad));
//     rotatedTriangle[i].y = centroid.y + (x * sin(rad) + y * cos(rad));
//   }

//   // Draw rotated triangle (red)
//   drawTriangle(rotatedTriangle, 1, 0, 0);

//   glFlush();
// }

// int main(int argc, char **argv)
// {
//   glutInit(&argc, argv);
//   glutInitDisplayMode(GLUT_SINGLE);
//   glutInitWindowPosition(0, 0);
//   glutInitWindowSize(600, 600);
//   glutCreateWindow("Triangle Rotation Around Centroid");

//   init();
//   glutDisplayFunc(display);
//   glutMainLoop();
//   return 0;
// }

//! 4 ( MOUSE CLICK CIRCLE )
#include <GL/freeglut.h>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;


vector<pair<int, int> >circleCordinates;

void line(int x1, int y1, int x2, int y2)
{
  int sx = (x2 > x1) ? 1 : -1;
  int sy = (y2 > y1) ? 1 : -1;

  int dy = abs(y2 - y1);
  int dx = abs(x2 - x1);

  int p;

  int x = x1, y = y1;

  glBegin(GL_POINTS);
  glVertex2i(x, y); // Plot point

  if (dx > dy)
  {

    p = 2 * dy - dx;
    for (int i = 0; i <= dx; i++)
    {
      glVertex2i(x, y); // Plot point
      x += sx;
      if (p < 0)
        p += 2 * dy;
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
    for (int i = 0; i <= dy; i++)
    {
      glVertex2i(x, y); // Plot point
      y += sy;
      if (p < 0)
        p += 2 * dx;
      else
      {
        x += sx;
        p += 2 * (dx - dy);
      }
    }
  }

  glEnd();
  glFlush();
}

void plotCirclePoint(int xc, int yc, int x, int y)
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

void circle(int xc, int yc, int r)
{
  int x = 0, y = r;
  int d = 3 - 2 * r;

  glBegin(GL_POINTS);
  plotCirclePoint(xc, yc, x, y);

  while (y >= x)
  {
    x++;
    plotCirclePoint(xc, yc, x, y);
    if (d < 0)
      d += 4 * x + 6;
    else
    {
      y--;
      d += 4 * (x - y) + 10;
    }
  }

  glEnd();
  glFlush();
}

void init()
{
  glClearColor(1, 1, 1, 1); // white background
  glPointSize(2);
  gluOrtho2D(0, 600, 0, 600);
}

void drawAxis()
{
  glColor3f(0, 1, 0.2); // green axes
  glBegin(GL_LINES);
  glVertex2i(300, 0);
  glVertex2i(300, 600); // Y-axis
  glVertex2i(0, 300);
  glVertex2i(600, 300); // X-axis
  glEnd();
}

int clickX = 0, clickY = 0; // Declare variables to store mouse click coordinates

void mousefn(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    clickX = x;
    clickY = 600 - y;    // Flip y to match OpenGL coords
    circleCordinates.push_back({ clickX, clickY});
    glutPostRedisplay(); // Ask //GLUT to call display()
  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // if(clickX > 0)
  //   circle(clickX, clickY, 200);

  for(auto&i : circleCordinates) {
    circle(i.first, i.second, 50);
  }
  drawAxis();

  glFlush();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(600, 600);
  glutCreateWindow("4");

  init();
  glutDisplayFunc(display);
  glutMouseFunc(mousefn);
  glutMainLoop();
  return 0;
}
