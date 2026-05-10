#define _USE_MATH_DEFINES 
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h> 
#include <stdio.h>
#include <stdbool.h>
#include <time.h>   

#include "texture.h"
#include "model.h"
#include "terrain.h"
#include "tree.h"
#include "camera.h"
#include "sun.h"
#include "help.h"

int main(int argc, char* argv[])
{
    SDL_Window *window;
    SDL_Event event;
    SDL_GLContext context;
    bool need_run = true;
    bool show_help = false;
    Uint32 last_ticks = 0;
    bool is_time_flowing = false;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return 1;

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) return 1;

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    window = SDL_CreateWindow("Jatek", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    context = SDL_GL_CreateContext(window);

    int screen_w, screen_h;
    SDL_GetWindowSize(window, &screen_w, &screen_h);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    glViewport(0, 0, screen_w, screen_h);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL); 
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_NORMALIZE); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect_ratio = (float)screen_w / (float)screen_h;
    glFrustum(-0.1, 0.1, -0.1 / aspect_ratio, 0.1 / aspect_ratio, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

    GLuint helpTex = loadTexture("assets/help.jpg");
    GLuint grassDiffuseTex = loadTexture("assets/grass/grass.jpg");
    
    GLuint sunTex = loadTexture("assets/2k_sun.jpg");
    GLuint sunModel = loadOBJ("assets/sol.obj", sunTex);
    
    srand(time(NULL));
    generateTrees(WORLD_SIZE);

    last_ticks = SDL_GetTicks(); 

    while (need_run)
    {
        Uint32 current_ticks = SDL_GetTicks();
        float delta_time = (current_ticks - last_ticks) / 1000.0f; 
        last_ticks = current_ticks;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) need_run = false;
            
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) 
                    {
                        need_run = false;
                    }
                if (event.key.keysym.sym == SDLK_F1) {
                    show_help = !show_help; 
                    if(show_help){ 
                        SDL_SetRelativeMouseMode(SDL_FALSE);
                    }
                    else {
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                    }
                }
                if(event.key.keysym.sym == SDLK_n){
                    is_time_flowing = !is_time_flowing;
                }
            }

            if (event.type == SDL_MOUSEMOTION && !show_help) {
                updateCameraRotation(event.motion.xrel, event.motion.yrel, 0.2f);
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        
        handleSunInput(state); 
        updateTimeAndSun(delta_time, state, is_time_flowing); 

        if(!show_help) {
            updateCameraPosition(state, 0.15f, WORLD_SIZE - 1.0f, 0.8f);
        }

        applySkyAndLighting(); 
        applyCameraView(1.2f); 
        
        // MÓDOSÍTVA: Átadjuk a betöltött modellt a rajzoló függvénynek
        renderSun(sunModel);
        
        drawTerrain(grassDiffuseTex);
        renderAllTrees();

        if (show_help) {
            renderHelpMenu(helpTex, screen_w, screen_h);
        }

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    glDeleteTextures(1, &helpTex);
    glDeleteTextures(1, &grassDiffuseTex);
    
    // --- ÚJ: NAP MEMÓRIA TÖRLÉSE ---
    glDeleteTextures(1, &sunTex);
    glDeleteLists(sunModel, 1);
    // -------------------------------
    
    IMG_Quit();
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}