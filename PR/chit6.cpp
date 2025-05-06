#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

// ==================== Common Variables ====================
int windowWidth = 800, windowHeight = 800;
int choice = 1; // 1 = Bezier, 2 = Koch

// ==================== Bezier Variables ====================
struct Point {
    double x, y;
};
Point controlPoints[3] = {{200, 200}, {300, 450}, {500, 150}};
int numControlPoints = 3;
int pointToBeChanged = 2;

// ==================== Bezier Functions ====================
void drawPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawControlPoints() {
    glColor3f(1.0, 1.0, 0.0);
    glPointSize(3);
    for (int i = 0; i < numControlPoints; i++) {
        drawPoint(controlPoints[i].x, controlPoints[i].y);
    }
}

int Factorial(int n) {
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        ans *= i;
    }
    return ans;
}

int Combination(int n, int k) {
    return Factorial(n) / (Factorial(k) * Factorial(n - k));
}

double bezierBlendingFunc(double t, int n, int k) {
    return Combination(n, k) * pow(t, k) * pow(1 - t, n - k);
}

void drawBezierCurve() {
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(1);
    for (double t = 0.0; t <= 1.0; t += 0.001) {
        double x = 0, y = 0;
        for (int i = 0; i < numControlPoints; i++) {
            x += bezierBlendingFunc(t, numControlPoints - 1, i) * controlPoints[i].x;
            y += bezierBlendingFunc(t, numControlPoints - 1, i) * controlPoints[i].y;
        }
        drawPoint(x, y);
    }
}

// ==================== Koch Functions ====================
GLfloat oldx = -0.7, oldy = 0.5;

void drawKoch(GLfloat dir, GLfloat len, GLint iter) {
    GLdouble dirRad = 0.0174533 * dir;
    GLfloat newX = oldx + len * cos(dirRad);
    GLfloat newY = oldy + len * sin(dirRad);

    if (iter == 0) {
        glVertex2f(oldx, oldy);
        glVertex2f(newX, newY);
        oldx = newX;
        oldy = newY;
    } else {
        iter--;
        drawKoch(dir, len, iter);
        dir += 60.0;
        drawKoch(dir, len, iter);
        dir -= 120.0;
        drawKoch(dir, len, iter);
        dir += 60.0;
        drawKoch(dir, len, iter);
    }
}

// ==================== Display Function ====================
void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (choice == 1) {
        drawControlPoints();
        drawBezierCurve();
    } else if (choice == 2) {
        glBegin(GL_LINES);
        glColor3f(0.0, 1.0, 1.0);
        oldx = -0.7; oldy = 0.5;
        drawKoch(0.0, 0.015, 4);
        drawKoch(-120.0, 0.015, 4);
        drawKoch(120.0, 0.015, 4);
        glEnd();
    }
    glFlush();
}

// ==================== Other Input Functions ====================
void myKeyboard(unsigned char key, int xMouse, int yMouse) {
    if (choice == 1 && isdigit(key)) {
        pointToBeChanged = key - '1';
    }
}

void myMouse(int button, int action, int xMouse, int yMouse) {
    if (choice == 1 && button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
        controlPoints[pointToBeChanged].x = xMouse;
        controlPoints[pointToBeChanged].y = 800 - yMouse;
        myDisplay();
    }
}

// ==================== Initialization ====================
void Init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Normalized for Koch
    if (choice == 1)
        gluOrtho2D(0, windowWidth, 0, windowHeight); // Window coords for Bezier
}

// ==================== Main Function ====================
int main(int argc, char** argv) {
    cout << "Choose Curve to Display:\n";
    cout << "1. Bezier Curve\n";
    cout << "2. Koch Curve\n";
    cout << "Enter choice: ";
    cin >> choice;

    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bezier and Koch Curve Viewer");

    Init();
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}

