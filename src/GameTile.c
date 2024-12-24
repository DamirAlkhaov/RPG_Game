#include "GameTile.h"
#include <SFML/Graphics.h>
#include <stdio.h>

GameTile* create_GameTile(const sfTexture const *texture) {
    GameTile *tile;
    tile->sprite = sfSprite_create();
    if (tile->sprite == NULL)
        //error
    sfSprite_setTexture(tile->sprite, texture, NULL);

    return tile;
}

void render(const sfRenderWindow const *win, const GameTile const*tile){
    sfRenderWindow_drawSprite(win, tile->sprite, NULL);
}