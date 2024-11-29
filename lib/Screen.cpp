#include <GL/glut.h>
#include "RGB.h"
#include "Game.h"
#include <iostream>
using namespace std;

int WIDTH = 0;
int HEIGHT = 0;
int MULTIPLIAR_HEIGTH = 0;
int MULTIPLIAR_WIDTH = 0;
struct RGB *pixels = NULL;
GLubyte *realScreen = NULL;

void initGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

struct RGB getPixel(int i, int j)
{
    return pixels[i * WIDTH + j];
}

void setPixel(int i, int j, struct RGB rgb)
{
    if (rgb.r == -1 && rgb.g == -1 && rgb.b == -1)
    {
        return;
    }

    pixels[i * WIDTH + j] = rgb;
}

void makeScreen()
{
    int position = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int im = 0; im < MULTIPLIAR_HEIGTH; im++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                for (int jm = 0; jm < MULTIPLIAR_WIDTH; jm++)
                {
                    realScreen[position++] = pixels[i * WIDTH + j].r;
                    realScreen[position++] = pixels[i * WIDTH + j].g;
                    realScreen[position++] = pixels[i * WIDTH + j].b;
                }
            }
        }
    }
}

void display()
{
    cycle();
    makeScreen();
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(WIDTH * MULTIPLIAR_WIDTH, HEIGHT * MULTIPLIAR_HEIGTH, GL_RGB, GL_UNSIGNED_BYTE, realScreen);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'a':
        exit(0);
        break;
    }
}

void timer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(20, timer, 0); // 50 fps 1000 / 20
}

void startScreen(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(WIDTH * MULTIPLIAR_WIDTH, HEIGHT * MULTIPLIAR_HEIGTH);
    glutCreateWindow("game");
    initGL();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}

void initScreen(int width, int height, int multipliar_width, int multipliar_heigth)
{
    WIDTH = width;
    HEIGHT = height;
    MULTIPLIAR_HEIGTH = multipliar_heigth;
    MULTIPLIAR_WIDTH = multipliar_width;
    pixels = new struct RGB[WIDTH * HEIGHT];
    realScreen = new GLubyte[WIDTH * HEIGHT * 3 * MULTIPLIAR_HEIGTH * MULTIPLIAR_WIDTH];
}