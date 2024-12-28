#include "Collision.h"

void Collision_Check(sfSprite *obj, sfSprite *obj2){
    float deltaX = sfSprite_getOrigin(obj).x - sfSprite_getOrigin(obj2).x;
    float deltaY = sfSprite_getOrigin(obj).y - sfSprite_getOrigin(obj2).y;

    float intersectX = abs(deltaX) - (31);
    float intersectY = abs(deltaY) - (31);   

    //printf("%f %f\n", intersectX, intersectY);
    if (intersectX < 0 && intersectY < 0){
        float push = 0.2;
        if (intersectX > intersectY){
            if (deltaX > 0) {
                sfSprite_move(obj, (sfVector2f){-intersectX * (1 - push), 0.f});
                sfSprite_move(obj2, (sfVector2f){intersectX * push, 0.f});
            } else {
                sfSprite_move(obj, (sfVector2f){intersectX* (1 - push), 0.f});
                sfSprite_move(obj2, (sfVector2f){-intersectX * push, 0.f});
            }
            
        } else {
            if (deltaY > 0) {
                sfSprite_move(obj, (sfVector2f){0.f, -intersectY* (1 - push)});
                sfSprite_move(obj2, (sfVector2f){0.f, intersectY * push});
            } else {
                sfSprite_move(obj, (sfVector2f){0.f, intersectY* (1 - push)});
                sfSprite_move(obj2, (sfVector2f){0.f, -intersectY* push});
            }
            
        }
    }
}