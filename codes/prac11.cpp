#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

const int SCR_WIDTH = 800, SCR_HEIGHT = 600;
float timeElapsed = 0.0f;
std::vector<std::pair<float, float>> lineVertices;

void setupViewport()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
}

void updateLine()
{
    timeElapsed += 0.01f;
    lineVertices.clear();
    int numSegments = 20;
    for (int i = 0; i < numSegments; i++)
    {
        float t = (float)i / (numSegments - 1);
        float x = -0.8f + 1.6f * t;
        float y = 0.3f * sin(timeElapsed + t * 6.28f);
        lineVertices.push_back({x, y});
    }
    glutPostRedisplay();
}

void renderLine()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(5.0f * (1.0f - 0.5f * sin(timeElapsed * 2.0f)));
    float r = 0.5f + 0.5f * sin(timeElapsed);
    float g = 0.5f + 0.5f * cos(timeElapsed);
    float b = 1.0f - 0.5f * sin(timeElapsed);
    glColor3f(r, g, b);
    glBegin(GL_LINE_STRIP);
    for (const auto &v : lineVertices)
    {
        glVertex2f(v.first, v.second);
    }
    glEnd();
    glutSwapBuffers();
}

void displayCallback()
{
    renderLine();
}

void timerCallback(int value)
{
    updateLine();
    glutTimerFunc(16, timerCallback, 0); // 60 FPS (1000ms / 60 ~= 16ms per frame)
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
    glutCreateWindow("Line Animation");
    setupViewport();
    glutDisplayFunc(displayCallback);
    glutTimerFunc(16, timerCallback, 0);
    glutMainLoop();
    return 0;
}