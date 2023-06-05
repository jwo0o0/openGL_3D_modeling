#include <iostream>
#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
#define TEX_BLACK 1
#define TEX_BODY 2
#define TEX_SKIN 3
#define TEX_ARM 4
#define TEX_SHOE 5
#define TEX_EYE 6
#define TEX_FACE 7
#define TEX_HAIR 8
#define PI 3.141592
#define TRUE 0
#define FALSE 1

void createCircle(GLfloat, GLfloat, GLfloat);
void createCylinder(GLfloat,GLfloat,GLfloat);
void createCylinder_tex(GLfloat,GLfloat,GLfloat, int, int);
//int LoadGLTextures(char*,int);
void createSphere(GLfloat);
//AUX_RGBImageRec *LoadBMPFile(char *Filename);
float x, y, z;
float radius;
float theta;
float phi;
float zoom = 90.0;

int beforeX, beforeY;

GLuint texture[10];                          // ≈ÿΩ∫√≥ ¿˙¿Â∞¯∞£

//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);                // WndProc º±æ

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

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //π‡¿∫ »∏ªˆ¿ª πË∞Êªˆ¿∏∑Œ º≥¡§
    glFrontFace(GL_CCW); //π›Ω√∞ËπÊ«‚¿∏∑Œ ∞®¿∫ ∆˙∏Æ∞Ô¿Ã æ’∏È

    glEnable(GL_LIGHTING); //¡∂∏Ì ƒ—±‚
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //º≥¡§
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); //º≥¡§
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specular); //º≥¡§
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); //º≥¡§
    glEnable(GL_LIGHT0); // 0π¯ ¡∂∏Ì ªÁøÎ
}

int init (void)
{
    // texture loading
//    LoadGLTextures((char *)"Data/black.bmp",TEX_BLACK);
//    LoadGLTextures((char *)"Data/body.bmp",TEX_BODY);
//    LoadGLTextures((char *)"Data/skin.bmp",TEX_SKIN);
//    LoadGLTextures((char *)"Data/arm.bmp",TEX_ARM);
//    LoadGLTextures((char *)"Data/shoe.bmp",TEX_SHOE);
//    LoadGLTextures((char *)"Data/eye.bmp",TEX_EYE);
//    LoadGLTextures((char *)"Data/face.bmp",TEX_FACE);
//    LoadGLTextures((char *)"Data/hair.bmp",TEX_HAIR);

    glEnable(GL_TEXTURE_2D);                        // ≈ÿΩ∫√≥ ∏≈«Œ¿ª »∞º∫»≠Ω√≈¥ ( ªıƒ⁄µÂ )
    glShadeModel(GL_SMOOTH);                        // ∫ŒµÂ∑ØøÓ Ω¶¿Ãµ˘¿ª »∞º∫»≠Ω√≈¥
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                    // ∞À¿∫ªˆ πË∞Ê
    glClearDepth(1.0f);                            // ±Ì¿Ãπˆ∆€ º≥¡§
    glEnable(GL_DEPTH_TEST);                        // ±Ì¿Ã≈◊Ω∫∆Æ∏¶ ƒ‘
    glDepthFunc(GL_LEQUAL);                            // ±Ì¿Ã≈◊Ω∫∆Æ ¡æ∑˘
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);            // ø¯±Ÿ ∞ËªÍ
    return TRUE;                                // √ ±‚»≠ º∫∞¯
}

