#include "GameMap.h"
#include <SFML/Graphics.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SCALE 6

sfSprite *fsprite;

void GameMap_Init(GameMap *gameMap){
    gameMap->size = MAP_SIZE;
    sfTexture *floorTXT = sfTexture_createFromFile("textures/floor.png", NULL);
    if (floorTXT == NULL){
        printf("Texture failed to load.\n");
        floorTXT = sfTexture_createFromFile("bin/textures/floor.png", NULL);
        if (floorTXT == NULL){
            printf("Texture for sure doesn't exist.\n");
        }
    } else {
        printf("Texture loaded successfully.\n");
    }

    fsprite = sfSprite_create();
    
    sfSprite_setTexture(fsprite, floorTXT, 0);
    if (fsprite != NULL){
        printf("Sprite successfully set\n");
    }

    GameTile *floor = GameTile_Create(floorTXT, fsprite);

    //temporary thing that sets the whole map to one sprite.
    for (int i = 0; i < MAP_SIZE; i++){
        for (int j = 0; j < MAP_SIZE; j++){
            gameMap->tiles[i][j] = floor;
        }
    }
}

void GameMap_Destroy(GameMap *gameMap){
    sfTexture_destroy(sfSprite_getTexture(fsprite));
    sfSprite_destroy(fsprite);
}

void GameMap_Render(GameMap *map, sfView *view, sfRenderWindow *win) {
    sfVector2f viewCenter = sfView_getCenter(view);
    sfVector2f viewSize = sfView_getSize(view);
    
    float viewLeft = (viewCenter.x - viewSize.x / 2) - 100;
    float viewTop = (viewCenter.y - viewSize.y / 2) - 100;
    float viewRight = (viewCenter.x + viewSize.x / 2) + 100;
    float viewBottom = (viewCenter.y + viewSize.y / 2) + 100;

    float tileX;
    float tileY;

    float sizeX;
    float sizeY;
    
    int p = 0;
    for (int i = 0; i < map->size; i++) {
        for (int j = 0; j < map->size; j++) {

            //get texture sizes
            sizeX = sfTexture_getSize(sfSprite_getTexture(map->tiles[i][j]->sprite)).x;
            sizeY = sfTexture_getSize(sfSprite_getTexture(map->tiles[i][j]->sprite)).y;
            // Compute tile position
            tileX = i * sizeX * SCALE;
            tileY = j * sizeY * SCALE;
            
            // Check if tile is within view bounds
            if ((tileX + sizeX * (SCALE)) > viewLeft && tileX < viewRight &&
                (tileY + sizeY * (SCALE)) > viewTop && tileY < viewBottom) {
                // Set tile position and scale
                sfSprite_setScale(map->tiles[i][j]->sprite, (sfVector2f){SCALE, SCALE});
                sfSprite_setPosition(map->tiles[i][j]->sprite, (sfVector2f){tileX, tileY});
    
                // Render tile
                GameTile_Render(win, map->tiles[i][j]);
                p++;
            }
            //printf("%f\n%f\n", tileX + sizeX * (SCALE), viewLeft);
        }
    }
    
}