#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include<iostream>
#include <irrKlang.h>
#include <vector>
#include <string.h>
#include "sgi.h"

using namespace std;

#define appear 1
#define diappear 0
#define menu 1
#define playing 2
#define died 3
int cheat = appear;
int play = menu;

GLfloat a = 18.0;
GLfloat PI = 3.1415926f;
GLfloat RG = 200;
GLfloat RD = 120;

float col = 0.0;
int cc = 1;
float high = 20.0;
GLfloat tt = 0;
double speed = 0.0;
GLfloat jump = 500.0;
GLfloat spin = 0.0;
GLint HP = 3;
GLfloat theda = 0.0;
GLfloat fin = 0.0;
GLint start = 0;

GLfloat dragon[3] = { RD * cos(0),0.0,RD * sin(0) };
static GLint attack[2] = { 1, 0 };

static GLfloat ambient_0[] = { 0.1,0.1,0.1,1.0 };
static GLfloat ambient_1[] = { 0.5,0.5,0.5,1.0 };
static GLfloat gray1[] = { 0.5,0.5,0.5,1.0 };
static GLfloat white[] = { 1.0,1.0,1.0,1.0 };
static GLfloat no_color[] = { 0.0,0.0,0.0,1.0 };
static GLfloat y[4] = { 1.0,1.0,0.0,1.0 };
static GLfloat red[4] = { 1.0,0,0.0,1.0 };

GLenum minfilter = GL_NEAREST;
GLenum magfilter = GL_NEAREST;
GLenum env = GL_MODULATE;
GLenum wraps = GL_CLAMP_TO_BORDER;
GLenum wrapt = GL_CLAMP_TO_BORDER;

int iheight, iwidth, idepth;
unsigned char* image1 = NULL;
unsigned char* image2 = NULL;

GLuint fontOffset;
irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();
// bitmap
GLubyte space[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
GLubyte letters[][13] = {
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}
};

void makeRasterFont(void)
{
    GLuint i, j;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    fontOffset = glGenLists(128);
    for (i = 0, j = 'A'; i < 26; i++, j++) {
        glNewList(fontOffset + j, GL_COMPILE);
        glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i]);
        glEndList();
    }
    glNewList(fontOffset + ' ', GL_COMPILE);
    glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, space);
    glEndList();
}

void printString(char* s)
{
    glPushAttrib(GL_LIST_BIT);
    glListBase(fontOffset);
    glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte*)s);
    glPopAttrib();
}

void texenv(void)
{
    GLfloat env_color[4], border_color[4];

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minfilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magfilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wraps);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapt);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, env);
    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, env_color);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
}

void texture(void)
{
    image1 = read_sgi("data/wall1.sgi", &iwidth, &iheight, &idepth);
    if (!image1)
        exit(0);

    texenv();
    gluBuild2DMipmaps(GL_TEXTURE_2D, idepth, iwidth, iheight,
        idepth == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image1);
}


void menudisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glLoadIdentity();

    if (start == 0) {
        gluLookAt(-1.0, high, 0.2, -0.95, high, 0.2, 0.0, 1.0, 0.0);

        glColor3f(1.0, 1.0, 1.0);
        glRasterPos3f(0.0+0.06, high+0.1, 0.0);
        printString("PRESS SPACE TO JUMP");
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        glColor3f(col, col, col);
        glRasterPos3f(0.0, high, 0.0);
        printString("PRESS SPACE TO START");
        glDisable(GL_BLEND);
    }

    else if (start == 1) {

        if (high >= 5.0) {
            high -= 0.05;
            gluLookAt((RD + 20) * cos(-0.2), high, (RD + 20) * sin(-0.2), 0.0, high, 0.0, 0.0, 1.0, 0.0);
        }
        else {
            gluLookAt((RD + 20) * cos(-0.2), 5.0, (RD + 20) * sin(-0.2), 0.0, 5.0, 0.0, 0.0, 1.0, 0.0);
            play = playing;
            SoundEngine->stopAllSounds();
            SoundEngine->play2D("data/playmusic.mp3", GL_TRUE);
            tt = 0;
            speed = 0.0;
            jump = 500.0;
            spin = 0.0;
            HP = 3;
            dragon[0] = RD * cos(0);
            dragon[2] = RD * sin(0);
        }
    }

    glPushMatrix();


    //floor	
    glBegin(GL_POLYGON);
    glCallList(2);
    glEnd();


    glPopMatrix();

    glPushMatrix();
    glTranslatef(RD, 0.0, 0.0);
    glCallList(1);
    glPopMatrix();

    glutSwapBuffers();

}

void playdisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    GLfloat light_position1[] = { 0.0, 30.0, -250.0, 1.0 };                 /*light*/
    

    //gluLookAt(a*cos(theda)*cos(fin), a*sin(theda)+3, a * cos(theda) * sin(fin),  0.0, 3.0, 0.0, 0.0, 1.0, 0.0);
    //gluLookAt((RG+30) * cos(theda) * cos(fin), (RG + 30) * sin(theda) , (RG + 30) * cos(theda) * sin(fin), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    gluLookAt((RD + 20) * cos(-spin-0.15), 5.0, (RD + 20) * sin(-spin-0.15), 0.0, 5.0, 0.0,    0.0, 1.0, 0.0);

    glPushMatrix();
    glutSolidSphere(10,10,10);
    glPopMatrix();

    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);

    
    


    glPushMatrix();
    glCallList(2);          //floor	
    glPopMatrix();

    glPushMatrix();
    glTranslatef(dragon[0],dragon[1],dragon[2]);
    glRotatef(spin/PI*180, 0, 1, 0);
    for (int i = 0; i < HP; i++) {
        glPushMatrix();
        glTranslatef(0.0, 0.0, -1.0 * i);
        glCallList(7);
        glPopMatrix();
    }                       //hp
    glCallList(1);          //小恐龍
    glPopMatrix();
    

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();         //障礙物們(長方體)
    glMaterialfv(GL_FRONT, GL_EMISSION, gray1);
    glCallList(5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}

void diedisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glLoadIdentity();
    gluLookAt(a,5.0,0.0,    0.0, 5.0, 0.0,   0.0, 1.0, 0.0);

    glPushMatrix();
    glCallList(1);          //小恐龍
    glEnable(GL_POLYGON_OFFSET_FILL);
    if (play == died) {
        glBegin(GL_POLYGON);                    //眼淚
        glVertex3f(2.0, 6.95, 0.0);
        glVertex3f(2.0, 6.5, 0.25);
        glVertex3f(2.0, 6.35, 0.2);
        glVertex3f(2.0, 6.25, 0.0);
        glVertex3f(2.0, 6.35, -0.2);
        glVertex3f(2.0, 6.5, -0.25);
        glEnd();
    }
    glDisable(GL_POLYGON_OFFSET_FILL);
    glPopMatrix();
    glutSwapBuffers();
}

void display(void){
    if (play == menu) {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        menudisplay();
    }
    else if (play == playing) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        playdisplay();
    }
    else {
        diedisplay();
    }
}



