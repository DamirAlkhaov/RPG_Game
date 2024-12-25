#include "Player.h"
#include <stdio.h>

sfTexture *playerTXT;
sfSprite *playerSprite;

void Player_Init(Player *player){
    playerSprite = sfSprite_create();
    playerTXT = sfTexture_createFromFile("textures/player.png", NULL);
    if (playerTXT == NULL){
        puts("Failed to load player texture.");
    }
    sfSprite_setTexture(playerSprite, playerTXT, 0);
    sfVector2f origin = {sfSprite_getLocalBounds(playerSprite).width/2, sfSprite_getLocalBounds(playerSprite).height/2};
    sfSprite_setOrigin(playerSprite, origin);
    sfSprite_scale(playerSprite, (sfVector2f){0.5,0.5});

    player->playerSprite = playerSprite;
}

void Player_Destroy(Player *player){
    sfTexture_destroy(playerTXT);
    sfSprite_destroy(playerSprite);
}