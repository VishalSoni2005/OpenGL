// #include <cmath>
// #include <iostream>
// #include <GL/freeglut.h>
// using namespace std;

// void displayPoint(int x, int y)
// {
//   glColor3f(0, 1, 0);
//   glBegin(GL_POINTS);
//   glVertex2i(x, y);
//   glEnd();
// }

// void dda(float x1, float y1, float x2, float y2)
// {

//   // step 1
//   float dx = x2 - x1;
//   float dy = y2 - y1;

//   // step 2 steps
//   float steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

//   // step 3
//   float xinc = dx / steps;
//   float yinc = dy / steps;

//   float x = x1;
//   float y = y1;

//   // step 4
//   for (int i = 0; i <= steps; i++)
//   {
//     if (i % 6 < 3)
//       displayPoint(round(x), round(y));

//     x += xinc;
//     y += yinc;
//   }

//   glFlush();
// }

// void init()
// {
//   glClearColor(0, 0, 0, 1);   // Black background
//   gluOrtho2D(0, 600, 0, 600); // 2D projection
//   glPointSize(3);             // Point size
// }

// void display()
// {
//   glClear(GL_COLOR_BUFFER_BIT);
//   dda(100, 100, 500, 500); // Example line
// }

// int main(int argc, char **argv)
// {
//   glutInit(&argc, argv);
//   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//   glutInitWindowPosition(100, 100);
//   glutInitWindowSize(600, 600);
//   glutCreateWindow("DDA Line Drawing");

//   init();
//   glutDisplayFunc(display);
//   glutMainLoop();
//   return 0;
// }