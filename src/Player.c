#include "Player.h"
#include <stdio.h>

sfTexture *playerTXT;
sfSprite *playerSprite;

void Player_Init(Player *player){
    player->lastShot = clock();
    playerSprite = sfSprite_create();
    playerTXT = sfTexture_createFromFile("bin/textures/player.png", NULL);
    if (playerTXT == NULL){
        puts("Failed to load player texture.");
    }
    sfSprite_setTexture(playerSprite, playerTXT, 0);
    sfVector2f origin = {sfSprite_getLocalBounds(playerSprite).width/2, sfSprite_getLocalBounds(playerSprite).height/2};
    sfSprite_setOrigin(playerSprite, origin);
    sfSprite_scale(playerSprite, (sfVector2f){0.5,0.5});

    player->playerSprite = playerSprite;
}

void Player_Destroy(){
    sfTexture_destroy(playerTXT);
    sfSprite_destroy(playerSprite);
}

void Player_Shoot(ARGS *args, Player *player){
    if (player->lastShot + 500 < clock()){
        Bullet_Create(player->lastFaced, sfSprite_getPosition(player->playerSprite));
        player->lastShot = clock();
    }

}