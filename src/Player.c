#include "Player.h"
#include <stdio.h>
#include <SFML/Window/Mouse.h>

sfTexture *playerTXT;
sfSprite *playerSprite;

void Player_Init(Player *player){
    player->lastShot = clock();
    player->stamina = 100.f;

    //sprite
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

void Player_Destroy(){
    sfTexture_destroy(playerTXT);
    sfSprite_destroy(playerSprite);
}

void Player_Shoot(ARGS *args, Player *player){
    if (player->lastShot + 100 < clock()){
        sfVector2i mousePosPixel = sfMouse_getPositionRenderWindow(args->window);
        sfVector2f mousePosCoord = sfRenderWindow_mapPixelToCoords(args->window, mousePosPixel, args->view);
        sfVector2f playerPos = sfSprite_getPosition(player->playerSprite);
        sfVector2f relVec = {mousePosCoord.x - playerPos.x, mousePosCoord.y - playerPos.y};
        double angle = atan2(relVec.y, relVec.x) * 180/M_PI;

        Bullet_Create(angle, sfSprite_getPosition(player->playerSprite));
        player->lastShot = clock();
    }

}