#include <iostream>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
#include "SOIL.h"

#define TEX_BLACK 1
#define TEX_BODY 2
#define TEX_SKIN 3
#define TEX_ARM 4
#define TEX_FOOT 5
#define TEX_FACE 7
#define TEX_EAR 8
#define TEX_BALL 9
#define PI 3.141592
#define TRUE 0
#define FALSE 1

void createCircle(GLfloat, GLfloat, GLfloat);
void createCylinder(GLfloat,GLfloat,GLfloat);
void createCylinder_tex(GLfloat,GLfloat,GLfloat, int, int);
int LoadGLTextures(const char*,int);
void createSphere(GLfloat);
GLuint LoadBMPFile(const char* Filename);
float x, y, z;
float radius;
float theta;
float phi;
float zoom = 100.0;

int beforeX, beforeY;

GLuint texture[10];

void InitLight()
{
    GLfloat ambientLight[4];
    GLfloat diffuseLight[4];
    GLfloat lightPosition[4];
    GLfloat specular[4];
    GLfloat yrot;

    ambientLight[0] = 0.3f;
    ambientLight[1] = 0.3f;
    ambientLight[2] = 0.3f;
    ambientLight[3] = 1.0f;

    diffuseLight[0] = 0.7f;
    diffuseLight[1] = 0.7f;
    diffuseLight[2] = 0.7f;
    diffuseLight[3] = 1.0f;

    lightPosition[0] = 0.0f;
    lightPosition[1] = 0.0f;
    lightPosition[2] = 5.0f;
    lightPosition[3] = 1.0f;

    specular[0] = 1.0f;
    specular[1] = 1.0f;
    specular[2] = 1.0f;
    specular[3] = 1.0f;

    yrot = 0.0f;

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glFrontFace(GL_CCW);

    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glEnable(GL_LIGHT0);
}

int init (void)
{
    // texture loading
    LoadGLTextures((char *)"/Users/jwo0o0/Desktop/texture/black.jpg",TEX_BLACK);
    LoadGLTextures((char *)"/Users/jwo0o0/Desktop/texture/body.jpg",TEX_BODY);
    LoadGLTextures((char *)"/Users/jwo0o0/Desktop/texture/white.jpg",TEX_SKIN);
    LoadGLTextures((char *)"/Users/jwo0o0/Desktop/texture/arm.jpg",TEX_ARM);
    LoadGLTextures((char *)"/Users/jwo0o0/Desktop/texture/white.jpg",TEX_FOOT);
    LoadGLTextures((char *)"/Users/jwo0o0/Desktop/texture/white.jpg",TEX_FACE);
    LoadGLTextures((char *)"/Users/jwo0o0/Desktop/texture/white.jpg",TEX_EAR);
    LoadGLTextures((char *)"/Users/jwo0o0/Desktop/texture/balloon.jpg", TEX_BALL);

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.2039f, 0.3843f, 0.7490f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    return TRUE;
}

void reshape (int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom, 1.0, 1.0, 100.0);

    radius = 10.0;
    theta = 10.0;
    phi = -10.0;
}
void display (void)
{
    // for zoom
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom, 1.0, 1.0, 100.0);

    x = -radius * cos(phi) * cos(theta);
    y = -radius * cos(phi) * sin(theta);
    z = radius * sin(phi);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    
    // modeling & texure mapping
    glBindTexture(GL_TEXTURE_2D, texture[TEX_ARM]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(1.9, 0.0, 0);
    glRotatef(30, 0.0, -1.0, 0.0);
    createCylinder_tex(0.6, 0.6, 1.5,TEX_SKIN,TEX_BLACK); // right arm
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_ARM]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.9, 0.0, 0);
    glRotatef(-30, 0.0, -1.0, 0.0);
    createCylinder_tex(0.6, 0.6, 1.5,TEX_SKIN,TEX_BLACK); // left arm
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_ARM]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.2, 0.0, 1.2);
    createSphere(0.6f); // left sholder

    glBindTexture(GL_TEXTURE_2D, texture[TEX_ARM]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(1.2, 0.0, 1.2);
    createSphere(0.6f); // right sholder
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.8, 0.0, -0.3);
    createSphere(0.6f); // left hand
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(1.8, 0.0, -0.3);
    createSphere(0.6f); // right hand

    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.55, 0.0, -1.6);
    createCylinder(0.6, 0.4, 2.5); // ieft leg

    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.55, 0.0, -1.6);
    createCylinder(0.6, 0.4, 2.5); // right leg
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_FOOT]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.6, 0.0, -1.7);
    createSphere(0.63f); // right shoe
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_FOOT]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.6, 0.0, -1.7);
    createSphere(0.63f); // left shoe

    glBindTexture(GL_TEXTURE_2D, texture[TEX_BODY]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -1.2);
    createCylinder_tex(2.3,1.3,2.8,TEX_BLACK,TEX_BLACK);   // body

    glBindTexture(GL_TEXTURE_2D, texture[TEX_FACE]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 3.0);
    glScalef(0.9, 1.0, 1.0);
    createSphere(2.0f); // head
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.7, -1.7, 2.8);
    createSphere(0.2f); // left eye
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.7, -1.7, 2.8);
    createSphere(0.2f); // right eye
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.2, -1.8, 2);
    glRotatef(60, 0.0, -1.0, 0.0);
    createCylinder_tex(0.05, 0.05, 0.5,TEX_SKIN,TEX_BLACK); // mouth
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.2, -1.8, 2);
    glRotatef(-60, 0.0, -1.0, 0.0);
    createCylinder_tex(0.05, 0.05, 0.5,TEX_SKIN,TEX_BLACK); // mouth
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_ARM]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.9, 0.0, 0);
    glRotatef(-30, 0.0, -1.0, 0.0);
    createCylinder_tex(0.6, 0.6, 1.5,TEX_SKIN,TEX_BLACK); // left arm

    glBindTexture(GL_TEXTURE_2D, texture[TEX_EAR]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.7, 0.0, 5.2);
    glRotatef(-80, 0.0, -1.0, 0.0);
    glScalef(4.0, 1.2, 1.3);
    createSphere(0.4f); // right pony

    glBindTexture(GL_TEXTURE_2D, texture[TEX_EAR]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.7, 0.0, 5.2);
    glRotatef(80, 0.0, -1.0, 0.0);
    glScalef(4.0, 1.2, 1.3);
    createSphere(0.4f); // left pony
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.3, 0.0, -0.5);
    glRotatef(-15, 0.0, -1.0, 0.0);
    createCylinder_tex(0.05, 0.05, 6.5,TEX_SKIN,TEX_BLACK); // ballon line
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_BALL]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(4, 0.0, 5.5);
    createCylinder_tex(0.5,0,1.0,TEX_BLACK,TEX_BLACK);   // ballon bottom
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_BALL]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(4, 0, 7.5);
    createSphere(1.5f); // ballon top
    
    glFlush ();
    glutSwapBuffers();
}

