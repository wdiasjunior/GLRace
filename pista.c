//
//  pista.c
//  Graphics3D
//
//  Created by Claudio Ramos on 02/06/19.
//  Copyright © 2019 Claudio Ramos. All rights reserved.
//

#include "pista.h"
#include <stdlib.h>
#include <OpenGL/OpenGL.h>
#include "math.h"
#include <GLUT/glut.h>

struct curve {
    float alphaX;
    float alphaY;
    float alphaZ;
};

struct curve pista[200];

float lint (float a, float b, float f) {
    return a + f * (b - a);
}

void initPista() {
    float curve = 0;
    int curveDir = 1;
    for(int i = 0; i < 200; i++) {
        struct curve dir = {
            0, 0, 0
        };
        
        int r = rand() % 100;
        if (i > 30 && curve <= 0 && r > 0) {
            curve = 1;
        }
        
        if (curve > 0) {
            int newDirRand = rand() % 1000;
            
            if (newDirRand > 600 && curve < 0.35f) {
                curveDir *= -1;
                curve = 1;
            }
            
            float alpha = lint(0, 90 * curveDir, ((curve-1)/1)*-1);
            dir.alphaX = alpha;
        }

        if (curve > 0)
            curve -= 0.0005f;
        pista[i] = dir;
    }
}

void renderPista() {
    glPushMatrix();
    
    glColor3d(0, 1, 0);
    
    glPolygonMode( GL_FRONT, GL_LINE );
    glBegin(GL_TRIANGLE_STRIP);

    struct curve currCurve = {
        0, 0 ,0
    };
    
    for(int i = 0; i < 200; i++) {
        struct curve dir = pista[i];
        
        currCurve.alphaX += dir.alphaX;
        currCurve.alphaY += dir.alphaY;
        currCurve.alphaZ += dir.alphaZ;
        
        glVertex3d(-6 + currCurve.alphaX, 0 + currCurve.alphaY, i * -2 + 8 + currCurve.alphaZ);
        glVertex3d( 6 + currCurve.alphaX, 0 + currCurve.alphaY, i * -2 + 8 + currCurve.alphaZ);
    }
    
    glEnd();
    
    glPopMatrix();
}
