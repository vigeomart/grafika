#ifndef CIRCLE_H
#define CIRCLE_H
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
typedef struct Color{
	float r,g,b;
}Color;

typedef struct Circle
{
	double x;
	double y;
	double radius;
	Color color;
} Circle;

void set_circle_data(Circle* circle, double x, double y, double radius);

double calc_circle_area(const Circle* circle);

void draw_circle(Circle* circle, int segment);

void draw_marker(double x, double y, double size);
bool is_point_in_circle(double px, double py, const Circle* c);

#endif // CIRCLE_H
