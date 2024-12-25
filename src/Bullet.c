#include "Bullet.h"
#include <stdio.h>

sfTexture *bulletTXT;
sfSprite *bulletSprite;
Bullet *bullets[BULLETS_LIMIT];

void Bullet_Init(){
    bulletTXT = sfTexture_createFromFile("textures/bullet.png", NULL);
    if (bulletTXT == NULL){
        puts("Bullets texture failed to load.");
    }
    bulletSprite = sfSprite_create();
    sfSprite_setTexture(bulletSprite, bulletTXT, 0);
}

void Bullet_Create(DIRECTIONS dir, sfVector2f pos){
    Bullet bullet = {bulletSprite, dir, clock(), pos};
    for (int i = 0; i < BULLETS_LIMIT; i++){
        sfVector2f move = {0,0};
        if (bullets[i] != NULL){
            continue;
        }
        bullets[i] = &bullet;
        return;
    }
}

void Bullet_Update(ARGS *args){
    
    for (int i = 0; i < BULLETS_LIMIT; i++){
        sfVector2f move = {0,0};
        if (bullets[i] == NULL){
            continue;
        }
        if (bullets[i]->createdOn + 10000 < clock()){
            bullets[i] = NULL;
            continue;
        }
        switch (bullets[i]->direction){
            case EAST:
                move.x = 1;
                break;
            case NORTH:
                move.y = 1;
                break;
            case WEST:
                move.x = -1;
                break;
            case SOUTH:
                move.y = -1;
                break;
        }
        move.x += move.x * sfTime_asSeconds(args->e);
        move.y += move.y * sfTime_asSeconds(args->e);
        bullets[i]->pos.x += move.x;
        bullets[i]->pos.y += move.y;
        printf("x: %f\ny: %f\n", move.x, move.y);
        //sfSprite_setPosition(bulletSprite, bullets[i]->pos);
        sfRenderWindow_drawSprite(args->window, bulletSprite, NULL);
        
    }
}

void Bullet_Destroy(){
    sfSprite_destroy(bulletSprite);
}