void compile(void) {
    //小恐龍
    {glNewList(1, GL_COMPILE);
    glPushMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, no_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, gray1);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);
    glBegin(GL_POLYGON);                //軀幹上半
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(2.0, 5.0, 1.0);
    glVertex3f(3.5, 0.0, 2.0);
    glVertex3f(3.0, 0.0, -2.5);
    glVertex3f(2.0, 5.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, 5.0, -1.0);
    glVertex3f(3.0, 0.0, -2.5);
    glVertex3f(-3.0, 0.0, -2.5);
    glVertex3f(-2.0, 5.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 5.0, -1.0);
    glVertex3f(-3.0, 0.0, -2.5);
    glVertex3f(-3.5, 0.0, 2.0);
    glVertex3f(-2.0, 5.0, 1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 5.0, 1.0);
    glVertex3f(-3.5, 0.0, 2.0);
    glVertex3f(-2.0, 0.0, 3.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 5.0, 1.0);
    glVertex3f(-2.0, 0.0, 3.0);
    glVertex3f(2.0, 0.0, 3.0);
    glVertex3f(2.0, 5.0, 1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, 5.0, 1.0);
    glVertex3f(2.0, 0.0, 3.0);
    glVertex3f(3.5, 0.0, 2.0);
    glEnd();

    glBegin(GL_POLYGON);                //軀幹下半
    glVertex3f(3.5, 0.0, 2.0);
    glVertex3f(2.0, -3.0, 1.0);
    glVertex3f(2.0, -3.0, -1.0);
    glVertex3f(3.0, 0.0, -2.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(3.0, 0.0, -2.5);
    glVertex3f(2.0, -3.0, -1.0);
    glVertex3f(-2.0, -3.0, -1.0);
    glVertex3f(-3.0, 0.0, -2.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-3.0, 0.0, -2.5);
    glVertex3f(-2.0, -3.0, -1.0);
    glVertex3f(-2.0, -3.0, 1.0);
    glVertex3f(-3.5, 0.0, 2.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-3.5, 0.0, 2.0);
    glVertex3f(-2.0, -3.0, 1.0);
    glVertex3f(-2.0, 0.0, 3.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 0.0, 3.0);
    glVertex3f(-2.0, -3.0, 1.0);
    glVertex3f(2.0, -3.0, 1.0);
    glVertex3f(2.0, 0.0, 3.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, 0.0, 3.0);
    glVertex3f(2.0, -3.0, 1.0);
    glVertex3f(3.5, 0.0, 2.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, -3.0, 1.0);
    glVertex3f(-2.0, -3.0, -1.0);
    glVertex3f(2.0, -3.0, -1.0);
    glVertex3f(2.0, -3.0, 1.0);
    glEnd();

    glBegin(GL_POLYGON);                //右腳
    glVertex3f(2.0, -3.0, 1.0);
    glVertex3f(2.0, -5.0, 0.5);
    glVertex3f(2.0, -3.0, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, -4.0, 0.0);
    glVertex3f(2.0, -5.0, 0.5);
    glVertex3f(2.0, -5.0, -0.5);
    glVertex3f(2.0, -4.0, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, -4.0, -0.5);
    glVertex3f(2.0, -5.0, -0.5);
    glVertex3f(1.0, -5.0, -0.5);
    glVertex3f(1.0, -4.0, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.0, -4.0, -0.5);
    glVertex3f(1.0, -5.0, -0.5);
    glVertex3f(1.0, -5.0, 0.5);
    glVertex3f(1.0, -4.0, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.0, -3.0, -0.5);
    glVertex3f(1.0, -5.0, 0.5);
    glVertex3f(1.0, -3.0, 1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.0, -3.0, 1.0);
    glVertex3f(1.0, -5.0, 0.5);
    glVertex3f(2.0, -5.0, 0.5);
    glVertex3f(2.0, -3.0, 1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, -4.0, 0.0);
    glVertex3f(2.0, -4.0, -0.5);
    glVertex3f(1.0, -4.0, -0.5);
    glVertex3f(1.0, -4.0, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, -4.0, 0.0);
    glVertex3f(1.0, -4.0, 0.0);
    glVertex3f(1.0, -3.0, -0.5);
    glVertex3f(2.0, -3.0, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.0, -5.0, 0.5);
    glVertex3f(2.0, -5.0, 0.5);
    glVertex3f(2.0, -5.0, -0.5);
    glVertex3f(1.0, -5.0, -0.5);
    glEnd();

    glBegin(GL_POLYGON);                //左腳
    glVertex3f(-2.0, -5.0, 0.5);
    glVertex3f(-2.0, -3.0, -0.5);
    glVertex3f(-2.0, -3.0, 1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, -4.0, 0.0);
    glVertex3f(-2.0, -4.0, -0.5);
    glVertex3f(-2.0, -5.0, -0.5);
    glVertex3f(-2.0, -5.0, 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, -4.0, -0.5);
    glVertex3f(-1.0, -4.0, -0.5);
    glVertex3f(-1.0, -5.0, -0.5);
    glVertex3f(-2.0, -5.0, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.0, -4.0, -0.5);
    glVertex3f(-1.0, -4.0, 0.0);
    glVertex3f(-1.0, -5.0, 0.5);
    glVertex3f(-1.0, -5.0, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.0, -3.0, -0.5);
    glVertex3f(-1.0, -3.0, 1.0);
    glVertex3f(-1.0, -5.0, 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.0, -3.0, 1.0);
    glVertex3f(-2.0, -3.0, 1.0);
    glVertex3f(-2.0, -5.0, 0.5);
    glVertex3f(-1.0, -5.0, 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, -4.0, 0.0);
    glVertex3f(-1.0, -4.0, 0.0);
    glVertex3f(-1.0, -4.0, -0.5);
    glVertex3f(-2.0, -4.0, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, -4.0, 0.0);
    glVertex3f(-2.0, -3.0, -0.5);
    glVertex3f(-1.0, -3.0, -0.5);
    glVertex3f(-1.0, -4.0, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.0, -5.0, 0.5);
    glVertex3f(-1.0, -5.0, -0.5);
    glVertex3f(-2.0, -5.0, -0.5);
    glVertex3f(-2.0, -5.0, 0.5);
    glEnd();

    glBegin(GL_POLYGON);                //尾巴
    glVertex3f(-2.0, 0.0, 3.0);
    glVertex3f(2.0, 0.0, 3.0);
    glVertex3f(0.0, -4.0, 4.6);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.0, -4.0, 4.6);
    glVertex3f(2.0, 0.0, 3.0);
    glVertex3f(0.0, -2.0, 5 / 3);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.0, -4.0, 4.6);
    glVertex3f(0.0, -2.0, 5 / 3);
    glVertex3f(-2.0, 0.0, 3.0);
    glEnd();

    glBegin(GL_POLYGON);                    //頭
    glVertex3f(2.0, 6.0, 1.0);
    glVertex3f(2.0, 5.0, 1.0);
    glVertex3f(2.0, 5.0, -3.0);
    glVertex3f(2.0, 6.0, -3.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, 8.0, 1.0);
    glVertex3f(2.0, 6.0, 1.0);
    glVertex3f(2.0, 6.0, -1.0);
    glVertex3f(2.0, 7.0, -3.5);
    glVertex3f(2.0, 9.0, -3.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, 6.0, -3.0);
    glVertex3f(2.0, 5.0, -3.0);
    glVertex3f(-2.0, 5.0, -3.0);
    glVertex3f(-2.0, 6.0, -3.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 6.0, -3.0);
    glVertex3f(-2.0, 5.0, -3.0);
    glVertex3f(-2.0, 5.0, 1.0);
    glVertex3f(-2.0, 6.0, 1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, 6.0, -1.0);
    glVertex3f(2.0, 6.0, -3.0);
    glVertex3f(-2.0, 6.0, -3.0);
    glVertex3f(-2.0, 6.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, 5.0, -1.0);
    glVertex3f(2.0, 5.0, -3.0);
    glVertex3f(-2.0, 5.0, -3.0);
    glVertex3f(-2.0, 5.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, 9.0, -3.5);
    glVertex3f(2.0, 7.0, -3.5);
    glVertex3f(-2.0, 7.0, -3.5);
    glVertex3f(-2.0, 9.0, -3.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 9.0, -3.5);
    glVertex3f(-2.0, 7.0, -3.5);
    glVertex3f(-2.0, 6.0, -1.0);
    glVertex3f(-2.0, 6.0, 1.0);
    glVertex3f(-2.0, 8.0, 1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 7.0, -3.5);
    glVertex3f(2.0, 7.0, -3.5);
    glVertex3f(2.0, 6.0, -1.0);
    glVertex3f(-2.0, 6.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 9.0, -3.5);
    glVertex3f(2.0, 9.0, -3.5);
    glVertex3f(2.0, 8.0, 1.0);
    glVertex3f(-2.0, 8.0, 1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 8.0, 1.0);
    glVertex3f(2.0, 8.0, 1.0);
    glVertex3f(2.0, 5.0, 1.0);
    glVertex3f(-2.0, 5.0, 1.0);
    glEnd();

    glBegin(GL_POLYGON);                //右手
    glVertex3f(2.0, 4.0, -1.3);
    glVertex3f(2.0, 35 / 13, -22 / 13);
    glVertex3f(2.0, 4.0, -3.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, 4.0, -3.0);
    glVertex3f(2.0, 3.5, -2.5);
    glVertex3f(2.0, 3.0, -3.0);
    glVertex3f(2.0, 3.5, -3.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, 4.0, -3.0);
    glVertex3f(2.0, 3.5, -3.5);
    glVertex3f(1.0, 3.5, -3.5);
    glVertex3f(1.0, 4.0, -3.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, 3.5, -3.5);
    glVertex3f(2.0, 3.0, -3.0);
    glVertex3f(1.0, 3.0, -3.0);
    glVertex3f(1.0, 3.5, -3.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.0, 4.0, -3.0);
    glVertex3f(1.0, 3.5, -3.5);
    glVertex3f(1.0, 3.0, -3.0);
    glVertex3f(1.0, 3.5, -2.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.0, 4.0, -3.0);
    glVertex3f(1.0, 35 / 13, -22 / 13);
    glVertex3f(1.0, 4.0, -1.3);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, 4.0, -1.3);
    glVertex3f(2.0, 4.0, -3.0);
    glVertex3f(1.0, 4.0, -3.0);
    glVertex3f(1.0, 4.0, -1.3);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.0, 3.5, -2.5);
    glVertex3f(2.0, 3.5, -2.5);
    glVertex3f(2.0, 3.0, -3.0);
    glVertex3f(1.0, 3.0, -3.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0, 3.5, -2.5);
    glVertex3f(2.0, 35 / 13, -22 / 13);
    glVertex3f(1.0, 35 / 13, -22 / 13);
    glVertex3f(1.0, 3.5, -2.5);
    glEnd();

    glBegin(GL_POLYGON);                //左手
    glVertex3f(-2.0, 4.0, -1.3);
    glVertex3f(-2.0, 4.0, -3.0);
    glVertex3f(-2.0, 35 / 13, -22 / 13);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 4.0, -3.0);
    glVertex3f(-2.0, 3.5, -3.5);
    glVertex3f(-2.0, 3.0, -3.0);
    glVertex3f(-2.0, 3.5, -2.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 4.0, -3.0);
    glVertex3f(-1.0, 4.0, -3.0);
    glVertex3f(-1.0, 3.5, -3.5);
    glVertex3f(-2.0, 3.5, -3.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 3.5, -3.5);
    glVertex3f(-1.0, 3.5, -3.5);
    glVertex3f(-1.0, 3.0, -3.0);
    glVertex3f(-2.0, 3.0, -3.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.0, 4.0, -3.0);
    glVertex3f(-1.0, 3.5, -2.5);
    glVertex3f(-1.0, 3.0, -3.0);
    glVertex3f(-1.0, 3.5, -3.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.0, 4.0, -3.0);
    glVertex3f(-1.0, 4.0, -1.3);
    glVertex3f(-1.0, 35 / 13, -22 / 13);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 4.0, -1.3);
    glVertex3f(-1.0, 4.0, -1.3);
    glVertex3f(-1.0, 4.0, -3.0);
    glVertex3f(-2.0, 4.0, -3.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.0, 3.5, -2.5);
    glVertex3f(-1.0, 3.0, -3.0);
    glVertex3f(-2.0, 3.0, -3.0);
    glVertex3f(-2.0, 3.5, -2.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 3.5, -2.5);
    glVertex3f(-1.0, 3.5, -2.5);
    glVertex3f(-1.0, 35 / 13, -22 / 13);
    glVertex3f(-2.0, 35 / 13, -22 / 13);
    glEnd();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 200.0);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glBegin(GL_TRIANGLE_STRIP);                                 //右眼
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(0.1);
    for (float i = 0.0; i < 6.4; i += 0.3) {
        glVertex3f(2.0, 7.5 + sin(i) * 0.4, cos(i) * 0.4);
        glVertex3f(2.0, 7.5 + sin(i) * 0.35, cos(i) * 0.35);
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);                                 //左眼

    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(0.1);
    for (float i = 0.0; i < 6.4; i += 0.3) {
        glVertex3f(-2.0, 7.5 + sin(i) * 0.4, cos(i) * 0.4);
        glVertex3f(-2.0, 7.5 + sin(i) * 0.3, cos(i) * 0.3);
    }
    glEnd();
    
    glPopMatrix();
    glDisable(GL_POLYGON_OFFSET_FILL);

    glEndList(); }

    //地板
    {
        glNewList(2, GL_COMPILE);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
        glMaterialfv(GL_FRONT, GL_SPECULAR, white);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_color);
        glMaterialf(GL_FRONT, GL_SHININESS, 2.0);
        glPushMatrix();
        glBegin(GL_POLYGON);
        glColor3f(1.0,1.0,1.0);
        for (int i = 0; i < 3600; i++) {
            glVertex3f(RG * cos(2 * PI * i / 3600), -5, RG * sin(2 * PI * i / 3600));
        }
        glEnd();
        glPopMatrix();
        glEndList();
    }




    //障礙物(長方體)(單個)
    glNewList(6, GL_COMPILE);
    {
        glBegin(GL_POLYGON);
        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(0.84, 0.875);
        glVertex3f(2.0, 7.0, 1.0);
        glTexCoord2f(0.84, 0.0);
        glVertex3f(2.0, -7.0, 1.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(2.0, -7.0, -1.0);
        glTexCoord2f(1.0, 0.875);
        glVertex3f(2.0, 7.0, -1.0);
        glEnd();

        glBegin(GL_POLYGON);
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.84, 0.875);
        glVertex3f(2.0, 7.0, -1.0);
        glTexCoord2f(0.84, 0.0);
        glVertex3f(2.0, -7.0, -1.0);
        glTexCoord2f(0.5, 0.0);
        glVertex3f(-2.0, -7.0, -1.0);
        glTexCoord2f(0.5, 0.875);
        glVertex3f(-2.0, 7.0, -1.0);
        glEnd();


        glBegin(GL_POLYGON);    //2
        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(0.5, 0.875);
        glVertex3f(-2.0, 7.0, -1.0);
        glTexCoord2f(0.5, 0.0);
        glVertex3f(-2.0, -7.0, -1.0);
        glTexCoord2f(0.34, 0.0);
        glVertex3f(-2.0, -7.0, 1.0);
        glTexCoord2f(0.34, 0.875);
        glVertex3f(-2.0, 7.0, 1.0);
        glEnd();

        glBegin(GL_POLYGON);    //1
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.34, 0.875);
        glVertex3f(-2.0, 7.0, 1.0);
        glTexCoord2f(0.34, 0.0);
        glVertex3f(-2.0, -7.0, 1.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(2.0, -7.0, 1.0);
        glTexCoord2f(0.0, 0.875);
        glVertex3f(2.0, 7.0, 1.0);
        glEnd();

        glBegin(GL_POLYGON);
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0.0, 0.875);
        glVertex3f(2.0, 7.0, 1.0);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(2.0, 7.0, -1.0);
        glTexCoord2f(0.34, 1.0);
        glVertex3f(-2.0, 7.0, -1.0);
        glTexCoord2f(0.34, 0.875);
        glVertex3f(-2.0, 7.0, 1.0);
        glEnd();
        glPopMatrix();
    }
    glEndList();
    

    //障礙物們
    {
        glNewList(5, GL_COMPILE);
        glColor3f(0.4, 0.2, 0.8);
        for (float i = 0; i <= 9; i++) {
            glPushMatrix();
            glColor3f(0.1 * i, 1.0, 1.0);
            glTranslatef(RD * cos(-i * (PI / 5) - PI / 10), 0, RD * sin(-i * (PI / 5) - PI / 10));
            glRotatef(-(-i* (PI / 5) - PI / 10)/PI*180, 0.0, 1.0, 0.0);
            glCallList(6);
            glPopMatrix();
        }
        glEndList();
    }


    //愛心
    {
        glNewList(7, GL_COMPILE);
        glMaterialfv(GL_FRONT, GL_AMBIENT, red);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
        glMaterialfv(GL_FRONT, GL_SPECULAR, red);
        glMaterialfv(GL_FRONT, GL_EMISSION, red);
        glBegin(GL_POLYGON);
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 10.0, 1.0);
        glVertex3f(0.0, 9.5, 1.0);
        glVertex3f(0.0, 9.5, 0.5);
        glVertex3f(0.0, 10.0, 0.5);
        glEnd();

        glEndList();
    }
}




