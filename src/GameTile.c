#include "GameTile.h"
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>

GameTile* GameTile_Create(sfTexture *texture, sfSprite *sprite) {
    GameTile *tile = (GameTile*)malloc(sizeof(GameTile));
    if (texture == NULL){
        puts("PUTA");
    }
    sfSprite_setTexture(sprite, texture, 0);
    if (sprite != NULL){
        printf("Sprite successfully set\n");
    }

    sfSprite_setOrigin(sprite, (sfVector2f){16, 16});

    tile->sprite = sprite;
    return tile;
}

void GameTile_Render(sfRenderWindow *win, const GameTile const*tile){
    sfRenderWindow_drawSprite(win, tile->sprite, 0);
}