#include <GL/gl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdbool.h>
#include <stdio.h>

#define MAX_LINE_COUNT 100

typedef struct line{
    int start_x[MAX_LINE_COUNT];
    int end_x[MAX_LINE_COUNT];
    int start_y[MAX_LINE_COUNT];
    int end_y[MAX_LINE_COUNT];
}Line;

int main(){
    int error_code;
    SDL_Window *window;
    bool need_run;
    SDL_Event event;   
    SDL_GLContext context;
    SDL_Renderer *renderer;
    SDL_Rect square = {0,0,400,100}; 
    Line points;
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
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

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
                   points.start_x[i] = b.x;
                   points.start_y[i] = b.y;
                   has_start_point = true;
                }
                else if (b.button == SDL_BUTTON_RIGHT ){
                    if (has_start_point == false)
                    {
                        printf("Elsonek kell egy bal klikk!");
                    }
                    else if (i < MAX_LINE_COUNT){
                        points.end_x[i] = b.x;
                        points.end_y[i] = b.y;
                        i++;
                        has_start_point = false;
                    }
                    
                }
                break;
            }
        }
        
    
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,1,2);
        glBegin(GL_LINES);
        
        for (int j = 0; j < i; j++)
        {
            glVertex2f(points.start_x[j], 600 - points.start_y[j]);
            glVertex2f(points.end_x[j], 600 - points.end_y[j]);
        }
        glEnd();
        SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}