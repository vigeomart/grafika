#include "circle.h"

#include <stdio.h>
#define MAX_CIRCLE_COUNT 50

int main(int argc, char* argv[])
{
	Circle circle;
	double area;
	
	set_circle_data(&circle, 5, 10, 8);
	area = calc_circle_area(&circle);
	
	printf("Circle area: %lf\n", area);
	
	SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Korok es Interakcio", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(window);

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 800, 600, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    Circle circles[MAX_CIRCLE_COUNT];
    int circle_count = 0;
    int dragged_circle_index = -1;

    bool running = true;
    SDL_Event ev;

    while (running) {
        int mx, my;
        SDL_GetMouseState(&mx, &my);

        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) running = false;

            if (ev.type == SDL_MOUSEBUTTONDOWN) {
                dragged_circle_index = -1;
                for (int i = 0; i < circle_count; i++) {
                    if (is_point_in_circle(ev.button.x, ev.button.y, &circles[i])) {
                        dragged_circle_index = i;
                        break;
                    }
                }

                if (dragged_circle_index == -1 && circle_count < MAX_CIRCLE_COUNT) {
                    circles[circle_count].x = ev.button.x;
                    circles[circle_count].y = ev.button.y;
                    circles[circle_count].radius = 30.0 + (rand() % 50);
                    circles[circle_count].color = (Color){(float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX};
                    circle_count++;
                }
            }

            if (ev.type == SDL_MOUSEBUTTONUP) {
                dragged_circle_index = -1;
            }

            if (ev.type == SDL_MOUSEMOTION && dragged_circle_index != -1) {
                circles[dragged_circle_index].x = ev.motion.x;
                circles[dragged_circle_index].y = ev.motion.y;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < circle_count; i++) {
            draw_circle(&circles[i], 32);

            // Ha felette van az egér, rajzolunk bele egy X-et
            if (is_point_in_circle(mx, my, &circles[i])) {
                draw_marker(circles[i].x, circles[i].y, 5);
            }
        }

        SDL_GL_SwapWindow(window);
    }

    SDL_Quit();
	return 0;
}
