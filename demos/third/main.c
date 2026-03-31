#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_LINE_COUNT 100
#define PALETTE_SIZE 5
#define PALETTE_BOX_SIZE 40

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
} Color;

typedef struct {
    int start_x, start_y;
    int end_x, end_y;
    Color color;
} Line;

Color palette[PALETTE_SIZE] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {255, 255, 0},
    {255, 0, 255}
};

int main() {
    SDL_Window *window;
    SDL_GLContext context;
    SDL_Event event;   
    bool need_run = true;

    Line lines[MAX_LINE_COUNT];
    int line_count = 0;
    bool has_start_point = false;
    int temp_start_x, temp_start_y;
    
    Color current_color = {255, 255, 255};

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Initalize error: %s\n", SDL_GetError());
        return 1;
    }
    
    window = SDL_CreateWindow("Szakasz Rajzolo Palettaval", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);

    // OpenGL vetítés beállítása (2D)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 600, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (need_run) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    need_run = false;
                    break;
                
                case SDL_MOUSEMOTION:
                    printf("Eger pozicio: X: %d, Y: %d\n", event.motion.x, event.motion.y);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mx = event.button.x;
                        int my = event.button.y;

                        if (my < PALETTE_BOX_SIZE && mx < PALETTE_BOX_SIZE * PALETTE_SIZE) {
                            int color_index = mx / PALETTE_BOX_SIZE;
                            current_color = palette[color_index];
                            has_start_point = false;
                            printf("Uj szin kivalasztva: %d. index\n", color_index);
                        } 
                        else {
                            if (!has_start_point) {
                                temp_start_x = mx;
                                temp_start_y = my;
                                has_start_point = true;
                            } else {
                                if (line_count < MAX_LINE_COUNT) {
                                    lines[line_count].start_x = temp_start_x;
                                    lines[line_count].start_y = temp_start_y;
                                    lines[line_count].end_x = mx;
                                    lines[line_count].end_y = my;
                                    lines[line_count].color = current_color;
                                    line_count++;
                                } else {
                                    printf("Minden hely betelt (MAX_LINE_COUNT)!\n");
                                }
                                has_start_point = false;
                            }
                        }
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT) {
                        has_start_point = false;
                    }
                    break;
            }
        }

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
        for (int i = 0; i < PALETTE_SIZE; i++) {
            glColor3ub(palette[i].r, palette[i].g, palette[i].b);
            glVertex2i(i * PALETTE_BOX_SIZE, 0);
            glVertex2i((i + 1) * PALETTE_BOX_SIZE, 0);
            glVertex2i((i + 1) * PALETTE_BOX_SIZE, PALETTE_BOX_SIZE);
            glVertex2i(i * PALETTE_BOX_SIZE, PALETTE_BOX_SIZE);
        }
        glEnd();

        glBegin(GL_LINES);
        for (int j = 0; j < line_count; j++) {
            glColor3ub(lines[j].color.r, lines[j].color.g, lines[j].color.b);
            glVertex2i(lines[j].start_x, lines[j].start_y);
            glVertex2i(lines[j].end_x, lines[j].end_y);
        }
        glEnd();

        if (has_start_point) {
            int mx, my;
            SDL_GetMouseState(&mx, &my);
            glBegin(GL_LINES);
            glColor3ub(current_color.r, current_color.g, current_color.b);
            glVertex2i(temp_start_x, temp_start_y);
            glVertex2i(mx, my);
            glEnd();
        }

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}