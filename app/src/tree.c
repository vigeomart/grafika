#define _USE_MATH_DEFINES 
#include "tree.h"
#include "terrain.h"
#include <GL/gl.h>
#include <math.h>
#include <stdlib.h>

float treePositions[NUM_TREES][2];
int placedTrees = 0;

void generateTrees(float worldSize) {
    float minDist = 2.2f; 
    int attempts = 0; 
    placedTrees = 0;
    while (placedTrees < NUM_TREES && attempts < 3000) {
        float newX = ((float)(rand() % ((int)worldSize * 20)) / 10.0f) - worldSize;
        float newZ = ((float)(rand() % ((int)worldSize * 20)) / 10.0f) - worldSize;
        bool collision = false;
        
        if (sqrt(newX*newX + (newZ-5.0f)*(newZ-5.0f)) < 3.0f) collision = true; // Kezdőpont
        for (int j = 0; j < placedTrees; j++) {
            if (sqrt(pow(newX - treePositions[j][0], 2) + pow(newZ - treePositions[j][1], 2)) < minDist) { 
                collision = true; break; 
            }
        }
        if (!collision) {
            treePositions[placedTrees][0] = newX;
            treePositions[placedTrees][1] = newZ;
            placedTrees++;
        }
        attempts++;
    }
}

bool checkTreeCollision(float x, float z, float radius) {
    for (int i = 0; i < placedTrees; i++) {
        if (sqrt(pow(x - treePositions[i][0], 2) + pow(z - treePositions[i][1], 2)) < radius) { 
            return true; 
        }
    }
    return false;
}

void drawTree() {
    glColor3f(0.4f, 0.2f, 0.0f); 
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f(-0.2f, 0.0f,  0.2f); glVertex3f( 0.2f, 0.0f,  0.2f); glVertex3f( 0.2f, 1.5f,  0.2f); glVertex3f(-0.2f, 1.5f,  0.2f);
    glNormal3f(0.0f, 0.0f, -1.0f); glVertex3f(-0.2f, 0.0f, -0.2f); glVertex3f(-0.2f, 1.5f, -0.2f); glVertex3f( 0.2f, 1.5f, -0.2f); glVertex3f( 0.2f, 0.0f, -0.2f);
    glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(-0.2f, 0.0f, -0.2f); glVertex3f(-0.2f, 0.0f,  0.2f); glVertex3f(-0.2f, 1.5f,  0.2f); glVertex3f(-0.2f, 1.5f, -0.2f);
    glNormal3f(1.0f, 0.0f, 0.0f); glVertex3f( 0.2f, 0.0f, -0.2f); glVertex3f( 0.2f, 1.5f, -0.2f); glVertex3f( 0.2f, 1.5f,  0.2f); glVertex3f( 0.2f, 0.0f,  0.2f);
    glEnd();

    glColor3f(0.1f, 0.6f, 0.2f); 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 1.0f, 1.0f); glVertex3f(-0.8f, 1.5f,  0.8f); glVertex3f( 0.8f, 1.5f,  0.8f); glVertex3f( 0.0f, 4.0f,  0.0f);
    glNormal3f(0.0f, 1.0f, -1.0f); glVertex3f( 0.8f, 1.5f, -0.8f); glVertex3f(-0.8f, 1.5f, -0.8f); glVertex3f( 0.0f, 4.0f,  0.0f);
    glNormal3f(-1.0f, 1.0f, 0.0f); glVertex3f(-0.8f, 1.5f, -0.8f); glVertex3f(-0.8f, 1.5f,  0.8f); glVertex3f( 0.0f, 4.0f,  0.0f);
    glNormal3f(1.0f, 1.0f, 0.0f); glVertex3f( 0.8f, 1.5f,  0.8f); glVertex3f( 0.8f, 1.5f, -0.8f); glVertex3f( 0.0f, 4.0f,  0.0f);
    glEnd();
}

void renderAllTrees() {
    for(int i = 0; i < placedTrees; i++) {
        glPushMatrix();
        float h = getHeight(treePositions[i][0], treePositions[i][1]);
        glTranslatef(treePositions[i][0], h, treePositions[i][1]);
        
        glDisable(GL_TEXTURE_2D); 
        drawTree();
        glEnable(GL_TEXTURE_2D);
        
        glPopMatrix();
    }
}