void change_coor(double x0, double z0, double* x1, double* z1) {
    *x1 = cos(spin + 0.001) * x0 + sin(spin - 0.001) * z0;
    *z1 = -sin(spin + 0.001) * x0 + cos(spin + 0.001) * z0;
}

bool collision(int a) {

    double dx0 = dragon[0];
    double dy = dragon[1];
    double dz0 = dragon[2];
    double dz1;
    double dx1;
    change_coor(dx0, dz0, &dx1, &dz1);

    double tx0 = RD * cos(-a * (PI / 5) - PI / 10);
    double tz0 = RD * sin(-a * (PI / 5) - PI / 10);
    double tx1;
    double tz1;
    change_coor(tx0, tz0, &tx1, &tz1);

    bool colx = dx1 + 3 > tx1 - 2 && tx1 + 2 > dx1 - 3;
    bool coly = dy + 9 > (-7) && 7 > dy - 5;
    //cout << "coly: " << coly;
    bool colz = dz1 - 1 < tz1 + 1 && tz1 - 1 < dz1 + 4;
    //cout << "   colz: " << colz<<endl;
    return colx && coly && colz;
}

void detection(int a){
    if (collision(a-1)) {
        HP -= 1;
        attack[1] = 1;
        cout << "hp:" << HP << endl;
        if (HP==0){ 
            cout << "dead" << endl;
            play = died;
            SoundEngine->stopAllSounds();
            SoundEngine->play2D("data/MUSIC.mp3", GL_FALSE);
        }
        else {
            speed -= 0.05;
        }

    }
}

