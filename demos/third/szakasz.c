#include <GL/gl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdbool.h>
#include <stdio.h>

#define MAX_LINE_COUNT 100

int main(){
    int error_code;
    SDL_Window *window;
    bool need_run;
    SDL_Event event;   
    SDL_GLContext context;
    int start_x,start_y;
    int pozi[MAX_LINE_COUNT][4];
    int i = 0;
    bool has_start_point = false;

    error_code =SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code !=0 )
    {
        printf("Initalize error: %s",SDL_GetError() );
        return error_code;
    }
    
    window = SDL_CreateWindow("Szakasz",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -1, 1); // left, right, bottom, top
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    need_run = true;
    while (need_run == true)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                need_run = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_MouseButtonEvent b = event.button;
                if (b.button == SDL_BUTTON_LEFT )
                {
                   start_x = b.x;
                   start_y = b.y;
                   has_start_point = true;
                }
                else if (b.button == SDL_BUTTON_RIGHT ){
                    if (has_start_point == false)
                    {
                        printf("Elsonek kell egy bal klikk!");
                    }
                    else if (i < MAX_LINE_COUNT){
                        pozi[i][0] = start_x;
                        pozi[i][1] = start_y;
                        pozi[i][2] = b.x;
                        pozi[i][3] = b.y;
                        i++;
                        has_start_point = false;
                    }
                    
                }
                break;
            }
        }
        
    
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,1,1);
        glBegin(GL_LINES);
        for (int j = 0; j < i; j++)
        {
            glVertex2f(pozi[j][0],600 - pozi[j][1]);
            glVertex2f(pozi[j][2],600 - pozi[j][3]);
        }
        glEnd();
        SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}