#include "circle.h"

void set_circle_data(Circle* circle, double x, double y, double radius)
{
	circle->x = x;
	circle->y = y;
	if (radius > 0.0) {
		circle->radius = radius;
	} else {
		circle->radius = NAN;
	}
}

double calc_circle_area(const Circle* circle)
{
	double area = circle->radius * circle->radius * M_PI;
	return area;
}
void draw_circle(Circle* circle, int segment){
	glBegin(GL_LINE_LOOP);
	glColor3f(circle->color.r, circle->color.g, circle->color.b);
	for (int i = 0; i < segment; i++) {
        double theta = 2.0 * M_PI * (double)i / (double)segment;
        double px = circle->x + circle->radius * cos(theta);
        double py = circle->y + circle->radius * sin(theta);
        glVertex2d(px, py);
    }
    glEnd();
}
void draw_marker(double x, double y, double size) {
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f); 
    glVertex2d(x - size, y - size); glVertex2d(x + size, y + size);
    glVertex2d(x + size, y - size); glVertex2d(x - size, y + size);
    glEnd();
}

bool is_point_in_circle(double px, double py, const Circle* c) {
    double dx = px - c->x;
    double dy = py - c->y;
    return (dx * dx + dy * dy) <= (c->radius * c->radius);
}