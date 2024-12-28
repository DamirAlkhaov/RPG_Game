#include "GameTile.h"
#include "Args.h"
#define MAP_SIZE 250 // 500 works well on the uni laptop.

typedef struct {
    GameTile *tiles[MAP_SIZE][MAP_SIZE];
    int size;
} GameMap;
//Initialize the game map
void GameMap_Init(ARGS *args, GameMap *gameMap);
//This function destroys the textures etc that are used in the game map.
void GameMap_Destroy(GameMap *gameMap);
//Render function for the game map.
void GameMap_Render(GameMap *gameMap, sfView *view, sfRenderWindow *win);