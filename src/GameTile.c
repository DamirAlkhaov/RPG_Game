#include "GameTile.h"
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>

GameTile* GameTile_Create(sfTexture *texture, sfSprite *sprite) {
    GameTile *tile = (GameTile*)malloc(sizeof(GameTile));
    tile->sprite = sprite;
    return tile;
}

void GameTile_Render(sfRenderWindow *win, const GameTile const*tile){
    sfRenderWindow_drawSprite(win, tile->sprite, 0);
}