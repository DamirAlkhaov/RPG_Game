#include "Collision.h"
#include <math.h>

sfVector2f Collision_Check(sfVector2f obj, sfVector2f obj2){
    float deltaX = obj.x - obj2.x;
    float deltaY = obj.y - obj2.y;

    float intersectX = abs(deltaX) - (31);
    float intersectY = abs(deltaY) - (31);   

    //printf("%f %f\n", intersectX, intersectY);
    if (intersectX < 0 && intersectY < 0){
        if (intersectX > intersectY){
            if (deltaX > 0) {
                return (sfVector2f){-intersectX, 0.f};
            } else {
                return (sfVector2f){intersectX, 0.f};
            }
            
        } else {
            if (deltaY > 0) {
                return (sfVector2f){ 0.f, -intersectY};
            } else {
                return (sfVector2f){ 0.f, intersectY};
            }
            
        }
    }

    return (sfVector2f){0, 0};
}