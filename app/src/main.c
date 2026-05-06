#define _USE_MATH_DEFINES 
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h> 
#include <time.h>   

#define NUM_TREES 70 
#define WORLD_SIZE 40.0f 

float getHeight(float x, float z) {
    float h = 2.0f * sinf(x * 0.2f) * cosf(z * 0.2f);
    float dist = sqrtf(x*x + z*z);
    if (dist < 3.0f) {
        h -= 1.0f * (3.0f - dist); 
    }
    return h;
}

void drawTerrain() {
    float step = 1.0f; 
    glBegin(GL_QUADS);
    for (float x = -WORLD_SIZE; x < WORLD_SIZE; x += step) {
        for (float z = -WORLD_SIZE; z < WORLD_SIZE; z += step) {
            float h1 = getHeight(x, z);
            float h2 = getHeight(x + step, z);
            float h3 = getHeight(x + step, z + step);
            float h4 = getHeight(x, z + step);
            
            // Normálvektor számítása a fényekhez (közelítő érték a magasságkülönbségekből)
            glNormal3f(h1 - h2, step, h1 - h4);

            glColor3f(0.2f, 0.4f + h1 * 0.1f, 0.2f); 
            glVertex3f(x, h1, z);
            glVertex3f(x + step, h2, z);
            glVertex3f(x + step, h3, z + step);
            glVertex3f(x, h4, z + step);
        }
    }
    glEnd();
}

void drawTree() {
    // Törzs (barna)
    glColor3f(0.4f, 0.2f, 0.0f); 
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.2f, 0.0f,  0.2f); glVertex3f( 0.2f, 0.0f,  0.2f);
    glVertex3f( 0.2f, 1.5f,  0.2f); glVertex3f(-0.2f, 1.5f,  0.2f);
    
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-0.2f, 0.0f, -0.2f); glVertex3f(-0.2f, 1.5f, -0.2f);
    glVertex3f( 0.2f, 1.5f, -0.2f); glVertex3f( 0.2f, 0.0f, -0.2f);
    
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.2f, 0.0f, -0.2f); glVertex3f(-0.2f, 0.0f,  0.2f);
    glVertex3f(-0.2f, 1.5f,  0.2f); glVertex3f(-0.2f, 1.5f, -0.2f);
    
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f( 0.2f, 0.0f, -0.2f); glVertex3f( 0.2f, 1.5f, -0.2f);
    glVertex3f( 0.2f, 1.5f,  0.2f); glVertex3f( 0.2f, 0.0f,  0.2f);
    glEnd();

    // Lomb (zöld)
    glColor3f(0.1f, 0.6f, 0.2f); 
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 1.0f, 1.0f); // Közelítő normálvektorok
    glVertex3f(-0.8f, 1.5f,  0.8f); glVertex3f( 0.8f, 1.5f,  0.8f); glVertex3f( 0.0f, 4.0f,  0.0f);
    glNormal3f(0.0f, 1.0f, -1.0f);
    glVertex3f( 0.8f, 1.5f, -0.8f); glVertex3f(-0.8f, 1.5f, -0.8f); glVertex3f( 0.0f, 4.0f,  0.0f);
    glNormal3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(-0.8f, 1.5f, -0.8f); glVertex3f(-0.8f, 1.5f,  0.8f); glVertex3f( 0.0f, 4.0f,  0.0f);
    glNormal3f(1.0f, 1.0f, 0.0f);
    glVertex3f( 0.8f, 1.5f,  0.8f); glVertex3f( 0.8f, 1.5f, -0.8f); glVertex3f( 0.0f, 4.0f,  0.0f);
    glEnd();
}

