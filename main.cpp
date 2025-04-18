#include <GL/glut.h>
#include <cmath>

// Set pixel using OpenGL
void setPixel(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

// Bresenham's Line Algorithm
void drawLine(int x1, int y1, int x2, int y2)
{
  int dx = abs(x2 - x1), dy = abs(y2 - y1);
  int sx = (x2 > x1) ? 1 : -1;
  int sy = (y2 > y1) ? 1 : -1;
  int err = dx - dy;

  while (true)
  {
    setPixel(x1, y1);
    if (x1 == x2 && y1 == y2)
      break;
    int e2 = 2 * err;
    if (e2 > -dy)
    {
      err -= dy;
      x1 += sx;
    }
    if (e2 < dx)
    {
      err += dx;
      y1 += sy;
    }
  }
}

// Bresenham's Circle Algorithm
void drawCircle(int xc, int yc, int r)
{
  int x = 0, y = r;
  int d = 3 - 2 * r;
  while (y >= x)
  {
    setPixel(xc + x, yc + y);
    setPixel(xc - x, yc + y);
    setPixel(xc + x, yc - y);
    setPixel(xc - x, yc - y);
    setPixel(xc + y, yc + x);
    setPixel(xc - y, yc + x);
    setPixel(xc + y, yc - x);
    setPixel(xc - y, yc - x);
    x++;
    if (d > 0)
    {
      y--;
      d = d + 4 * (x - y) + 10;
    }
    else
    {
      d = d + 4 * x + 6;
    }
  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // Left wall (main rectangle)
  drawLine(100, 100, 100, 300); // Left vertical
  drawLine(100, 300, 200, 300); // Top horizontal
  drawLine(200, 300, 200, 100); // Right vertical
  drawLine(100, 100, 200, 100); // Bottom horizontal

  // Right rectangle
  drawLine(200, 300, 350, 300); // Top
  drawLine(350, 300, 350, 100); // Right
  drawLine(350, 100, 200, 100); // Bottom

  // Triangle roof
  drawLine(100, 300, 150, 375); // Left slope
  drawLine(150, 375, 200, 300); // Right slope

  // Circle window in roof
  drawCircle(150, 335, 15); // Centered in triangle

  // Door
  drawLine(120, 100, 120, 200); // Left door
  drawLine(120, 200, 150, 200); // Top door
  drawLine(150, 200, 150, 100); // Right door

  glFlush();
}

void init()
{
  glClearColor(1.0, 1.0, 1.0, 1.0); // Background: white
  glColor3f(0.0, 0.0, 0.0);         // Drawing color: black
  glPointSize(1.0);                 // Pixel size
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0, 500, 0, 500); // Coordinate system
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Accurate House Drawing using Bresenham Algorithms");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
