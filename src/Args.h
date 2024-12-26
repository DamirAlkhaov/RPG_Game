#pragma once
#include <SFML/Graphics.h>
#include <math.h>

typedef enum {EAST, NORTH, WEST, SOUTH, NE, NW, SW, SE} DIRECTIONS;

typedef struct {
    sfRenderWindow *window;
    sfView *view;
    sfEvent *event;
    sfTime e;
} ARGS;
