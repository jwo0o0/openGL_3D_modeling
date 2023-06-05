//
//  ex_1.cpp
//  miffy_modeling
//
//  Created by 김정우 on 2023/06/05.
//

#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GL/glut.h>
#include <math.h>
#define Pi 3.14

void myDisplay2() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); //matrix reset
    
    gluOrtho2D(0.0, 100.0, 0.0, 100.0);
    glColor3f(1.0, 0.0, 0.0);
    glRectf(30.0, 30.0, 50.0, 50.0);
    glutSwapBuffers(); //내부적으로 glFlush() 호출
}

void myDisplay3() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    GLfloat size[2];
    GLfloat angle;
    glColor3f(1.0, 1.0, 1.0);
    glGetFloatv(GL_SMOOTH_POINT_SIZE_RANGE, size);
    glPointSize((size[1]-size[0])/2.0 + size[0]);
    glBegin(GL_POINTS);
    for (angle = 0.0; angle < 2.0 * Pi; angle += Pi / 30.0)
        glVertex3f(0.5 * cos(angle), 0.5 * sin(angle), 0.0);
    glEnd();
    glFlush();
}

void myDisplay4() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    glBegin(GL_LINES);
    glLineWidth(5.0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);
    glEnd();
    glFlush();
}

void myDisplay5() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    //기본이 GL_SMOOTH
    //glShadeModel(GL_SMOOTH);
    glShadeModel(GL_FLAT);
    
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, -0.5, 0.0);
    glEnd();
    glFlush();
}

