#include "Bullet.h"
#include <stdio.h>
#include <stdlib.h>
#include "Collision.h"
#include "crate.h"
#define BULLET_SPEED 500

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
    sfVector2f origin = {sfSprite_getLocalBounds(bulletSprite).width/2, sfSprite_getLocalBounds(bulletSprite).height/2};
    sfSprite_setOrigin(bulletSprite, origin);
}

void Bullet_Create(double dir, sfVector2f pos){
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
        bullet->dir = dir;
        bullet->pos = pos;
        bullets[i] = bullet;

        return;
    }
}

void Bullet_Update(ARGS *args){
    
    for (int i = 0; i < BULLETS_LIMIT; i++){
        sfVector2f move = {BULLET_SPEED,BULLET_SPEED};
        if (bullets[i] == NULL){
            continue;
        }
        if (bullets[i]->createdOn + 3000 < clock()){
            bullets[i] = NULL;
            continue;
        }
        
        bullets[i]->pos.x += move.x * cos(bullets[i]->dir * PI/180) * sfTime_asSeconds(args->e);
        bullets[i]->pos.y += move.y * sin(bullets[i]->dir * PI/180) * sfTime_asSeconds(args->e);

        sfSprite_setRotation(bulletSprite, bullets[i]->dir);
        sfSprite_setPosition(bulletSprite, bullets[i]->pos);
        sfRenderWindow_drawSprite(args->window, bulletSprite, NULL);
        
    }
}

void Bullet_Destroy(){
    sfSprite_destroy(bulletSprite);
}

void Bullet_Collisions(sfSprite *objs[]){
    for (size_t i = 0; i < BULLETS_LIMIT; i++){
        if (bullets[i] == NULL) continue;
        for (size_t j = 0; j < CRATE_LIMIT; j++){
            if (objs[j] == NULL) continue;
            sfVector2f iPos = sfSprite_getPosition(bullets[i]->bulletSprite);
            sfVector2f jPos = sfSprite_getPosition(objs[j]);
            sfBool touching = Collision_Check_Bullets(iPos, jPos);
            if (!touching) continue;

            //bullets[i] = NULL;
            objs[j] = NULL;
        }
    }
    
}