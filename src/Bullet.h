#pragma once
#include <SFML/Graphics.h>
#include <time.h>
#include "Args.h"
#define BULLETS_LIMIT 50

typedef struct {
    sfSprite *bulletSprite;
    double dir;
    clock_t createdOn;
    sfVector2f pos;
} Bullet;

void Bullet_Init();
void Bullet_Create(double dir, sfVector2f pos);
void Bullet_Update(ARGS *args);
void Bullet_Destroy();