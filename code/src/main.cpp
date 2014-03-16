#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "Game.h"
#include <iostream>
#include <string.h>


/// Useful global variables

float x_pos = 0;
float y_pos = 0;
float z_pos = 0;
float theta = M_PI / 6;
float phi = M_PI / 2;
float R = 9;

float scaleFactor = 1;

float gameEdge = 10.0; ///< edge size of the base plance
float gameHeight = 20.0; ///< height to reach for win

Game G = Game(gameEdge, gameHeight);
Cuboid C;

float y = 0; ///< displacement of the falling cube
float speed = 0.02; ///< speed with which the cube falls
float newHeight = G.globalHeight - (G.cuboids[0].getYS() / 2); ///< the new height to be reached for win, with reference to the new base(cubes have fallen)
int j = 0; ///< incrementer through the vector of random cuboids
bool rightZone = false; ///< weather or not the falling cube has the x, z coordinates within the last fallen cube surface;
bool GameLose = false; ///< true when lose the game
bool GameWin = false; ///< true for win
bool Pause = false;


/// prints a text in 2d within the window

void print_text(char* string, int x, int y, void* font, float r, float g, float b)
{
    glColor3f(r, g, b);
    glRasterPos2i(x, y);
    int len = strlen(string);
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

/// changing the size of the whole perspective

void changeSize(int w, int h)
{
    if (h == 0)
        h = 1;
    float ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(90, ratio, 1, 1000);
}

void display()
{
    x_pos = R * cos(phi) * cos(theta);
    y_pos = R * sin(theta);
    z_pos = R * sin(phi) * cos(theta);

    glClearColor(0.0f, 1.0f, 1.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (cos(theta) >= 0)
        gluLookAt(x_pos, y_pos, z_pos, 0, 0, 0, 0, 1, 0);
    else
        gluLookAt(x_pos, y_pos, z_pos, 0, 0, 0, 0, -1, 0);



    // the base plane (square)
    glColor3f(0.0, 0.0, 0.6);
    glTranslatef(0, -4, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-G.baseEdge / 2, 0, -G.baseEdge / 2);
    glVertex3f(G.baseEdge / 2, 0, -G.baseEdge / 2);
    glVertex3f(G.baseEdge / 2, 0, G.baseEdge / 2);
    glVertex3f(-G.baseEdge / 2, 0, G.baseEdge / 2);
    glEnd();


    C = G.cuboids[j];
    C.setTranslation(C.getXT(), C.getYT() - y, C.getZT());

    float x, z, xa, xb, za, zb;

    if (j > 0)
    {

        float x = C.getXT();
        float z = C.getZT();

        float xa = G.cuboids[j - 1].getXT() - (G.cuboids[j - 1].getXS() / 2);
        float xb = G.cuboids[j - 1].getXT() + (G.cuboids[j - 1].getXS() / 2);
        float za = G.cuboids[j - 1].getZT() - (G.cuboids[j - 1].getZS() / 2);
        float zb = G.cuboids[j - 1].getZT() + (G.cuboids[j - 1].getZS() / 2);

        if (x >= xa && x <= xb && z >= za && z <= zb)
        {
            C.setColor(0.7, 0.0, 0.0);
            rightZone = true;
        } else rightZone = false;
    }


    bool GameOver = GameLose || GameWin;
    if (!GameOver)
        C.generateCuboid();

    if (!Pause)
        y += speed;
    else
        print_text((char*) "PAUSED", 3, 10, GLUT_BITMAP_TIMES_ROMAN_24, 1.0, 1.0, 0.0);

    if (y >= newHeight && !GameOver)
    {
        y = 0.0;
        speed = 0.02;
        C.setColor(0.0, 0.8, 0.0);
        G.cuboids[j] = C;

        newHeight -= G.cuboids[j].getYS() / 2 + G.cuboids[j + 1.2].getYS() / 2;
        if (newHeight < C.getYS())
        {
            GameWin = true;
            std::cout << "YOU WIN! Game over!" << std::endl;

        } else if (j > 0 && rightZone == false)
        {
            GameLose = true;
            std::cout << "YOU LOSE! Game over!" << std::endl;
        }
        j++;
    }


    if (GameWin) print_text((char*) "YOU WIN! Game over!", 3, 10, GLUT_BITMAP_TIMES_ROMAN_24, 1.0, 0.0, 1.0);
    if (GameLose) print_text((char*) "YOU LOOSE! Game over!", 3, 10, GLUT_BITMAP_TIMES_ROMAN_24, 1.0, 0.0, 1.0);

    if (j > 0)
    {
        C.setColor(0.8, 0.0, 0.0);
        for (int i = 0; i < j; i++)
        {
            G.cuboids[i].generateCuboid();
        }
    }



    glutSwapBuffers();
}

void processKeys(unsigned char key, int x, int y)
{
    C = G.cuboids[j];
    switch (key)
    {
        case 'w': // move camera up
            theta += 0.1;
            break;
        case 's': //move camera down
            theta -= 0.1;
            break;
        case 'a': //move camera left
            phi += 0.1;
            break;
        case 'd': // move camera right
            phi -= 0.1;
            break;
        case 't': //zoom out
            if (R < 100)
                R += 0.3f;
            break;
        case 'g': // zoom in
            if (R > 4)
                R -= 0.3f;
            break;
        case 'p': //pause the game
            if ((GameWin || GameLose) == false)
            {
                if (Pause)
                    Pause = false;
                else
                    Pause = true;
            }

            break;
        case ' ': // when on the right trajectory, you can press space to increase the falling speed
            speed = 0.2;
            break;
        case 'q': // quit
            exit(0);
            break;
        case 'r': //restart
            if (GameWin || GameLose)
            {
                G = Game(gameEdge, gameHeight);
                GameWin = GameLose = false;

                j = 0;
                C = G.cuboids[j];
                y = 0;
                newHeight = G.globalHeight - (G.cuboids[0].getYS() / 2);
                rightZone = false;
                gluPerspective(90.0, 1.0, 1.0, 1000.0);
            }
            break;
    }

    G.cuboids[j] = C;
}

void processSpecialKeys(int key, int x, int y)
{
    if (!Pause)
    {
        C = G.cuboids[j];
        switch (key)
        {
            case GLUT_KEY_UP: //move cuboid forward
                if (C.getZT() <= -G.baseEdge / 2)
                    C.setTranslation(C.getXT(), C.getYT(), -G.baseEdge / 2);
                else
                    C.setTranslation(C.getXT(), C.getYT(), C.getZT() - 0.2);
                break;
            case GLUT_KEY_DOWN: //move cuboid backward
                if (C.getZT() >= G.baseEdge / 2)
                    C.setTranslation(C.getXT(), C.getYT(), G.baseEdge / 2);
                else
                    C.setTranslation(C.getXT(), C.getYT(), C.getZT() + 0.2);
                break;
            case GLUT_KEY_LEFT: // move cuboid to the left
                if (C.getXT() <= -G.baseEdge / 2)
                    C.setTranslation(-G.baseEdge / 2, C.getYT(), C.getZT());
                else
                    C.setTranslation(C.getXT() - 0.2, C.getYT(), C.getZT());
                break;
            case GLUT_KEY_RIGHT: // move cuboid to the right
                if (C.getXT() >= G.baseEdge / 2)
                    C.setTranslation(G.baseEdge / 2, C.getYT(), C.getZT());
                else
                    C.setTranslation(C.getXT() + 0.2, C.getYT(), C.getZT());
                break;
        }
        G.cuboids[j] = C;
    }
}

void spin(void)
{
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("BOX Game - Mihai Baltac");
    glClearColor(0.0f, 0.9f, 0.9f, 0.0f);

    glEnable(GL_DEPTH_TEST);

    glutReshapeFunc(changeSize);
    glutDisplayFunc(display);

    //Processing keys function
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(90.0, 1.0, 1.0, 1000.0);

    glutIdleFunc(spin);

    glutMainLoop();


    return 0;
}