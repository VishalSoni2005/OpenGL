// //* bresenham line and circle drawing algo
// #include <GL/freeglut.h>
// #include <iostream>
// using namespace std;

// void plotCirclePoints(int xc, int yc, int x, int y)
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

// void drawCircle(int xc, int yc, int r)
// {
//   int x = 0, 
//   y = r;

//   int p = 3 - 2 * r;

//   glBegin(GL_POINTS);
//   while (x <= y)
//   {
//     plotCirclePoints(xc, yc, x, y);
//     x++;
//     if (p < 0)
//       p = p + 4 * x + 6;
//     else
//     {
//       y--;
//       p = p + 4 * (x - y) + 10;
//     }
//   }
//   glEnd();
//   glFlush();
// }

// void line(int x1, int y1, int x2, int y2)
// {
//   int dx = abs(x2 - x1);
//   int dy = abs(y2 - y1);

//   int p;
//   int sx = (x2 > x1) ? 1 : -1;
//   int sy = (y2 > y1) ? 1 : -1;

//   int x = x1;
//   int y = y1;

//   glBegin(GL_POINTS);

//   if (dx > dy)
//   {
//     p = 2 * dy - dx;

//     for (int i = 0; i <= dx; i++)
//     {
//       glVertex2i(x, y);
//       x += sx;

//       if (p >= 0)
//       {
//         y += sy;
//         p += 2 * (dy - dx);
//       }
//       else
//         p += 2 * dy;
//     }
//   }

//   else
//   {
//     p = 2 * dx - dy;
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

// void init()
// { //* CCOPS
//   glClearColor(0, 0, 0, 1);
//   glColor3f(1, 1, 1);
//   gluOrtho2D(0, 600, 0, 600);
//   glPointSize(2);
// }

// void display()
// {
//   glClear(GL_COLOR_BUFFER_BIT);
//   drawCircle(300, 300, 100);

//   line(0, 0, 600, 600);
//   glFlush();
// }

// int main(int argc, char **argv)
// {
//   //! IDPSC
//   glutInit(&argc, argv);
//   glutInitDisplayMode(GLUT_SINGLE);
//   glutInitWindowPosition(0, 0);
//   glutInitWindowSize(600, 600);
//   glutCreateWindow("Todays practice");

//   init();
//   glutDisplayFunc(display);
//   glutMainLoop();
//   return 0;
// }

// left click to select vertices of polygon , after that right click and choose option to proceed
#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

struct Point
{
  int xc;
  int yc;
} p[10];
int i = 0;
int n;

bool flag = true;
int tx, ty, sx, sy;
struct Point translated_p[10];
struct Point scaled_p[10];
bool translated = false;
bool scaled = false;

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
  float step;
  float dx = x2 - x1;
  float dy = y2 - y1;

  if (abs(dx) > abs(dy))
  {
    step = abs(dx);
  }
  else
  {
    step = abs(dy);
  }

  float Xinc = dx / step;
  float Yinc = dy / step;
  float x = x1;
  float y = y1;

  for (int j = 0; j <= step; j++)
  {
    displayPoint(round(x), round(y));
    x = x + Xinc;
    y = y + Yinc;
  }
  glFlush();
}

void drawPolygon(struct Point points[], int num_points)
{

  glPointSize(1.0);
  int j;
  for (j = 0; j < num_points - 1; j++)
  {
    SimpleLine(points[j].xc, points[j].yc, points[j + 1].xc, points[j + 1].yc);
  }

  SimpleLine(points[j].xc, points[j].yc, points[0].xc, points[0].yc);

  glEnd();
  glFlush();
}

void myDisplay()
{
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0f, 0.0f, 0.0f);
  SimpleLine(0, 300, 600, 300);
  SimpleLine(300, 0, 300, 600);

  if (!flag && n > 0)
  {
    drawPolygon(p, n); // Draw original

    if (translated)
    {
      drawPolygon(translated_p, n); // draw translated polygon
    }
    if (scaled)
    {
      drawPolygon(scaled_p, n); // draw scaled polygon
    }
  }
  glFlush();
}

void translate(int tx, int ty)
{
  for (int j = 0; j < n; j++)
  {
    translated_p[j].xc = p[j].xc + tx;
    translated_p[j].yc = p[j].yc + ty;
  }
  translated = true;
  glutPostRedisplay();
}

void scaling(int sx, int sy)
{
  for (int j = 0; j < n; j++)
  {
    scaled_p[j].xc = round(p[j].xc * sx);
    scaled_p[j].yc = round(p[j].yc * sy);
  }
  scaled = true;
  glutPostRedisplay();
}

void menu(int choice)
{
  switch (choice)
  {
  case 1: // Translate
    cout << "\n enter tx and ty: ";
    cin >> tx >> ty;
    translate(tx, ty);
    break;
  case 2: // Scaling
    cout << "\n enter sx and sy: ";
    cin >> sx >> sy;
    scaling(sx, sy);
    break;
  case 3:
    exit(0);
  }
  glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    if (flag == true && i < 10)
    {
      p[i].xc = x;
      p[i].yc = 600 - y;
      displayPoint(x, 600 - y);
      i++;
      glFlush();
    }
  }
  else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {
    if (flag == true && i >= 3)
    {
      n = i;
      // Initialize translated and scaled polygons with the original
      for (int j = 0; j < n; j++)
      {
        translated_p[j] = p[j];
        scaled_p[j] = p[j];
      }
      drawPolygon(p, n); // Draw the initial polygon
      flag = false;
      translated = false; // Reset transformation flags
      scaled = false;
      glutCreateMenu(menu);
      glutAddMenuEntry("1. Translate", 1);
      glutAddMenuEntry("2. Scaling", 2);
      glutAddMenuEntry("3. Exit", 3);
      glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
    else if (flag == true)
    {
      cout << "Please select at least 3 vertices to form a polygon." << endl;
    }
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Original and Transformed Polygon");
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 600, 0, 600);
  glutDisplayFunc(myDisplay);
  glutMouseFunc(myMouse);
  glutMainLoop();
  return (0);
}