int main(int argc, char* argv[])
{
    SDL_Window *window;
    SDL_Event event;
    SDL_GLContext context;
    bool need_run = true;
    
    float light_intensity = 1.0f;
    bool show_help = false;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return 1;

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    window = SDL_CreateWindow("Jatek", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);

    SDL_SetRelativeMouseMode(SDL_TRUE);

    glViewport(0, 0, 800, 600);
    glClearColor(0.5f, 0.7f, 1.0f, 1.0f); 

    glEnable(GL_DEPTH_TEST);
    
    // FÉNYELÉS INICIALIZÁLÁSA
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL); // Lehetővé teszi, hogy a glColor3f továbbra is működjön a fényekkel
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_NORMALIZE); // Automatikusan javítja a normálvektorok méretét

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.1, 0.1, -0.075, 0.075, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

    srand(time(NULL));
    float treePositions[NUM_TREES][2];
    float minDist = 2.2f; 
    int placedTrees = 0;
    int attempts = 0;

    while (placedTrees < NUM_TREES && attempts < 3000) {
        float newX = ((float)(rand() % ((int)WORLD_SIZE * 20)) / 10.0f) - WORLD_SIZE;
        float newZ = ((float)(rand() % ((int)WORLD_SIZE * 20)) / 10.0f) - WORLD_SIZE;
        bool collision = false;
        float startDistX = newX - 0.0f;
        float startDistZ = newZ - 5.0f;
        if (sqrt(startDistX*startDistX + startDistZ*startDistZ) < 3.0f) collision = true;
        for (int j = 0; j < placedTrees; j++) {
            float dx = newX - treePositions[j][0];
            float dz = newZ - treePositions[j][1];
            if (sqrt(dx*dx + dz*dz) < minDist) { 
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

    float camX = 0.0f, camZ = 5.0f;
    float camAngle = 0.0f; 
    float pitch = 0.0f;    
    
    const float moveSpeed = 0.15f;
    const float mouseSensitivity = 0.2f; 
    const float mapLimit = WORLD_SIZE - 1.0f; 
    const float playerRadius = 0.8f; 

    while (need_run)
    {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) need_run = false;
            
            
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_F1) {
                    show_help = !show_help; // Ki-Be kapcsolás
                    // Ha a help nyitva van, kiszabadítjuk az egeret
                    if(show_help) {
                        SDL_SetRelativeMouseMode(SDL_FALSE);
                    }
                    else{
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                    }
                }
            }

            // Csak akkor mozgassuk a kamerát, ha nincs nyitva a súgó
            if (event.type == SDL_MOUSEMOTION && !show_help) {
                camAngle += event.motion.xrel * mouseSensitivity;
                pitch += event.motion.yrel * mouseSensitivity;

                if (pitch > 89.0f) pitch = 89.0f;
                if (pitch < -89.0f) pitch = -89.0f;
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        
        // FÉNYERŐ SZABÁLYOZÁSA (+ ÉS - GOMBOK)
        // (Figyeli a sima és a Numpad billentyűket is)
        if (state[SDL_SCANCODE_KP_PLUS] || state[SDL_SCANCODE_EQUALS]) {
            light_intensity += 0.02f;
            if(light_intensity > 3.0f)
            {
                light_intensity = 3.0f; 
            }
        }
        if (state[SDL_SCANCODE_KP_MINUS] || state[SDL_SCANCODE_MINUS]) {
            light_intensity -= 0.02f;
            if(light_intensity < 0.0f) {
                light_intensity = 0.0f; 
            }
        }

        // Fény paramétereinek frissítése a light_intensity alapján
        GLfloat lightAmbient[] = { 0.2f * light_intensity, 0.2f * light_intensity, 0.2f * light_intensity, 1.0f };
        GLfloat lightDiffuse[] = { 0.8f * light_intensity, 0.8f * light_intensity, 0.8f * light_intensity, 1.0f };
        GLfloat lightPosition[] = { 0.0f, 20.0f, 0.0f, 1.0f }; // Nap fentről
        
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        // MOZGÁS (Csak ha nincs nyitva a help)
        if(!show_help) {
            float rad = camAngle * M_PI / 180.0f;
            float moveX = 0.0f;
            float moveZ = 0.0f;

            if (state[SDL_SCANCODE_W]) { moveX += sin(rad) * moveSpeed; moveZ -= cos(rad) * moveSpeed; }
            if (state[SDL_SCANCODE_S]) { moveX -= sin(rad) * moveSpeed; moveZ += cos(rad) * moveSpeed; }
            if (state[SDL_SCANCODE_A]) { moveX -= cos(rad) * moveSpeed; moveZ -= sin(rad) * moveSpeed; }
            if (state[SDL_SCANCODE_D]) { moveX += cos(rad) * moveSpeed; moveZ += sin(rad) * moveSpeed; }

            float nextX = camX + moveX;
            bool collisionX = false;
            if (nextX < -mapLimit || nextX > mapLimit) collisionX = true;
            for (int i = 0; i < placedTrees; i++) {
                float dx = nextX - treePositions[i][0];
                float dz = camZ - treePositions[i][1];
                if (sqrt(dx*dx + dz*dz) < playerRadius) { collisionX = true; break; }
            }
            if (!collisionX) camX = nextX;

            float nextZ = camZ + moveZ;
            bool collisionZ = false;
            if (nextZ < -mapLimit || nextZ > mapLimit) collisionZ = true;
            for (int i = 0; i < placedTrees; i++) {
                float dx = camX - treePositions[i][0];
                float dz = nextZ - treePositions[i][1];
                if (sqrt(dx*dx + dz*dz) < playerRadius) { collisionZ = true; break; }
            }
            if (!collisionZ) camZ = nextZ;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        float groundHeight = getHeight(camX, camZ);
        float eyeLevel = 1.2f; 
        float currentCamY = groundHeight + eyeLevel;

        glRotatef(pitch, 1.0f, 0.0f, 0.0f);
        glRotatef(camAngle, 0.0f, 1.0f, 0.0f);
        glTranslatef(-camX, -currentCamY, -camZ); 

        drawTerrain();

        for(int i = 0; i < placedTrees; i++) {
            glPushMatrix();
            float h = getHeight(treePositions[i][0], treePositions[i][1]);
            glTranslatef(treePositions[i][0], h, treePositions[i][1]); 
            drawTree();
            glPopMatrix();
        }

        if (show_help) {
            // Váltás 2D Ortografikus nézetre
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0, 800, 600, 0, -1, 1);
            
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();

            // 3D effektek (fény, mélység) kikapcsolása a HUD-hoz
            glDisable(GL_LIGHTING);
            glDisable(GL_DEPTH_TEST);
            
            // Átlátszóság bekapcsolása a háttérpanelhez
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            // Félig átlátszó fekete téglalap (Panel)
            glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
            glBegin(GL_QUADS);
                glVertex2f(100.0f, 100.0f);
                glVertex2f(700.0f, 100.0f);
                glVertex2f(700.0f, 500.0f);
                glVertex2f(100.0f, 500.0f);
            glEnd();
            glDisable(GL_BLEND);

            glColor3f(1.0f, 1.0f, 1.0f);
            glLineWidth(10.0f);
            glBegin(GL_LINES);
                glVertex2f(350.0f, 200.0f); glVertex2f(350.0f, 400.0f);
                glVertex2f(450.0f, 200.0f); glVertex2f(450.0f, 400.0f);
                glVertex2f(350.0f, 300.0f); glVertex2f(450.0f, 300.0f);
            glEnd();
            glLineWidth(1.0f);

            // 3D effektek visszakapcsolása
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_LIGHTING);

            // Kamera mátrixok visszaállítása
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
