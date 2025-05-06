#include <iostream>
#include <GL/glut.h>

using namespace std;

// Window dimensions
const int windowWidth = 600, windowHeight = 600;

// Color definitions
float intColor[3] = {1.0, 1.0, 1.0}; // Initial color
float fillColorFlood[3] = {1.0, 0.0, 0.0}; // Flood fill color
float fillColorBoundary[3] = {0.0, 0.0, 1.0}; // Boundary fill color
float borderColor[3] = {1.0, 0.0, 0.0}; // Boundary color

int fillMode = 1; // 1 for Flood Fill, 2 for Boundary Fill

// Function to set a pixel color
void setPixel(int x, int y, float color[3]) {
    glColor3fv(color);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Function to draw a polygon (rectangle)
void drawPolygon(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glEnd();
    glFlush();
}

// Function to check and apply Flood Fill
void floodFill(int x, int y, float oldColor[3], float newColor[3]) {
    float color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
    if (color[0] == oldColor[0] && color[1] == oldColor[1] && color[2] == oldColor[2]) {
        setPixel(x, y, newColor);
        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
    }
}

// Function to check and apply Boundary Fill
void boundaryFill(int x, int y, float fillColor[3], float borderColor[3]) {
    float color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
    if ((color[0] != borderColor[0] || color[1] != borderColor[1] || color[2] != borderColor[2]) &&
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {
        setPixel(x, y, fillColor);
        boundaryFill(x + 1, y, fillColor, borderColor);
        boundaryFill(x - 1, y, fillColor, borderColor);
        boundaryFill(x, y + 1, fillColor, borderColor);
        boundaryFill(x, y - 1, fillColor, borderColor);
    }
}

// Mouse click function
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int newY = windowHeight - y; // Adjust for OpenGL coordinates
        if (fillMode == 1) {
            floodFill(x, newY, intColor, fillColorFlood);
        } else if (fillMode == 2) {
            boundaryFill(x, newY, fillColorBoundary, borderColor);
        }
    }
    glFlush();
}

// Keyboard function to choose fill mode
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'f':
            fillMode = 1;
            break;
        case 'b':
            fillMode = 2;
            break;
    }
    glutMouseFunc(mouse);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    drawPolygon(150, 250, 300, 400);
    glFlush();
}

// OpenGL initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Flood Fill and Boundary Fill Algorithm  ");
    
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    float color[3];
    glReadPixels(200, 200, 1, 1, GL_RGB, GL_FLOAT, color);
    cout << "Pixel Color at (" << 200 << ", " << 200 << "): " << color[0] << ", " << color[1] << ", " << color[2] << endl;

    cout << "Press 'f' for Flood Fill and 'b' for Boundary Fill" << endl;
    glutMainLoop();
    return 0;
}
