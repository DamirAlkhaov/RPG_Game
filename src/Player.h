#include <SFML/Graphics.h>
#include "Bullet.h"
#include "Time.h"

typedef struct {
    sfSprite *playerSprite;
    DIRECTIONS lastFaced;
    clock_t lastShot;
} Player;

void Player_Init(Player *player);

void Player_Destroy();

void Player_Shoot(ARGS *args, Player *player);