void menuredo(void) {
    col += cc * 0.001;
    if (col < -0.01)
        cc = 1;
    else if (col > 0.7)
        cc = -1;
    tt++;
}

void playrep(void)
{
    if (speed < 300) {
        speed += 0.0005;
    }
    spin += ceil(speed / 50) * 0.0005 + 0.0008;
    //cout << spin << endl;

    dragon[0] = RD * cos(-spin);
    dragon[2] = RD * sin(-spin);

    glLightfv(GL_LIGHT1, GL_POSITION, dragon);

    if (jump < 300) {
        jump += 0.8;
        dragon[1] = -0.0006 * jump * jump + 0.1866 * jump;
    }
    else {
        dragon[1] = 0.0;
    }
    if (cheat) {
        double aa = floor(spin / (2 * PI));
        int a = ceil((spin - aa * 2 * PI) / (PI / 5));
        if (attack[0] != a) {
            attack[0] = a;
            attack[1] = 0;
        }
        if (attack[1] == 0) { detection(a); }
    }
    

}

void diedrep(void) {
    tt++;
    if (tt > 4000) {
        play = menu;
        SoundEngine->stopAllSounds();
        SoundEngine->play2D("data/menu.mp3", GL_TRUE);
        tt = 0;
        high = 20.0;
        start = 0;
    }    
    
}

