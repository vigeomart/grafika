#define _USE_MATH_DEFINES 
#include "camera.h"
#include "tree.h"
#include "terrain.h"
#include <GL/gl.h>
#include <math.h>

float camX = 0.0f, camZ = 5.0f;
float camAngle = 0.0f, pitch = 0.0f;

void updateCameraRotation(float xrel, float yrel, float sensitivity) {
    camAngle += xrel * sensitivity;
    pitch += yrel * sensitivity;
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
}

void updateCameraPosition(const Uint8 *state, float speed, float mapLimit, float playerRadius) {
    float rad = camAngle * M_PI / 180.0f;
    float moveX = 0.0f;
    float moveZ = 0.0f;

    if (state[SDL_SCANCODE_W]) { moveX += sin(rad) * speed; moveZ -= cos(rad) * speed; }
    if (state[SDL_SCANCODE_S]) { moveX -= sin(rad) * speed; moveZ += cos(rad) * speed; }
    if (state[SDL_SCANCODE_A]) { moveX -= cos(rad) * speed; moveZ -= sin(rad) * speed; }
    if (state[SDL_SCANCODE_D]) { moveX += cos(rad) * speed; moveZ += sin(rad) * speed; }

    float nextX = camX + moveX;
    if (nextX >= -mapLimit && nextX <= mapLimit && !checkTreeCollision(nextX, camZ, playerRadius)) {
        camX = nextX;
    }

    float nextZ = camZ + moveZ;
    if (nextZ >= -mapLimit && nextZ <= mapLimit && !checkTreeCollision(camX, nextZ, playerRadius)) {
        camZ = nextZ;
    }
}

void applyCameraView(float eyeLevel) {
    float groundHeight = getHeight(camX, camZ);
    float currentCamY = groundHeight + eyeLevel;
    glRotatef(pitch, 1.0f, 0.0f, 0.0f);
    glRotatef(camAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-camX, -currentCamY, -camZ); 
}