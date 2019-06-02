//
//  main.c
//  Graphics3D
//
//  Created by Claudio Ramos on 21/05/19.
//  Copyright © 2019 Claudio Ramos. All rights reserved.
//
#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include "math.h"
#include "pista.h"
#include "glm/glm.hpp"

#define PI 3.14

GLfloat x = 0;
GLfloat playerX = 0;

//camera
float pitch = 0;
float yaw = 1;

double lastX = 0;
double lastZ = 0;

void secTimer(int value) {
    x += 0.5f;
    glutTimerFunc(10, secTimer, 1);
    
    glutPostRedisplay();
}

void keyboardDown(unsigned char key,
                  int x, int y) {
    if (key == 'D' || key == 'd') {
        yaw += 0.1f;
    }
    
    glutPostRedisplay();
}

void myReshape(int w, int h) {
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, ((float)w)/h, 0.1, 75);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void myDisplay(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
    glPushMatrix();
    gluLookAt(0, 4, lastZ + 12 - x,
              0, 0, 0 - x,
              0, 1, 0);
    
    renderPista();
    
    glPushMatrix();
    glTranslatef(0, 0, -x);
    glColor3f(1, 0, 0);
    glutSolidCube(1);
    glPopMatrix();
    
    glPopMatrix();
    
    glutSwapBuffers();
    
    printf("%f\n", yaw);
}

int main(int argc, char ** argv) {
    initPista();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(350, 50);
    glutCreateWindow(argv[0]);
    
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glutTimerFunc(10, secTimer, 1);
    glutKeyboardFunc(keyboardDown);
    glutMainLoop();
    return 0;
}
