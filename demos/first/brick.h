#ifndef BRICK_H
#define BRICK_H

typedef struct Brick {
	double x;
	double y;
	double z;
}Brick;

void set_brick(Brick* brick, double x, double y, double z);
double cal_brick_volume(Brick* brick);
double cal_surface(Brick* brick);
int is_square(Brick* brick);
#endif 

