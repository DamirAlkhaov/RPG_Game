#pragma once
#include <SFML/Graphics.h>
#include <time.h>
#include "Args.h"
#define BULLETS_LIMIT 50

typedef struct {
    sfSprite *bulletSprite;
    DIRECTIONS direction;
    clock_t createdOn;
    sfVector2f pos;
} Bullet;

void Bullet_Init();
void Bullet_Create(DIRECTIONS dir, sfVector2f pos);
void Bullet_Update(ARGS *args);
void Bullet_Destroy();