#include <SFML/Graphics.h>

typedef enum directions {EAST, NORTH, WEST, SOUTH} DIRECTIONS;

typedef struct {
    sfSprite *playerSprite;
    DIRECTIONS lastFaced;
} Player;

void Player_Init(Player *player);

void Player_Destroy(Player *player);