void reshape (int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
//    glOrtho (-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    gluPerspective(zoom, 1.0, 1.0, 100.0);  // ∏÷∞Ì ∞°±ÓøÚ¿ª «•«ˆ.

    radius = 10.0;
    theta = 10.0;
    phi = -10.0;
}
void display (void)
{
    // for zoom
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom, 1.0, 1.0, 100.0);  // ∏÷∞Ì ∞°±ÓøÚ¿ª «•«ˆ.

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
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.2, 0.0, 1.2);
    createSphere(0.6f); // left sholder

    glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);
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
    glTranslatef(-0.6, 0.0, -2.2);
    createCylinder(0.6, 0.4, 3.0); // ieft leg

    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.6, 0.0, -2.2);
    createCylinder(0.6, 0.4, 3.0); // right leg
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_SHOE]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.6, 0.0, -2.1);
    createSphere(0.6f); // right shoe
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_SHOE]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.6, 0.0, -2.1);
    createSphere(0.6f); // left shoe

    glBindTexture(GL_TEXTURE_2D, texture[TEX_BODY]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -1.2);
    createCylinder_tex(2.3,1.3,2.8,TEX_BLACK,TEX_BLACK);   // body
    
//    glBindTexture(GL_TEXTURE_2D, texture[TEX_BODY]);
//    glLoadIdentity();
//    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
//    glTranslatef(0.0, 0.0, 0.5);
//    createCylinder_tex(2.3,1.3,1.0,TEX_BLACK,TEX_BLACK);   // body top

    glBindTexture(GL_TEXTURE_2D, texture[TEX_FACE]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 3.0);
    glScalef(0.9, 1.0, 1.0);
    createSphere(2.0f); // head
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.7, 1.7, 2.8);
    createSphere(0.2f); // left eye
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.7, 1.7, 2.8);
    createSphere(0.2f); // right eye
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_ARM]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 1.8, 2);
    glRotatef(60, 0.0, -1.0, 0.0);
    createCylinder_tex(0.07, 0.07, 0.7,TEX_SKIN,TEX_BLACK); // right arm
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_ARM]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.3, 1.8, 2);
    glRotatef(-60, 0.0, -1.0, 0.0);
    createCylinder_tex(0.07, 0.07, 0.7,TEX_SKIN,TEX_BLACK); // right arm
    
    glBindTexture(GL_TEXTURE_2D, texture[TEX_ARM]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.9, 0.0, 0);
    glRotatef(-30, 0.0, -1.0, 0.0);
    createCylinder_tex(0.6, 0.6, 1.5,TEX_SKIN,TEX_BLACK); // left arm

    glBindTexture(GL_TEXTURE_2D, texture[TEX_HAIR]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.7, 0.0, 5.2);
    glRotatef(-80, 0.0, -1.0, 0.0);
    glScalef(4.0, 1.2, 1.3);
    createSphere(0.4f); // right pony

    glBindTexture(GL_TEXTURE_2D, texture[TEX_HAIR]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.7, 0.0, 5.2);
    glRotatef(80, 0.0, -1.0, 0.0);
    glScalef(4.0, 1.2, 1.3);
    createSphere(0.4f); // left pony
    
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

    if ( theta > 2.0 * PI ) // 360µµ ≥—æÓ∞°∏È
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

void createSphereEye(GLfloat r)
{
    GLUquadricObj *sphere = gluNewQuadric();

    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricDrawStyle(sphere, GLU_FILL);
    glPolygonMode(GL_FRONT, GL_FILL);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    
    GLfloat diffuseColor[] = {0.0f, 0.0f, 0.0f, 1.0f};  // 검정색으로 설정
    GLfloat ambientColor[] = {0.0f, 0.0f, 0.0f, 1.0f};  // 검정색으로 설정

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);

    gluSphere(sphere, r, 36, 18);

    gluDeleteQuadric(sphere);
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
  createCircle(bottom, 1.0f, 0.0f); // ø¯±‚µ’ πÿ∏È
  glBindTexture(GL_TEXTURE_2D, texture[texture2]);
  createCircle(top, -1.0f, height); // ø¯±‚µ’ ¿≠∏È
}