void rep(void) {
    if (play == menu) {
        menuredo();
    }
    else if (play == playing) {
        playrep();
    }
    else {
        diedrep();
    }
    Sleep(1);
    glutPostRedisplay();
}




void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(68.0, (GLfloat)w / (GLfloat)h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glPolygonOffset(-1.0, -1.0);
    glEnable(GL_NORMALIZE);
    compile();
    makeRasterFont();
    SoundEngine->play2D("data/menu.mp3", GL_TRUE);
}

void keyboard(unsigned char key, int x, int y)
{
    if (play == menu) {
        switch (key) {
        case 'c':
            if (cheat) {
                cheat = diappear;
            }
            else {
                cheat = appear;
            }
            break;
        case ' ':
            if (start == 0)
                SoundEngine->play2D("data/bleep.mp3", GL_FALSE);
            start = 1;
            tt = 0;
            break;

        case 27:
            exit(0);
            break;

        default:
            break;
        }

    }
    else if (play == playing) {
        switch (key) {
        case 'c':
            if (cheat) {
                cheat = diappear;
            }
            else {
                cheat = appear;
            }
            break;
        case 'r':
            theda += 0.2;
            glutPostRedisplay();
            break;
        case 'e':
            fin += 0.2;
            glutPostRedisplay();
            break;

        case ' ':
            if (jump >= 300) {
                SoundEngine->play2D("data/jump.mp3", GL_FALSE);
                jump = 0.0;
            }
            break;
        case 27:
            exit(0);
            break;
        }
    }
    else {
        switch (key) {
        case 27:
            exit(0);
            break;
        }
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Dianosaur");
    init();
    glutDisplayFunc(display);
    texture();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(rep);
    glutMainLoop();
    return 0;
}
