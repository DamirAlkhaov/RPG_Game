#include "GameMap.h"
#include <SFML/Graphics.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SCALE 1

sfSprite *fsprite;
sfSprite *wsprite;

enum tiles {FLOOR, WALL};

void GameMap_Init(GameMap *gameMap){
    gameMap->size = MAP_SIZE;

    //texture loading
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

    sfTexture *wallTXT = sfTexture_createFromFile("textures/wall.png", NULL);
    if (wallTXT == NULL){
        printf("Texture failed to load.\n");
        wallTXT = sfTexture_createFromFile("C:\\coding\\sfmlGame\\bin\\textures\\wall.png", NULL);
        if (wallTXT == NULL){
            printf("Texture for sure doesn't exist.\n");
        }
    } else {
        printf("Texture loaded successfully.\n");
    }

    //initialising sprites
    fsprite = sfSprite_create();
    wsprite = sfSprite_create();

    // making the game tile class
    GameTile *floor = GameTile_Create(floorTXT, fsprite);
    GameTile *wall = GameTile_Create(wallTXT, wsprite);

    //randing the tiles
    for (int i = 0; i < MAP_SIZE; i++){
        for (int j = 0; j < MAP_SIZE; j++){
            int r = rand() % 2;
            switch (r)
            {
            case FLOOR:
                gameMap->tiles[i][j] = floor;
                break;
            case WALL:
                gameMap->tiles[i][j] = wall;
                break;
            
            default:
                break;
            }
        }
    }
    printf("Game map init done.\n");
}

void GameMap_Destroy(){
    sfTexture_destroy(sfSprite_getTexture(fsprite));
    sfSprite_destroy(fsprite);

    sfTexture_destroy(sfSprite_getTexture(wsprite));
    sfSprite_destroy(wsprite);
}

void GameMap_Render(GameMap *map, sfView *view, sfRenderWindow *win) {
    sfVector2f viewCenter = sfView_getCenter(view);
    sfVector2f viewSize = sfView_getSize(view);
    
    //screen coordinates (in pixels and centered)
    float viewLeft = (viewCenter.x - viewSize.x / 2) - 100;
    float viewTop = (viewCenter.y - viewSize.y / 2) - 100;
    float viewRight = (viewCenter.x + viewSize.x / 2) + 100;
    float viewBottom = (viewCenter.y + viewSize.y / 2) + 100;

    float tileX;
    float tileY;
    
    //rendering for loop.
    for (int i = 0; i < map->size; i++) {
        for (int j = 0; j < map->size; j++) {

            //get texture sizes
            
            // Compute tile position
            tileX = i * 32 * SCALE;
            tileY = j * 32 * SCALE;
            
            // Check if tile is within view bounds
            if ((tileX + 32 * (SCALE)) > viewLeft && tileX < viewRight &&
                (tileY + 32 * (SCALE)) > viewTop && tileY < viewBottom) {
                // Set tile position and scale
                sfSprite_setScale(map->tiles[i][j]->sprite, (sfVector2f){SCALE, SCALE});
                sfSprite_setPosition(map->tiles[i][j]->sprite, (sfVector2f){tileX, tileY});
    
                // Render tile
                GameTile_Render(win, map->tiles[i][j]);
            }
        }
    }
    
}