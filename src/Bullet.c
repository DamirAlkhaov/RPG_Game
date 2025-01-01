#include "Bullet.h"
#include <stdio.h>
#include <stdlib.h>
#include "Collision.h"
#include "crate.h"
#define BULLET_SPEED 1000

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

typedef struct {
    sfSprite **objs;
    int start;
} BULLET_ARG;

void MC_BulletCol(void *arg){
    BULLET_ARG *args = (BULLET_ARG *)arg;
    sfSprite **objs = args->objs;
    for (int i = 0; i < BULLETS_LIMIT; i++){
        //conditional that skips half the bullets. this can easily be added into the for loop conditional instead but decided to do this instead.
        if ((i + args->start) % 2 != 0) continue;
        //if bullet doesn't exist, do nothing.
        if (bullets[i] == NULL) continue;

        //printf("Thread %d is working on bullet %d\n", args->start+1, i);

        //cycle through the crates and check for collision.
        for (size_t j = 0; j < CRATE_LIMIT; j++){
            if (objs[j] == NULL) continue;
            sfVector2f iPos = bullets[i]->pos;
            sfVector2f jPos = sfSprite_getPosition(objs[j]);
            sfBool touching = Collision_Check_Bullets(iPos, jPos);

            if (touching) {

                bullets[i]->createdOn = 0;
                objs[j] = NULL;
                break;
            }
            
        }
    }
}

void Bullet_Collisions(sfSprite **objs){
    
    sfThread *thread1;
    sfThread *thread2;
    
    BULLET_ARG obj1;
    obj1.objs = objs;
    obj1.start = 0;
    thread1 = sfThread_create(&MC_BulletCol, (void *)&obj1);

    BULLET_ARG obj2;
    obj2.objs = objs;
    obj2.start = 1;
    thread2 = sfThread_create(&MC_BulletCol, (void *)&obj2);

    sfThread_launch(thread1);
    sfThread_launch(thread2);

    sfThread_wait(thread1);
    sfThread_wait(thread2);
}

