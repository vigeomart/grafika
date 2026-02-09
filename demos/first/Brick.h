#include <stdio.h>

struct Brick{
	double a;
	double b;
	double c;
};

struct void set_size(struct Brick brick,double length, double width, double height){
	struct Brick brick;
	brick.a = length;
	brick.b = width;
	brick.c = height;
};
double calc_volume(struct Brick brick){
	return brick.a * brick.b * brick.c;
};
double calc_surface(struct Brick brick){
	double eredmeny1 = (brick.a * brick.b)*2;
	double eredmeny2 = (brick.b * brick.c)*2;
	double eredmeny3 = (brick.c * brick.a)*2;
	return eredmeny1+eredmeny2+eredmeny3;
};
