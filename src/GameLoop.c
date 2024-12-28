#include "GameLoop.h"
#include <SFML/System/Time.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Mouse.h>
#include "UI.h"


float cameraSpeed = 100;

GameMap map;
Player player;

void Loop_Init(){
    GameMap_Init(&map);
    Player_Init(&player);
    Bullet_Init();
    UI_Init(&player);

}

void Loop_Update(ARGS *args){
    sfTime dt = args->e;
    float deltaTime = sfTime_asSeconds(dt);
    sfRenderWindow *win = args->window;
    sfView *view = args->view;
    sfBool moved = sfFalse;

    // do keyboard stuff here
    if (sfRenderWindow_hasFocus(win)){
        if (sfKeyboard_isKeyPressed(sfKeyEscape)){
            sfRenderWindow_close(win);
        }  

        if (sfKeyboard_isKeyPressed(sfKeyD) && sfKeyboard_isKeyPressed(sfKeyW) && !moved){
            sfView_move(view, (sfVector2f){cameraSpeed*deltaTime*cos(45 * PI/180), -cameraSpeed*deltaTime*sin(45 * PI/180)});
            moved = sfTrue;
        }
        if (sfKeyboard_isKeyPressed(sfKeyA) && sfKeyboard_isKeyPressed(sfKeyW) && !moved){
            sfView_move(view, (sfVector2f){-cameraSpeed*deltaTime*cos(45 * PI/180), -cameraSpeed*deltaTime*sin(45 * PI/180)});
            moved = sfTrue;
        }
        if (sfKeyboard_isKeyPressed(sfKeyA) && sfKeyboard_isKeyPressed(sfKeyS) && !moved){
            sfView_move(view, (sfVector2f){-cameraSpeed*deltaTime*cos(45 * PI/180), cameraSpeed*deltaTime*sin(45 * PI/180)});
            moved = sfTrue;
        }
        if (sfKeyboard_isKeyPressed(sfKeyD) && sfKeyboard_isKeyPressed(sfKeyS) && !moved){
            sfView_move(view, (sfVector2f){cameraSpeed*deltaTime*cos(45 * PI/180), cameraSpeed*deltaTime*sin(45 * PI/180)});
            moved = sfTrue;
        }

        if (sfKeyboard_isKeyPressed(sfKeyA) && !moved){

            sfView_move(view, (sfVector2f){-cameraSpeed*deltaTime, 0});
            moved = sfTrue;

        }
        if (sfKeyboard_isKeyPressed(sfKeyD) && !moved){

            sfView_move(view, (sfVector2f){cameraSpeed*deltaTime, 0});
            moved = sfTrue;
        }
        if (sfKeyboard_isKeyPressed(sfKeyW) && !moved){

            sfView_move(view, (sfVector2f){0, -cameraSpeed*deltaTime});
            moved = sfTrue;
        }
        if (sfKeyboard_isKeyPressed(sfKeyS) && !moved){

            sfView_move(view, (sfVector2f){0, cameraSpeed*deltaTime});
            moved = sfTrue;
        }
        if (sfKeyboard_isKeyPressed(sfKeyLBracket)){
            sfView_zoom(view, 1 + 2 * deltaTime);
            UI_SetZoom(1 + 2 * deltaTime);
            
        }
        if (sfKeyboard_isKeyPressed(sfKeyRBracket)){
            sfView_zoom(view, 1 - 2 * deltaTime);
            UI_SetZoom(1 - 2 * deltaTime);
            
        }
        if (sfKeyboard_isKeyPressed(sfKeyLShift) && ((player.stamina > 0 && !player.cooldown) || (player.stamina >= 20 && player.cooldown))){
            cameraSpeed = 250;
            player.stamina -= 25 * deltaTime;
            if (player.stamina < 0) {player.stamina = 0; player.cooldown = sfTrue;}
            if (player.stamina >= 20) player.cooldown = sfFalse;
        } else {
            cameraSpeed = 100;
            player.stamina += 10 * deltaTime;
            if (player.stamina > 100) player.stamina = 100;
        }
        if (sfMouse_isButtonPressed(sfMouseLeft)){
            Player_Shoot(args, &player);
        }
    }

    // fps counter title
    char title[255];
    sprintf(title, "Menace | FPS:%d", (int)(1/deltaTime));
    sfRenderWindow_setTitle(win, title);
    
    // collisions here


    // update player sprite pos
    sfSprite_setPosition(player.playerSprite, sfView_getCenter(view));

    //rendering
    GameMap_Render(&map, view, win);
    Bullet_Update(args);
    sfRenderWindow_setView(win, view);
    sfRenderWindow_drawSprite(win, player.playerSprite, NULL);
    
    
    UI_Update(args);
}

void Loop_End(){
    GameMap_Destroy(&map);
    Player_Destroy();
    Bullet_Destroy();
    UI_Destroy();
}