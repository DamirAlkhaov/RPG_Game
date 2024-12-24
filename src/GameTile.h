#include <SFML/Graphics/Sprite.h>

typedef struct gameTile {
    sfSprite *sprite;
    sfBool wall;
} GameTile;

GameTile* create_GameTile(const sfTexture const *texture);

void render(const sfRenderWindow const *win, const GameTile const *tile);