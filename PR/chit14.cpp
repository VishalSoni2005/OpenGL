/* Chit No.14
Instructions: First left-click to select center, second left-click to select radius */
#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

int xc, yc, r;
bool clicked_once = false;
bool draw_flag = false;

// Function to draw one circle using Bresenham's algorithm
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
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    glEnd();
}

// Draw the Flower of Life (center + 4 surrounding circles)
void drawFlower() {
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(xc, yc, r);                 // Center
    drawCircle(xc - 2 * r, yc, r);         // Left
    drawCircle(xc - r, yc + r, r);         // Top Left
    drawCircle(xc - r, yc - r, r);         // Bottom Left
    glFlush();
}

// Mouse callback
void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!clicked_once) {
            xc = x;
            yc = 600 - y;  // Flip y-axis
            clicked_once = true;
        } else {
            r = abs(x - xc);
            draw_flag = true;
            glutPostRedisplay();  // Trigger display() redraw
            clicked_once = false; // Reset for next circle if needed
        }
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (draw_flag) {
        drawFlower();
    }
    glFlush();
}

// Initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // White background
    glPointSize(2.0);                 // Bigger points for visibility
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);       // Coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Flower of Life");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);  // Set mouse callback here
    glutMainLoop();
    return 0;
}

