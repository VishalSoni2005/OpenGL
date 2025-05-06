#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

// Global variables
int xmin, xmax, ymin, ymax;
int outcode1[4], outcode2[4];
int xa, ya, xb, yb;

// Utility function to round float to int
int ROUND(float a) {
    return static_cast<int>(a + 0.5f);
}

// DDA Line Drawing
void DDALine(int xa, int ya, int xb, int yb) {
    int dx = xb - xa;
    int dy = yb - ya;
    int steps = max(abs(dx), abs(dy));

    float xinc = static_cast<float>(dx) / steps;
    float yinc = static_cast<float>(dy) / steps;

    float x = xa, y = ya;
    glVertex2i(ROUND(x), ROUND(y));
    for (int i = 0; i < steps; ++i) {
        x += xinc;
        y += yinc;
        glVertex2i(ROUND(x), ROUND(y));
    }
}

// Compute outcode for a point
void computeOutcode(int x, int y, int* outcode) {
    outcode[0] = (y > ymax) ? 1 : 0;
    outcode[1] = (y < ymin) ? 1 : 0;
    outcode[2] = (x > xmax) ? 1 : 0;
    outcode[3] = (x < xmin) ? 1 : 0;
}

// Get outcode as integer
int getOutcode(const int* outcode) {
    return (outcode[0] << 3) | (outcode[1] << 2) | (outcode[2] << 1) | outcode[3];
}

// Cohen-Sutherland Line Clipping
void lineClip() {
    int x1 = xa, y1 = ya;
    int x2 = xb, y2 = yb;
    bool accept = false;

    int dx = x2 - x1;
    int dy = y2 - y1;
    float slope = dx != 0 ? static_cast<float>(dy) / dx : 0;

    while (true) {
        computeOutcode(x1, y1, outcode1);
        computeOutcode(x2, y2, outcode2);

        int code1 = getOutcode(outcode1);
        int code2 = getOutcode(outcode2);

        if ((code1 | code2) == 0) {
            accept = true;
            break;
        } else if ((code1 & code2) != 0) {
            break;
        } else {
            int outcodeOut = code1 ? code1 : code2;
            int x = 0, y = 0;

            if (outcodeOut & 8) { // Top
                y = ymax;
                x = x1 + (1 / slope) * (ymax - y1);
            } else if (outcodeOut & 4) { // Bottom
                y = ymin;
                x = x1 + (1 / slope) * (ymin - y1);
            } else if (outcodeOut & 2) { // Right
                x = xmax;
                y = y1 + slope * (xmax - x1);
            } else if (outcodeOut & 1) { // Left
                x = xmin;
                y = y1 + slope * (xmin - x1);
            }

            if (outcodeOut == code1) {
                x1 = x;
                y1 = y;
            } else {
                x2 = x;
                y2 = y;
            }
        }
    }

    if (accept) {
        xa = x1;
        ya = y1;
        xb = x2;
        yb = y2;
    } else {
        xa = ya = xb = yb = -1;
    }
}

// Drawing function
void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    // Draw clipping rectangle (black)
    glColor3f(0.0, 0.0, 0.0);
    DDALine(xmin, ymin, xmax, ymin);
    DDALine(xmax, ymin, xmax, ymax);
    DDALine(xmax, ymax, xmin, ymax);
    DDALine(xmin, ymax, xmin, ymin);

    // Draw the clipped line (green)
    if (xa != -1 && ya != -1 && xb != -1 && yb != -1) {
        glColor3f(0.0, 1.0, 0.0);
        DDALine(xa, ya, xb, yb);
    }

    glEnd();
    glFlush();
}

// Main Function
int main(int argc, char** argv) {
    // User input
    cout << "Enter clipping window bottom-left (xmin ymin): ";
    cin >> xmin >> ymin;
    cout << "Enter clipping window top-right (xmax ymax): ";
    cin >> xmax >> ymax;

    cout << "Enter first point (x1 y1): ";
    cin >> xa >> ya;
    cout << "Enter second point (x2 y2): ";
    cin >> xb >> yb;

    computeOutcode(xa, ya, outcode1);
    computeOutcode(xb, yb, outcode2);

    int code1 = getOutcode(outcode1);
    int code2 = getOutcode(outcode2);

    cout << "Outcode P1: " << outcode1[0] << outcode1[1] << outcode1[2] << outcode1[3] << "\n";
    cout << "Outcode P2: " << outcode2[0] << outcode2[1] << outcode2[2] << outcode2[3] << "\n";

    if ((code1 | code2) == 0) {
        cout << "Line Accepted (Completely inside)\n";
    } else if ((code1 & code2) != 0) {
        cout << "Line Rejected (Completely outside)\n";
        xa = ya = xb = yb = -1;
    } else {
        cout << "Line Partially Accepted (Clipping applied)\n";
        lineClip();
    }

    // OpenGL Init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen–Sutherland Line Clipping - C++");

    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    gluOrtho2D(0, 640, 0, 480);

    glutDisplayFunc(Draw);
    glutMainLoop();

    return 0;
}

