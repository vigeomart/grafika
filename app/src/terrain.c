#define _USE_MATH_DEFINES 
#include "terrain.h"
#include <math.h>

float getHeight(float x, float z) {
    float h = 2.0f * sinf(x * 0.2f) * cosf(z * 0.2f);
    float dist = sqrtf(x*x + z*z);
    if (dist < 3.0f) {
        h -= 1.0f * (3.0f - dist); 
    }
    return h;
}

void drawTerrain(GLuint groundTex) {
    float step = 1.0f; 
    float texScale = 0.5f; 

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, groundTex);
    glColor3f(1.0f, 1.0f, 1.0f); 

    glBegin(GL_QUADS);
    for (float x = -WORLD_SIZE; x < WORLD_SIZE; x += step) {
        for (float z = -WORLD_SIZE; z < WORLD_SIZE; z += step) {
            float h1 = getHeight(x, z);
            float h2 = getHeight(x + step, z);
            float h3 = getHeight(x + step, z + step);
            float h4 = getHeight(x, z + step);
            
            glNormal3f(h1 - h2, step, h1 - h4);

            glTexCoord2f(x * texScale, z * texScale);
            glVertex3f(x, h1, z);
            
            glTexCoord2f((x + step) * texScale, z * texScale);
            glVertex3f(x + step, h2, z);
            
            glTexCoord2f((x + step) * texScale, (z + step) * texScale);
            glVertex3f(x + step, h3, z + step);
            
            glTexCoord2f(x * texScale, (z + step) * texScale);
            glVertex3f(x, h4, z + step);
        }
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
