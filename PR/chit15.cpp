/* Chit No.15
Instructions: Left-click once to select the center, and again to select radius */
#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

int xc, yc, r;
bool firstClick = true;
bool draw_flag = false;

// Bresenham's circle drawing algorithm
void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    glBegin(GL_POINTS);
    while (x <= y) {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc - y, yc - x);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc + y, yc - x);
        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    glEnd();
}

// Draw central, outer ring, and surrounding pattern
void drawPattern() {
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(xc, yc, r);           // Central circle
    drawCircle(xc, yc, r + 40);      // Outer ring

    // 6 surrounding circles spaced equally
    float angleIncrement = 2 * M_PI / 6;
    for (int i = 0; i < 6; ++i) {
        float angle = i * angleIncrement;
        int x = xc + round(r * 2 * cos(angle));
        int y = yc + round(r * 2 * sin(angle));
        drawCircle(x, y, r);
    }
    glFlush();
}

// Mouse click handling
void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (firstClick) {
            xc = x;
            yc = 600 - y;
            firstClick = false;
        } else {
            r = abs(x - xc);
            draw_flag = true;
            glutPostRedisplay();   // Trigger redraw
            firstClick = true;     // Reset for next use
        }
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (draw_flag) {
        drawPattern();
    }
    glFlush();
}

// Initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    glPointSize(2.0);                // Larger points for visibility
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);      // 2D projection
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Circle - Chit 15");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);  // Set mouse callback here, not in display()
    glutMainLoop();
    return 0;
}

