#include "brick.h"

#include <math.h>

void set_brick(Brick* brick, double x, double y, double z){
    brick->x = x;
    brick->y = y;
    brick->z = z;
};

double cal_brick_volume(Brick* brick){
    double volume = brick->x* brick->y* brick->z;
    return volume;
};
double cal_surface(Brick* brick){
    double surface1 =(brick->x*brick->y)*2;
    double surface2 =(brick->y*brick->z)*2;
    double surface3 =(brick->x*brick->z)*2;
    
    return surface1+surface2+surface3;
};
int is_square(Brick* brick){
    if (brick->x == brick->y || brick->x == brick->z || brick->z == brick->y )
    {
        return 1;
    }
    else
    {
        return 0;
    }
      
};

