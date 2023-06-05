//
//  main.cpp
//  miffy_modeling
//
//  Created by 김정우 on 2023/06/05.
//

#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GL/glut.h>

#include "ex_1.h"

void myDisplay() {
    //이전 frame에서 남아있을 수 있기 때문에 먼저 frameBuffer의 메모리 clear
    glClear(GL_COLOR_BUFFER_BIT); //default color는 black으로 됨
    glLoadIdentity(); //matrix reset
    
    glColor3f(1.0, 1.0, 0.0);
    glutSolidTeapot(0.5);
    glColor3f(1.0, 0.0, 0.0);
    glutWireTeapot(0.5);
    
    glFlush(); //draw 끝나고 frame에 있는 frameBuffer clear
}

int main(int argc, char**argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    
    glutCreateWindow("Example 5");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    glutDisplayFunc(myDisplay5);
    
    glutMainLoop();
}
