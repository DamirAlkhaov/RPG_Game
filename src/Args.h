#pragma once
#include <SFML/Graphics.h>
#include <math.h>

typedef struct {
    sfRenderWindow *window;
    sfView *view;
    sfEvent *event;
    sfTime e;
} ARGS;
