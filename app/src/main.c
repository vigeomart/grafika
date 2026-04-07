#define _USE_MATH_DEFINES 
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void drawCube() {
    glBegin(GL_QUADS);
    // Elülső oldal (Piros)
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); glVertex3f( 1.0f, -1.0f,  1.0f); glVertex3f( 1.0f,  1.0f,  1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    // Hátsó oldal (Zöld)
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    // Felső oldal (Kék)
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); glVertex3f(-1.0f,  1.0f,  1.0f); glVertex3f( 1.0f,  1.0f,  1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    // Alsó oldal (Sárga)
    glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); glVertex3f( 1.0f, -1.0f, -1.0f); glVertex3f( 1.0f, -1.0f,  1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    // Jobb oldal (Lila)
    glColor3f(1.0f, 0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); glVertex3f( 1.0f,  1.0f,  1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    // Bal oldal (Cián)
    glColor3f(0.0f, 1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); glVertex3f(-1.0f, -1.0f,  1.0f); glVertex3f(-1.0f,  1.0f,  1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();
}

void drawFloor() {
    glBegin(GL_LINES);
    glColor3f(0.4f, 0.4f, 0.4f); 
    for(float i = -20.0f; i <= 20.0f; i += 1.0f) {
        glVertex3f(-20.0f, -1.0f, i);
        glVertex3f( 20.0f, -1.0f, i);
    
        glVertex3f(i, -1.0f, -20.0f);
        glVertex3f(i, -1.0f,  20.0f);
    }
    glEnd();
}

int main(int argc, char* argv[])
{
    SDL_Window *window;
    SDL_Event event;
    SDL_GLContext context;
    bool need_run = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return 1;

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    window = SDL_CreateWindow("Jatek", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);

    glViewport(0, 0, 800, 600);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -0.75, 0.75, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);

    float camX = 0.0f;       
    float camZ = 5.0f;       
    float camAngle = 0.0f;   
    const float moveSpeed = 0.15f; 
    const float rotSpeed = 2.5f;  
    while (need_run)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                need_run = false;
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        float rad = camAngle * M_PI / 180.0f; 
        
        if (state[SDL_SCANCODE_W]) {
            camX += sin(rad) * moveSpeed;
            camZ -= cos(rad) * moveSpeed;
        }
        if (state[SDL_SCANCODE_S]) {
            camX -= sin(rad) * moveSpeed;
            camZ += cos(rad) * moveSpeed;
        }
        
        if (state[SDL_SCANCODE_A]) {
            camX -= cos(rad) * moveSpeed; 
            camZ -= sin(rad) * moveSpeed;
        }
        if (state[SDL_SCANCODE_D]) {
            camX += cos(rad) * moveSpeed; 
            camZ += sin(rad) * moveSpeed;
        }

        if (state[SDL_SCANCODE_LEFT]) {
            camAngle -= rotSpeed;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            camAngle += rotSpeed;
        }
        
        if (camAngle >= 360.0f) camAngle -= 360.0f;
        if (camAngle < 0.0f) camAngle += 360.0f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glLoadIdentity(); 

        glRotatef(camAngle, 0.0f, 1.0f, 0.0f); 
        glTranslatef(-camX, 0.0f, -camZ);       

        drawFloor(); 
        drawCube();

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}