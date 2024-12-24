#include "GameTile.h"
#define MAP_SIZE 1

typedef struct gameMap {
    GameTile *tiles[MAP_SIZE][MAP_SIZE];
} GameMap;

void GameMap_Init(GameMap *gameMap);