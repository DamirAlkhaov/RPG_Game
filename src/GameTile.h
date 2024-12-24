#include <SFML/Graphics/Sprite.h>

typedef struct gameTile {
    sfSprite *sprite;
    sfBool wall;
} GameTile;

GameTile* create_GameTile(sfTexture *texture, sfSprite *sprite);

void renderTile(sfRenderWindow *win, const GameTile const *tile);