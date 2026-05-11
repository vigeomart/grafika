#define _USE_MATH_DEFINES 
#include "sun.h"
#include <GL/gl.h>
#include <math.h>

float time_of_day = 0.0f;     
float sunRadius = 40.0f;      
float light_intensity = 1.0f;

const float MIN_SUN_RADIUS = 10.0f;
const float MAX_SUN_RADIUS = 80.0f; 

void handleSunInput(const Uint8 *state) {
    if (state[SDL_SCANCODE_KP_PLUS] || state[SDL_SCANCODE_EQUALS]) {
        light_intensity += 0.02f;
        if(light_intensity > 3.0f) light_intensity = 3.0f; 
    }
    if (state[SDL_SCANCODE_KP_MINUS] || state[SDL_SCANCODE_MINUS]) {
        light_intensity -= 0.02f;
        if(light_intensity < 0.0f) light_intensity = 0.0f; 
    }
}

void updateTimeAndSun(float delta_time, const Uint8 *state, bool is_time_flowing) {
    if (is_time_flowing) {
        time_of_day += delta_time / 60.0f; 
    } else {
        if (state[SDL_SCANCODE_LEFT])  time_of_day -= delta_time * 0.2f; 
        if (state[SDL_SCANCODE_RIGHT]) time_of_day += delta_time * 0.2f; 
        
        if (state[SDL_SCANCODE_UP])   sunRadius += delta_time * 20.0f;
        if (state[SDL_SCANCODE_DOWN]) sunRadius -= delta_time * 20.0f;
        
        if (sunRadius < MIN_SUN_RADIUS) sunRadius = MIN_SUN_RADIUS;
        if (sunRadius > MAX_SUN_RADIUS) sunRadius = MAX_SUN_RADIUS;
    }

    if (time_of_day < 0.0f) time_of_day = 0.0f;
    if (time_of_day > 1.0f) time_of_day = 1.0f;
}

void applySkyAndLighting() {
    float skyR = 0.5f * (1.0f - time_of_day) + 0.02f * time_of_day;
    float skyG = 0.7f * (1.0f - time_of_day) + 0.02f * time_of_day;
    float skyB = 1.0f * (1.0f - time_of_day) + 0.08f * time_of_day;
    
    glClearColor(skyR, skyG, skyB, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();

    float sunAngleCalc = time_of_day * (M_PI / 2.0f); 
    float sunX = -sinf(sunAngleCalc) * sunRadius; 
    float sunY = cosf(sunAngleCalc) * sunRadius + 10.0f; 
    float sunZ = -20.0f;                 
    
    float current_light = light_intensity * (1.0f - (time_of_day * 0.9f));
    GLfloat lightAmbient[] = { 0.2f * current_light, 0.2f * current_light, 0.2f * current_light, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f * current_light, 0.8f * current_light, 0.8f * current_light, 1.0f };
    GLfloat lightPosition[] = { sunX, sunY, sunZ, 1.0f }; 
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void renderSun(GLuint sunModel) {
    float sunAngleCalc = time_of_day * (M_PI / 2.0f); 
    float sunX = -sinf(sunAngleCalc) * sunRadius; 
    float sunY = cosf(sunAngleCalc) * sunRadius + 10.0f; 
    float sunZ = -20.0f;

    glPushMatrix();
        glDisable(GL_LIGHTING);         
        glEnable(GL_TEXTURE_2D);         
        glTranslatef(sunX, sunY, sunZ);
        
        glScalef(0.00015f, 0.00015f, 0.00015f);        
        glColor3f(1.0f, 1.0f, 1.0f);        
        glCallList(sunModel); 
        
        glEnable(GL_LIGHTING);
    glPopMatrix();
}
