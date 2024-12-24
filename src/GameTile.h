#include <SFML/Graphics/Sprite.h>

typedef struct gameTile {
    sfSprite *sprite;
    sfBool wall;
} GameTile;

GameTile* GameTile_Create(sfTexture *texture, sfSprite *sprite);

void GameTile_Render(sfRenderWindow *win, const GameTile const *tile);