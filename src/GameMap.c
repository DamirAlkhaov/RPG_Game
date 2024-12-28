#include "GameMap.h"
#include <SFML/Graphics.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

sfSprite *fsprite;
sfSprite *wsprite;

GameTile *floor;
GameTile *wall; 

enum tiles {FLOOR, WALL};

void GameMap_Init(GameMap *gameMap){
    gameMap->size = MAP_SIZE;

    printf("Sizeof Game Tile: %zu", sizeof(GameTile));

    //texture loading
    sfTexture *floorTXT = sfTexture_createFromFile("textures/floor.png", NULL);
    if (floorTXT == NULL){
        printf("Texture failed to load.\n");
    } else {
        printf("Texture loaded successfully.\n");
    }

    sfTexture *wallTXT = sfTexture_createFromFile("textures/wall.png", NULL);
    if (wallTXT == NULL){
        printf("Texture failed to load.\n");
    } else {
        printf("Texture loaded successfully.\n");
    }

    //initialising sprites
    fsprite = sfSprite_create();
    wsprite = sfSprite_create();

    // making the game tile class
    floor = GameTile_Create(floorTXT, fsprite);
    wall = GameTile_Create(wallTXT, wsprite);

    //randing the tiles
    for (int i = 0; i < MAP_SIZE; i++){
        for (int j = 0; j < MAP_SIZE; j++){
            int r = 1 + rand() % 100;
            if (r <= 90){
                gameMap->tiles[i][j] = floor;
                gameMap->tiles[i][j]->wall = sfFalse;
            } else {
                gameMap->tiles[i][j] = wall;
                gameMap->tiles[i][j]->wall = sfTrue;
            }
        }
    }
    printf("Game map init done.\n");
}

void GameMap_Destroy(GameMap *gameMap){
    sfTexture_destroy(sfSprite_getTexture(fsprite));
    sfSprite_destroy(fsprite);

    sfTexture_destroy(sfSprite_getTexture(wsprite));
    sfSprite_destroy(wsprite);

    free(floor);
    free(wall);
}

void GameMap_Render(GameMap *map, sfView *view, sfRenderWindow *win) {
    sfVector2f viewCenter = sfView_getCenter(view);
    sfVector2f viewSize = sfView_getSize(view);
    
    //screen coordinates (in pixels and centered)
    float viewLeft = (viewCenter.x - viewSize.x / 2) - 50;
    float viewTop = (viewCenter.y - viewSize.y / 2) - 50;
    float viewRight = (viewCenter.x + viewSize.x / 2) + 50;
    float viewBottom = (viewCenter.y + viewSize.y / 2) + 50;

    float tileX;
    float tileY;

    float halfMap = MAP_SIZE/2;

    int left = (viewLeft / 32) + halfMap;
    int top = (viewTop / 32) + halfMap;
    int right = (viewRight / 32) + halfMap;
    int bottom = (viewBottom /32) + halfMap;
    if (left < 0) left = 0;
    if (top < 0) top = 0;
    if (bottom > map->size) bottom = map->size;
    if (right > map->size) right = map->size;

    // sfRenderTexture *mapTexture = sfRenderTexture_create(800, 800, sfFalse);

    //printf("l: %d t: %d b: %d r:%d\n", left, top, bottom, right);
    //rendering for loop.
    for (int i = left; i < right; i++) {
        for (int j = top; j < bottom; j++) { 
            // tile position
            tileX = (i - halfMap) * 32;
            tileY = (j - halfMap) * 32;
            
            
            sfSprite_setPosition(map->tiles[i][j]->sprite, (sfVector2f){tileX, tileY});
            
            // Render tile
            GameTile_Render(win, map->tiles[i][j]);
        }
    }
}