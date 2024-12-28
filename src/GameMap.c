#include "GameMap.h"
#include <SFML/Graphics.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define QUADRANTS 21

sfSprite *fsprite;
sfSprite *wsprite;

sfRenderTexture *mapTexture;
sfSprite *mapSprite;

//GameTile *floor;
//GameTile *wall; 

enum tiles {FLOOR, WALL};

void GameMap_Init(ARGS *args, GameMap *gameMap){
    gameMap->size = MAP_SIZE;
    mapTexture = sfRenderTexture_create(MAP_SIZE * 32, MAP_SIZE * 32, sfFalse);

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

    sfVector2f center = {16, 16};

    //initialising sprites
    fsprite = sfSprite_create();
    wsprite = sfSprite_create();

    sfSprite_setTexture(fsprite, floorTXT, 1);
    sfSprite_setTexture(wsprite, wallTXT, 1);

    //sfSprite_setOrigin(fsprite, center);
    //sfSprite_setOrigin(wsprite, center);

    // making the game tile class
    //floor = GameTile_Create(floorTXT, fsprite);
    //wall = GameTile_Create(wallTXT, wsprite);

    float tileX;
    float tileY;
    
    //randing the tiles
    for (int i = 0; i < MAP_SIZE; i++){
        for (int j = 0; j < MAP_SIZE; j++){

            tileX = (i ) * 32;
            tileY = (j ) * 32;

            int r = 1 + rand() % 100;
            if (r <= 90){
                sfSprite_setPosition(fsprite, (sfVector2f){tileX, tileY});
                sfRenderTexture_drawSprite(mapTexture, fsprite, NULL);
            } else {
                sfSprite_setPosition(wsprite, (sfVector2f){tileX, tileY});
                sfRenderTexture_drawSprite(mapTexture, wsprite, NULL);
            }
        }
    }

    sfRenderTexture_display(mapTexture);

    mapSprite = sfSprite_create();
    sfSprite_setTexture(mapSprite, sfRenderTexture_getTexture(mapTexture), 1);

    //sfImage_saveToFile(sfTexture_copyToImage(sfRenderTexture_getTexture(mapTexture)), "output/img.png");

    printf("Game map init done.\n");
}

void GameMap_Destroy(GameMap *gameMap){
    sfTexture_destroy(sfSprite_getTexture(fsprite));
    sfSprite_destroy(fsprite);

    sfTexture_destroy(sfSprite_getTexture(wsprite));
    sfSprite_destroy(wsprite);

    //sfRenderTexture_destroy(mapTexture);
    sfSprite_destroy(mapSprite);

    //free(floor);
    //free(wall);
}

void GameMap_Render(GameMap *map, sfView *view, sfRenderWindow *win){
    float halfMap = MAP_SIZE/2;
    float halfMap_Pixels = halfMap * 32;
    sfSprite_setOrigin(mapSprite, (sfVector2f){halfMap * 32, halfMap * 32});
    
    sfVector2f viewCenter = sfView_getCenter(view);
    sfVector2f viewSize = sfView_getSize(view);

    int cells = (QUADRANTS - 1) / 2;

    int sum = 0;

    for (int i = -cells; i <= cells; i++){
        for (int j = -cells; j <= cells; j++){
            int tileX = MAP_SIZE * 32 * i;
            int tileY = MAP_SIZE * 32 * j;

            float deltaX = viewCenter.x - tileX;
            float deltaY = viewCenter.y - tileY;
            float intersectX = abs(deltaX) - ((viewSize.x/2) + halfMap_Pixels);
            float intersectY = abs(deltaY) - ((viewSize.y/2) + halfMap_Pixels);

            if ((intersectX < 0 && intersectY < 0)){
                sum++;
                sfSprite_setPosition(mapSprite, (sfVector2f){tileX, tileY});
                sfRenderWindow_drawSprite(win, mapSprite, NULL);
            }
        }
    }
    
    //printf("%d\n", sum);
}

/*
void GameMap_Render_Old(GameMap *map, sfView *view, sfRenderWindow *win) {
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
*/