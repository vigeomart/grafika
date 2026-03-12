#include <GL/gl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdbool.h>
#include <stdio.h>


typedef struct line
{
    int color;
    double p1 [1][1];
    double p2[1][1];
}Line;

/**
 * SDL2 OpenGL example
 */
int main(int argc, char* argv[])
{
  int error_code;
  SDL_Window* window;
  bool need_run;
  SDL_Event event;
  SDL_GLContext gl_context;
  int i;
  int p1,p2;

  error_code = SDL_Init(SDL_INIT_EVERYTHING);
  if (error_code != 0) {
    printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
    return error_code;
  }

  window = SDL_CreateWindow(
    "Hello SDL!",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    800, 600,
    SDL_WINDOW_OPENGL);

  gl_context = SDL_GL_CreateContext(window);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  need_run = true;
  while (need_run) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_KEYDOWN:
        case SDL_SCANCODE_Q:
        need_run = false;
        break;
      case SDL_QUIT:
        need_run = false;
        break;
      }
    }
     glRotatef(0.1, 0, 0, 1);

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(0, 0);
    glColor3f(0, 1, 0);
    glVertex2f(1, 0);
    glColor3f(0, 0, 1);
    glVertex2f(0, 1);
    glEnd();
    
    SDL_GetMouseState(&p1,&p2);
    SDL_GL_SwapWindow(window);
    printf("\nx: %d, y : %d", p1,p2);
  }

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}