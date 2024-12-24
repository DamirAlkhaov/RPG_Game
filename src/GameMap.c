#include "GameMap.h"
#include <SFML/Graphics.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void GameMap_Init(GameMap *gameMap){
    gameMap->size = MAP_SIZE;
    sfTexture *floorTXT = sfTexture_createFromFile("textures/floor.png", NULL);
    if (floorTXT == NULL){
        printf("Texture failed to load.\n");
        floorTXT = sfTexture_createFromFile("bin/textures/floor.png", NULL);
        if (floorTXT == NULL){
            printf("im gonna go crazy\n");
        }
    } else {
        printf("yay\n");
    }

    sfSprite *fsprite = sfSprite_create();
    
    sfSprite_setTexture(fsprite, floorTXT, 0);
    if (fsprite != NULL){
        printf("Sprite successfully set\n");
    }

    GameTile *floor = create_GameTile(floorTXT, fsprite);

    for (int i = 0; i < MAP_SIZE; i++){
        for (int j = 0; j < MAP_SIZE; j++){
            gameMap->tiles[i][j] = floor;
        }
    }
}