// ZOOM
void keyboard( unsigned char key, int x, int y )
{
    switch(key)
    {
        case 'a':
            zoom--;
            break;
        case 'z':
            zoom++;
            break;
    }

}

// VIEWPOINT 1
void processMouse(int button, int state, int x, int y)
{

    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            beforeX = x;
            beforeY = y;
        }
    }
}

// VIEWPOINT 2
void processMouseMotion(int x, int y)
{
    if(abs(beforeX-x) > abs(beforeY-y)){
        if(beforeX < x)
        {
            theta -= 0.1;
        }else if(beforeX > x){
            theta += 0.1;
        }
    }else {
        if(beforeY > y){
            phi -= 0.1;
        }else if(beforeY < y){
            phi -= 0.1;
        }
    }

    beforeX = x;
    beforeY = y;

    glutPostRedisplay();

    if ( theta > 2.0 * PI )
        theta -= (2.0 * PI);
    else if ( theta < 0.0 )
        theta += (2.0 * PI);
}

void createSphere(GLfloat r)
{
GLUquadricObj *sphere = gluNewQuadric();
  
  gluQuadricTexture(sphere, GL_TRUE);
  gluQuadricDrawStyle(sphere, GLU_FILL);
  glPolygonMode(GL_FRONT, GL_FILL);
  gluQuadricNormals(sphere, GLU_SMOOTH);
  gluSphere(sphere,r,36 ,18);
}

void createCylinder_tex(GLfloat bottom, GLfloat top, GLfloat height, int texture1, int texture2)
{
  GLUquadricObj *cylinder = gluNewQuadric();
  
  gluQuadricTexture(cylinder, GL_TRUE);
  gluQuadricDrawStyle(cylinder, GLU_FILL);
  glPolygonMode(GL_FRONT, GL_FILL);
  gluQuadricNormals(cylinder, GLU_SMOOTH);
  gluCylinder(cylinder, bottom, top, height, 20, 100);
  
  glBindTexture(GL_TEXTURE_2D, texture[texture1]);
  createCircle(bottom, 1.0f, 0.0f);
  glBindTexture(GL_TEXTURE_2D, texture[texture2]);
  createCircle(top, -1.0f, height);
}

void createCylinder(GLfloat bottom, GLfloat top, GLfloat height)
{
  GLUquadricObj *cylinder = gluNewQuadric();
  
  gluQuadricTexture(cylinder, GL_TRUE);
  gluQuadricDrawStyle(cylinder, GLU_FILL);
  glPolygonMode(GL_FRONT, GL_FILL);
  gluQuadricNormals(cylinder, GLU_SMOOTH);
  gluCylinder(cylinder, bottom, top, height, 20, 100);
  
  createCircle(bottom, 1.0f, 0.0f);
  createCircle(top, -1.0f, height);
}

// for cylinder top & bottom
void createCircle(GLfloat r, GLfloat pos, GLfloat move){
  GLfloat centerx = 0, centery = 0, centerz = 0;
  GLfloat x, y, angle;

  glBegin(GL_TRIANGLE_FAN);
  glTexCoord2f(0.0f, 0.0f);
  glNormal3f(0.0f, 0.0f, pos);
  glVertex3f(centerx, centery, centerz + move);
  for(angle = (2.0f*PI); angle > 0.0f; angle -= (PI/8.0f))
  {
      x = centerx + r*sin(angle);
      y = centery + r*cos(angle);
      glTexCoord2f(x, y);
      glNormal3f(0.0f, 0.0f, pos);
      glVertex3f(x, y, centerz + move);
  }
  glEnd();
}


GLuint LoadBMPFile(const char* Filename)
{
    GLuint textureID = 0;
    int width, height;
    
    unsigned char* image = SOIL_load_image(Filename, &width, &height, 0, SOIL_LOAD_RGB);
    if (image == NULL)
    {
        printf("Failed to load BMP file: %s\n", Filename);
        return 0;
    }
    
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    SOIL_free_image_data(image);
    
    return textureID;
}

int LoadGLTextures(const char* filename, int num)
{
    GLuint textureID = LoadBMPFile(filename);
    if (textureID == 0)
    {
        return FALSE;
    }
    
    texture[num] = textureID;
    
    return TRUE;
}



int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (1000, 1000);
    glutCreateWindow ("Miffy");
    init();
    InitLight();
    glClearColor(0.2039f, 0.3843f, 0.7490f, 1.0f);
    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseMotion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
