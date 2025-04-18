#include <GL/freeglut.h>
#include <math.h>
using namespace std;

void displayPixel(float x, float y)
{
  glPointSize(4);
  glColor3f(0.3, 1, 0.6);
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void simpleLine(float x1, float y1, float x2, float y2)
{

  // step 1
  float dx = x2 - x1;
  float dy = y2 - y1;

  // setp 2
  float steps = (abs(dx) > abs(dy)) ? dx : dy;

  // step 3;
  float xInc = dx / steps;
  float yInc = dy / steps;

  // step 4;
  float x = x1;
  float y = y1;

  for (int i = 0; i < steps; i++)
  {
    displayPixel(round(x), round(y));
    x += xInc;
    y += yInc;
  }
}

void dotedLine(float x1, float y1, float x2, float y2)
{

  // step 1
  float dx = x2 - x1;
  float dy = y2 - y1;

  // setp 2
  float steps = (abs(dx) > abs(dy)) ? dx : dy;

  // step 3;
  float xInc = dx / steps;
  float yInc = dy / steps;

  // step 4;
  float x = x1;
  float y = y1;

  displayPixel(round(x), round(y));
  for (int i = 0; i < steps; i++)
  {
    x += xInc;
    y += yInc;
    if (i % 6 == 0)
    {
      displayPixel(round(x), round(y));
    }
  }
}

void thickLine(float x1, float y1, float x2, float y2)
{

  // step 1
  float dx = x2 - x1;
  float dy = y2 - y1;

  // setp 2
  float steps = (abs(dx) > abs(dy)) ? dx : dy;

  // step 3;
  float xInc = dx / steps;
  float yInc = dy / steps;

  // step 4;
  float x = x1;
  float y = y1;

  for (int i = 0; i <= steps; i++)
  {
    glPointSize(20);
    glColor3f(0, 0.6, 1);
    glBegin(GL_POINTS);
    glVertex2i(round(x), round(y));
    glEnd();
    x += xInc;
    y += yInc;
  }
}

void dashLine(float x1, float y1, float x2, float y2)
{
  int count = 1;

  // step 1
  float dx = x2 - x1;
  float dy = y2 - y1;

  // setp 2
  float steps = (abs(dx) > abs(dy)) ? dx : dy;

  // step 3;
  float xInc = dx / steps;
  float yInc = dy / steps;

  // step 4;
  float x = x1;
  float y = y1;
  displayPixel(x, y);

  for (int i = 0; i <= steps; i++)
  {
    x += xInc;
    y += yInc;
    count++;
    if (count <= 10)
      displayPixel(round(x), round(y));
    else if (count >= 10 and count < 15)
      continue;
    else
    {
      count = 1;
      continue;
    }
  }
}

void init()
{
  glClearColor(0.0, 0.0, 0.0, 1.0); // black background
  gluOrtho2D(0, 600, 0, 400);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // simpleLine(10, 10, 300, 300);
  // dotedLine(10, 10, 300, 300);
  // thickLine(10, 10, 300, 300);
  dashLine(10, 10, 300, 300);

  glFlush();
}
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(400, 400);
  glutCreateWindow("DDA");

  init();

  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
