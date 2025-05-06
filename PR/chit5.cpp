#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

const int WINDOW_SIZE = 600;
const int BOARD_SIZE = 8;

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x2 >= x1) ? 1 : -1;
    int sy = (y2 >= y1) ? 1 : -1;
    
    bool steep = dy > dx;
    if (steep) { 
        swap(x1, y1);
        swap(x2, y2);
        swap(dx, dy);
        swap(sx, sy);
    }
    
    int p = 2 * dy - dx;
    int x = x1, y = y1;
    
    glColor3f(0, 0, 0); 
    glBegin(GL_POINTS);
    
    for (int i = 0; i <= dx; i++) {
        if (steep) 
            glVertex2i(y, x);
        else 
            glVertex2i(x, y);
        
        x += sx;
        if (p >= 0) {
            y += sy;
            p -= 2 * dx;
        }
        p += 2 * dy;
    }
    
    glEnd();
    glFlush();
}

void drawChessboard(int boardSize) {
    int squareSize = WINDOW_SIZE / boardSize;


    for (int i = 0; i <= boardSize; i++) {
        drawLine(0, i * squareSize, boardSize * squareSize, i * squareSize); // Horizontal lines
        drawLine(i * squareSize, 0, i * squareSize, boardSize * squareSize); // Vertical lines
    }
    

    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            if ((row + col) % 2 == 0)
                glColor3f(1.0f, 1.0f, 1.0f); // White
            else
                glColor3f(0.0f, 0.0f, 0.0f); // Black

            glBegin(GL_POLYGON);
            glVertex2i(col * squareSize, row * squareSize);
            glVertex2i((col + 1) * squareSize, row * squareSize);
            glVertex2i((col + 1) * squareSize, (row + 1) * squareSize);
            glVertex2i(col * squareSize, (row + 1) * squareSize);
            glEnd();
        }
    }
}

void initOpenGL() {
    glClearColor(0.8, 0.8, 0.8, 1.0); 
    gluOrtho2D(0, WINDOW_SIZE, 0, WINDOW_SIZE);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawChessboard(BOARD_SIZE);
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("SIB22");
    
    initOpenGL();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
