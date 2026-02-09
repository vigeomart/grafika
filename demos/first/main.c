#include <stdio.h>

#include  "brick.h"

int main(){
    Brick brick;
    double volume;
    double surface;
    int square;

    set_brick(&brick,10,10,8);
    volume = cal_brick_volume(&brick);
    surface = cal_surface(&brick);
    square = is_square(&brick);

   
    printf("Brick volume: %lf\nBrick surface: %lf\n",volume,surface);

    printf("The brick have square faces: %d\n",square);
    return 0;
}