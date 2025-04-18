//! practical_2 { DDA }
#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

void drawPixel(float x, float y) {
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void drawLineDDA( float x1, float y1, float x2, float y2) {

  // step 1 : calculating dx, dy
  float dx = x2 - x1;
  float dy = y2 - y1;

  // step 2 : calculate steps
  float steps = ( abs(dx) > abs(dy) ) ? abs(dx) : abs(dy);

  // step 3 : calculating increments
  float xInc = dx / steps;
  float yInc = dy / steps;

  float x = x1;
  float y = y1;

  // step 4 : loop ploting
  for(int i=0; i<steps; i++) {
    drawPixel(round(x), round(y));
    x += xInc;
    y += yInc;

  }
}

void init() { // initial state of window
  glClearColor(0.0, 0.0, 0.0, 0.0); //black
  // glMatrixMode(GL_PROJECTION);
  glPointSize(2.0);
  glColor3f(1, 1, 1); //Setting Drawing Color to white
  gluOrtho2D(0, 600, 0, 600);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1, 1, 1); // Setting Drawing Color to white
  drawLineDDA(50, 50, 300, 300); // Example: Draw line from (50, 50) to (300, 300)
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("DDA Practical 2");
  init();

  glutDisplayFunc(display);
  glutMainLoop();
  return 0;

}






















// //! Practical_1 SIB64
// #include <GL/freeglut.h>
// #include <iostream>
// using namespace std;

// void initialize()
// {
//     glClearColor(1, 1, 1, 1);     //* Set the background color to white
//     glClear(GL_COLOR_BUFFER_BIT); //* glClear() actually clears the screen with the specified color.
//     gluOrtho2D(0, 600, 0, 600);   //* Set up a 2D orthographic projection efining the coordinate system for your drawing area.
// }

// void display()
// {
//     glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
//     glFlush();                    // Force execution of OpenGL commands
// }
// void mainMenu(int choice)
// {
//     switch (choice)
//     {
//     case 1: // Pixel
//         glPointSize(10);
//         glColor3f(1, 0, 0);
//         glBegin(GL_POINTS);
//         glVertex2i(100, 100);
//         glEnd();
//         break;
//     case 2: // Line
//         glLineWidth(3);
//         glColor3f(1, 0, 0);
//         glBegin(GL_LINES);
//         glVertex2i(10, 10);
//         glVertex2i(300, 10);
//         glEnd();
//         break;
//     case 3: // Triangle
//         glColor3f(0, 0, 1);
//         glBegin(GL_TRIANGLES);
//         glVertex2i(50, 50);
//         glVertex2i(300, 50);
//         glVertex2i(150, 100);
//         glEnd();
//         break;
//     case 4: // Polygon
//         glColor3f(0, 1, 1);
//         glBegin(GL_POLYGON);
//         glVertex2i(150, 150);
//         glVertex2i(400, 150);
//         glVertex2i(400, 250);
//         glVertex2i(150, 250);
//         glEnd();
//         break;
//     case 5: // Exit
//         exit(0);
//         break;
//     }
// }

// int main(int argc, char **argv)
// {
//     glutInit(&argc, argv);

//     glutInitDisplayMode(GLUT_SINGLE);
//     glutInitWindowPosition(0, 0);
//     glutInitWindowSize(600, 600);
//     glutCreateWindow("Practical_1 SIB64");
//     initialize();

//     glutCreateMenu(mainMenu);
//     glutAddMenuEntry("Pixel", 1);
//     glutAddMenuEntry("Line", 2);
//     glutAddMenuEntry("Triangle", 3);
//     glutAddMenuEntry("Polygon", 4);
//     glutAddMenuEntry("Exit", 5);
//     glutAttachMenu(GLUT_RIGHT_BUTTON);
//     glutDisplayFunc(display);
//     glutMainLoop();
//     return 0;
// }