void createCylinder(GLfloat bottom, GLfloat top, GLfloat height)
{
  GLUquadricObj *cylinder = gluNewQuadric();
  
  gluQuadricTexture(cylinder, GL_TRUE);
  gluQuadricDrawStyle(cylinder, GLU_FILL);
  glPolygonMode(GL_FRONT, GL_FILL);
  gluQuadricNormals(cylinder, GLU_SMOOTH);

  gluCylinder(cylinder, bottom, top, height, 20, 100);
    
  
  createCircle(bottom, 1.0f, 0.0f); // ø¯±‚µ’ πÿ∏È
  createCircle(top, -1.0f, height); // ø¯±‚µ’ ¿≠∏È
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

// texure load 1
//AUX_RGBImageRec *LoadBMPFile(char *Filename)
//{
//    FILE *File=NULL;                            // ∆ƒ¿œ «⁄µÈ
//    if (!Filename)                                // ∆ƒ¿œ¿Ã∏ß¿Ã ¿¸¥ﬁµ«æ˙¥¬¡ˆ »Æ¿Œ
//   {
//       return NULL;                            // ±◊∑∏¡ˆ æ ¥Ÿ∏È NULL¿ª π›»Ø
//   }
//
//    File=fopen(Filename,"r");                        // ∆ƒ¿œ¿Ã ¡∏¿Á«œ¥¬¡ˆ »Æ¿Œ
//    if (File)                                // ∆ƒ¿œ¿Ã ¡∏¿Á«œ¥¬∞°?
//   {
//       fclose(File);                            // «⁄µÈ¿ª ¥›¿Ω
//       return auxDIBImageLoad(Filename);                // ∫Ò∆Æ∏ ¿ª ¿–æÓµÈ¿Ã∞Ì ∆˜¿Œ≈Õ∏¶ π›»Ø
//   }
//
//    return NULL;
//}

// texure load 2
//int LoadGLTextures(char* filename, int num)
//{
//    int Status=FALSE;                            // ªÛ≈¬ «•Ω√±‚
//    AUX_RGBImageRec *TextureImage[1];                    // ≈ÿΩ∫√≥øÎ ¿˙¿Â∞¯∞£¿ª ∏∏µÎ
//    memset(TextureImage,0,sizeof(void *)*1);                // ∆˜¿Œ≈Õ∏¶ NULL∑Œ º≥¡§

    //printf("%s\n",filename);
//    if (TextureImage[0]=LoadBMPFile(filename))
//    {
//       Status=TRUE;                            // Status∏¶ TRUE∑Œ º≥¡§
//       glGenTextures(1, &texture[num]);                    // ≈ÿΩ∫√≥∏¶ ∏∏µÎ
//
//       // ∫Ò∆Æ∏ ¿∏∑Œ∫Œ≈Õ ∞°¡Æø¬ µ•¿Ã≈Õ∏¶ ªÁøÎ«— ¿œπ›¿˚¿Œ ≈ÿΩ∫√≥ ª˝º∫
//       glBindTexture(GL_TEXTURE_2D, texture[num]);
//       // ≈ÿΩ∫√≥∏¶ ∏∏µÁ¥Ÿ
//       glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
//       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    // º±«¸ « ≈Õ∏µ
//       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);    // º±«¸ « ≈Õ∏µ
//    }
//
//     if (TextureImage[0])                            // ≈ÿΩ∫√≥∞° ¡∏¿Á«œ¥¬¡ˆ »Æ¿Œ
//   {
//       if (TextureImage[0]->data)                    // ≈ÿΩ∫√≥ ¿ÃπÃ¡ˆ∞° ¡∏¿Á«œ¥¬¡ˆ »Æ¿Œ
//       {
//           free(TextureImage[0]->data);                // ≈ÿΩ∫√≥ ¿ÃπÃ¡ˆ ∏ﬁ∏∏Æ∏¶ «ÿ¡¶
//       }
//
//       free(TextureImage[0]);                        // ¿ÃπÃ¡ˆ ±∏¡∂√º∏¶ «ÿ¡¶
//   }
//
//    return Status;                                // Status∏¶ π›»Ø
//}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (1000, 1000);
    glutCreateWindow ("IU YOU&I ver");
    init();
    InitLight();
    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseMotion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
