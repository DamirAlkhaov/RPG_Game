#include "GameTile.h"
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>

GameTile* create_GameTile(sfTexture *texture, sfSprite *sprite) {
    GameTile *tile = (GameTile*)malloc(sizeof(GameTile));
    tile->sprite = sprite;
    return tile;
}

void renderTile(sfRenderWindow *win, const GameTile const*tile){
    sfRenderWindow_drawSprite(win, tile->sprite, 0);
}