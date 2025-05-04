#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;
int centerX, centerY, radiusX, radiusY, radius;
bool firstclick = false;
void drawCircle(int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 1 - r;
    while (x <= y)
    {
        glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
        glEnd();
        x++;
        if (d > 0)
        {
            y--;
            d = d + 2 * (x - y) + 1;
        }
        else
        {
            d = d + 2 * x + 1;
        }
    }
    glFlush();
}
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
    for (int i = 0; i <= step; i++)
    {
        displayPoint(x, y);
        x = x + Xinc;
        y = y + Yinc;
    }
    glFlush();
}
void init()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 600, 0, 600);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    SimpleLine(200, 200, 400, 200);
    SimpleLine(400, 200, 300, 400);
    SimpleLine(300, 400, 200, 200);
    drawCircle(300, 263, 60);
    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Midpoint Cicle - SIB64");
    init();
}
