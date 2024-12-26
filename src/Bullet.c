#include "Bullet.h"
#include <stdio.h>
#include <stdlib.h>
#define BULLET_SPEED 500

sfTexture *bulletTXT;
sfSprite *bulletSprite;
Bullet *bullets[BULLETS_LIMIT];

void Bullet_Init(){
    bulletTXT = sfTexture_createFromFile("bin/textures/bullet.png", NULL);
    if (bulletTXT == NULL){
        puts("Bullets texture failed to load.");
    }
    bulletSprite = sfSprite_create();
    sfSprite_setTexture(bulletSprite, bulletTXT, 0);
    sfVector2f origin = {sfSprite_getLocalBounds(bulletSprite).width/2, sfSprite_getLocalBounds(bulletSprite).height/2};
    sfSprite_setOrigin(bulletSprite, origin);
}

void Bullet_Create(DIRECTIONS dir, sfVector2f pos){
    Bullet *bullet = (Bullet *)malloc(sizeof(Bullet));
    if (bullet == NULL){
        puts("Bullet failed to allocate.");
    }
    for (int i = 0; i < BULLETS_LIMIT; i++){
        sfVector2f move = {0,0};
        if (bullets[i] != NULL){
            continue;
        }
        bullet->bulletSprite = bulletSprite;
        bullet->createdOn = clock();
        bullet->direction = dir;
        bullet->pos = pos;
        bullets[i] = bullet;

        return;
    }
}

void Bullet_Update(ARGS *args){
    
    for (int i = 0; i < BULLETS_LIMIT; i++){
        sfVector2f move = {0,0};
        if (bullets[i] == NULL){
            continue;
        }
        if (bullets[i]->createdOn + 3000 < clock()){
            bullets[i] = NULL;
            continue;
        }
        DIRECTIONS dir = bullets[i]->direction;

        switch (dir){
            case EAST:
                move.x = BULLET_SPEED;
                sfSprite_setRotation(bulletSprite, 0);
                break;
            case NORTH:
                move.y = -BULLET_SPEED;
                sfSprite_setRotation(bulletSprite, 270);
                break;
            case WEST:
                move.x = -BULLET_SPEED;
                sfSprite_setRotation(bulletSprite, 180);
                break;
            case SOUTH:
                move.y = BULLET_SPEED;
                sfSprite_setRotation(bulletSprite, 90);
                break;
            case NE:
                move.x = BULLET_SPEED * cos(45);
                move.y = -BULLET_SPEED * sin(45);
                sfSprite_setRotation(bulletSprite, 270+45);
                break;
            case NW:
                move.x = -BULLET_SPEED * cos(45);
                move.y = -BULLET_SPEED * sin(45);
                sfSprite_setRotation(bulletSprite, 270-45);
                break;
            case SW:
                move.x = -BULLET_SPEED * cos(45);
                move.y = BULLET_SPEED * sin(45);
                sfSprite_setRotation(bulletSprite, 180-45);
                break;
            case SE:
                move.x = BULLET_SPEED * cos(45);
                move.y = BULLET_SPEED * sin(45);
                sfSprite_setRotation(bulletSprite, 45);
                break;
            default:
                break;
        }
        
        bullets[i]->pos.x += move.x * sfTime_asSeconds(args->e);
        bullets[i]->pos.y += move.y * sfTime_asSeconds(args->e);

        sfSprite_setPosition(bulletSprite, bullets[i]->pos);
        sfRenderWindow_drawSprite(args->window, bulletSprite, NULL);
        
    }
}

void Bullet_Destroy(){
    sfSprite_destroy(bulletSprite);
}