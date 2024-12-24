#include "GameMap.h"
#include <SFML/Graphics.h>
#include <stdio.h>
#include <string.h>

void GameMap_Init(GameMap *gameMap){
    sfTexture *floorTXT = sfTexture_createFromFile("textures/floor.png", NULL);
    GameTile *floor = create_GameTile(floorTXT);

    for (int i = 0; i < MAP_SIZE; i++){
        for (int j = 0; j < MAP_SIZE; j++){
            gameMap->tiles[i][j] = floor;
        }
    }
}