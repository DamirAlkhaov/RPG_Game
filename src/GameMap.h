#include "Args.h"
#define MAP_SIZE 250 // 500 works well on the uni laptop.

//Initialize the game map
void GameMap_Init();
//This function destroys the textures etc that are used in the game map.
void GameMap_Destroy();
//Render function for the game map.
void GameMap_Render(sfView *view, sfRenderWindow *win);