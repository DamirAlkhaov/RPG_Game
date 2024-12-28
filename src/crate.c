#include "crate.h"
#include <stdio.h>
#include "Collision.h"


sfTexture *crateTexture;
void Crate_Init(){
    crateTexture = sfTexture_createFromFile("textures/crate.png", NULL);
    if (crateTexture == NULL){
        puts("Crate texture failed to load.");
    }
}

void Crate_Add(sfSprite *objs[], sfVector2f position){
    for (int i = 0; i < CRATE_LIMIT; i++){
        if (objs[i] != NULL) continue;
        sfSprite *crate = sfSprite_create();
        sfSprite_setTexture(crate, crateTexture, 0);
        sfSprite_setOrigin(crate, (sfVector2f){16, 16});
        sfSprite_setPosition(crate, position);
        objs[i] = crate;
        break;
    }
    

}

void Crate_Destroy(sfSprite *objs[]){
    sfTexture_destroy(crateTexture);
    for (int i = 0; i < CRATE_LIMIT; i++){
        if (objs[i] == NULL) continue;
        sfSprite_destroy(objs[i]);
    }
}

void Crate_Render(ARGS *args, sfSprite *objs[]){
    for (int i = 0; i < CRATE_LIMIT; i++){
        if (objs[i] == NULL) continue;
        sfRenderWindow_drawSprite(args->window, objs[i], NULL);
    }
}

void Crate_Collisions(sfSprite *objs[]){
    for (int i = 0; i < CRATE_LIMIT; i++){
        if (objs[i] == NULL) continue;
        for (int j = 0; j < CRATE_LIMIT; j++){
            if (i == j) continue;
            if (objs[j] == NULL) continue;
            sfVector2f iPos = sfSprite_getPosition(objs[i]);
            sfVector2f jPos = sfSprite_getPosition(objs[j]);
            sfVector2f moveVec = Collision_Check(iPos, jPos);
            if (moveVec.x == 0 && moveVec.y == 0) continue;
            sfVector2f otherVec = moveVec;
            otherVec.x *= -0.5; otherVec.y *= -0.5;
            moveVec.x *= 0.5; moveVec.y *= 0.5;
            
            sfSprite_move(objs[i], moveVec);
            sfSprite_move(objs[j], otherVec);
        }
    }
}