#pragma once
#include <SFML/Graphics.h>
#include "Args.h"
#define CRATE_LIMIT 255

void Crate_Init();

void Crate_Add(sfSprite *objs[],sfVector2f position);

void Crate_Destroy(sfSprite *objs[]);

void Crate_Render(ARGS *args, sfSprite *objs[]);

void Crate_Collisions(sfSprite *objs[]);