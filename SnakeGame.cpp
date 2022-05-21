#include <GL/glut.h>
#include <fstream>
#include "math.h"

using namespace std;

int dir;
int d = 1;
int num = 7;
int key1 = 3;
int Score = 0;
int hightScore;
int Scale = 25;
int N = 50, M = 30;
int w = Scale * N;
int h = Scale * M;

char sScore[15];
char sHightScore[15];
float xm = 0.0;
float ym = 0.0;
bool down = false;

struct {
    int x;
    int y;
} s[100];

class Fruct {
public:
    int x, y;
    void New()
    {
        x = rand() % N;
        y = rand() % (M - 3);
    }
    void DrawFruct()
    {
        glColor3f(1.0, 0.9, 0.0);
        glRectf(x * Scale, y * Scale, (x + 1) * Scale, (y + 1) * Scale);
    }
} m[2];

//class check {
//public:
//    int x, y;
//
//    void New()
//    {
//        x = rand() % N;
//        y = rand() % (M - 3);
//    }
//
//} u[10];

void draw_string(void* font, const char* string)
{
    while (*string)
        glutStrokeCharacter(font, *string++);
}

void DrawMenu()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON); // Start
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(705.0, 650.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(500.0, 650.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(500.0, 550.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(705.0, 550.0, 0.0);
    glEnd();
    glBegin(GL_POLYGON); // Exit
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(670.0, 230.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(540.0, 230.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(540.0, 140.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(670.0, 140.0, 0.0);
    glEnd();

    glLineWidth(4.0f);
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslatef(w / (2.38), h / (1.3), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "START");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(w / (2.229), h / (4.4), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "EXIT");
    glPopMatrix();

    glFinish();
    glutSwapBuffers();
}

void DrawExit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(950.0, 150.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(300.0, 150.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(300.0, 90.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(950.0, 90.0, 0.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(670.0, 80.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(580.0, 80.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(580.0, 30.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(670.0, 30.0, 0.0);
    glEnd();

    glLineWidth(7.0f);
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(w / (6), h / (1.5), 0);
    glScalef(1.1f, 1.1f, 1.1f);
    draw_string(GLUT_STROKE_ROMAN, "Game over!");
    glPopMatrix();

    glLineWidth(2.5f);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(w / (3.0), h / 7, 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "By Ishav, Kartik and Manmeet ");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w / (2.07), h / (15.3), 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "EXIT");
    glPopMatrix();

    glLineWidth(3.5f);
    glColor3f(0.9, 0.3, 0.5);
    glPushMatrix();
    glTranslatef(w / (2.8), h / (2.1), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "Final score:");
    glPopMatrix();

    sprintf_s(sScore, "%9d", Score);
    glPushMatrix();
    glTranslatef(w / (2.8), h / (2.1), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, sScore);
    glPopMatrix();

    glFinish();
    glutSwapBuffers();
}

void Tick()
{
    // Movement of the snake's body:
    for (int i = num; i > 1; --i) {
        s[i].x = s[i - 2].x;
        s[i].y = s[i - 2].y;
    }

    // Movement of the snake's head:
    switch (dir) {
    case 0:
        s[0].y += 1;
        break;
    case 1:
        s[0].x -= 1;
        break;
    case 2:
        s[0].x += 1;
        break;
    case 3:
        s[0].y -= 1;
        break;
    }
    // int h = 1;
     // The snake's length increases on eating a fruit:
    for (int i = 0; i < 5; i++)
        if ((s[0].x == m[i].x) && (s[0].y == m[i].y)) {
            num++;
            m[i].New();
            /*
            if (h != 11) {
            }
            else {
                h = 0;
                u[h].New();
            }
            */
            Score += 2;
        }



    // Game ends on touching the boundary:
   // if (s[0].x > N || s[0].x < 0 || s[0].y >(M - 3) || s[0].y < 0) {
     //   key1 = 2;
   // }
    if (s[0].x > N || s[0].x < 0 ) {
        key1 = 1;
        s[0].x=0;
    }
    if (s[0].y > (M - 3) || s[0].y < 0) {
        key1 = 2;
      
    }


}

void DrawSnake()
{
    for (int i = 0; i < num; i++) {
        glColor3f(i / (num * 1.0), 0.0, 0.0);

        glRectf(s[i].x * Scale, s[i].y * Scale, (s[i].x + 1) * Scale, (s[i].y + 1) * Scale);
    }
}

void DrawScore()
{
    glLineWidth(1.5f);
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslatef(w / (5.4), h / (1.05), 0);
    glScalef(0.3f, 0.3f, 0.3f);
    draw_string(GLUT_STROKE_ROMAN, "Your score:");
    glPopMatrix();
    sprintf_s(sScore, "%9d", Score);
    glPushMatrix();
    glTranslatef(w / (5), h / (1.05), 0);
    glScalef(0.3f, 0.3f, 0.3f);
    draw_string(GLUT_STROKE_ROMAN, sScore);
    glPopMatrix();

}

void display()
{
    switch (key1) {
    case 1:
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POLYGON);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 800.0, 0.0);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0, 700.0, 0.0);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1400.0, 700.0, 0.0);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(1400.0, 800.0, 0.0);
        glEnd();
        for (int i = 0; i < 2; i++)
            m[i].DrawFruct();
        DrawSnake();
        DrawScore();
        break;
    case 2:
        DrawExit();
        break;
    case 3:
        DrawMenu();
        break;
    case 4:
        break;
    }
    glFlush();
}

void spawn()
{
    for (int i = 0; i < 2; i++)
        m[i].New();
    /*for (int i = 0; i < 10; i++)
        u[i].New();*/

    s[0].x = 10;
    s[0].y = 10;
}

void MyKeyboard(int key, int a, int b)
{
    switch (key) {
    case 101: // up
        dir = 0;
        break;
    case 102: // right
        dir = 2;
        break;
    case 100: // left
        dir = 1;
        break;
    case 103: // down
        dir = 3;
        break;
    case 27: // escape
        exit(0);
        break;
    }
}

void MousePressed(int button, int state, int ax, int ay)
{
    down = button == GLUT_LEFT_BUTTON && state == GLUT_LEFT;
    if (down) {
        if (key1 == 3) {
            //exit
            if (ax > (540.0) && ax < (670.0) && ay >(490.0) && ay < (600.0)) {
                exit(0);
            }

            if (ax > (500.0) && ax < (705.0) && ay >(100.0) && ay < (190.0)) {
                //start
                key1 = 1;
                d = 2;
                num = 5;
                Score = 0;
                spawn();
                display();
            }
        }
        if (key1 == 2) {
            //return to menu
            if (ax > (580.0) && ax < (670.0) && ay >(660.0) && ay < (690.0)) {
                exit(0);
            }
            //    if (ax > (540.0) && ax < (670.0) && ay >(580.0) && ay < (610.0)) {
            //        key1 = 3;
            //        d = 1;
            //        glClear(GL_COLOR_BUFFER_BIT);
            //        spawn();
            //        DrawMenu();
            //    }
        }
        /*if (key1 == 4) {
            if (ax > (520.0) && ax < (680.0) && ay >(580.0) && ay < (610.0)) {
                key1 = 3;
                d = 1;
                glClear(GL_COLOR_BUFFER_BIT);
                spawn();
                DrawExit();
            }
        }*/
    }
    glutMouseFunc(MousePressed);
}

void CreateGlutWindow()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Mode selection: single buffer and RGBA colors
    glutInitWindowSize(w, h);
    glutCreateWindow("Snake");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
}

void timer(int = 0)
{
    if (d == 2) {
        display();
    }
    Tick();

    glutTimerFunc(100, timer, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    CreateGlutWindow();
    glutDisplayFunc(display);
    glutTimerFunc(1000, timer, 0);
    glutSpecialFunc(MyKeyboard);
    glutMouseFunc(MousePressed);
    glutMainLoop(); //  enter GLUT event processing loop
    return 0;
}