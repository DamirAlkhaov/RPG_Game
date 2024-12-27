#pragma once
#include <SFML/Graphics.h>
#include <math.h>
#define PI 3.14

typedef struct {
    sfRenderWindow *window;
    sfView *view;
    sfEvent *event;
    sfTime e;
} ARGS;
