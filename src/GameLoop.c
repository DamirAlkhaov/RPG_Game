#include "GameLoop.h"
#include <SFML/System/Time.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Mouse.h>


float cameraSpeed = 100;

GameMap map;
Player player;


void Loop_Init(){
    GameMap_Init(&map);
    Player_Init(&player);
    Bullet_Init();
}

void Loop_Update(ARGS *args){
    sfTime dt = args->e;
    float deltaTime = sfTime_asSeconds(dt);
    sfRenderWindow *win = args->window;
    sfView *view = args->view;
    sfBool moved = sfFalse;

    // do keyboard stuff here
    if (sfKeyboard_isKeyPressed(sfKeyEscape)){
        sfRenderWindow_close(win);
    }  

    if (sfKeyboard_isKeyPressed(sfKeyD) && sfKeyboard_isKeyPressed(sfKeyW) && !moved){
        sfView_move(view, (sfVector2f){cameraSpeed*deltaTime*cos(45), -cameraSpeed*deltaTime*sin(45)});
        player.lastFaced = NE;
        moved = sfTrue;
    }
    if (sfKeyboard_isKeyPressed(sfKeyA) && sfKeyboard_isKeyPressed(sfKeyW) && !moved){
        sfView_move(view, (sfVector2f){-cameraSpeed*deltaTime*cos(45), -cameraSpeed*deltaTime*sin(45)});
        player.lastFaced = NW;
        moved = sfTrue;
    }
    if (sfKeyboard_isKeyPressed(sfKeyA) && sfKeyboard_isKeyPressed(sfKeyS) && !moved){
        sfView_move(view, (sfVector2f){-cameraSpeed*deltaTime*cos(45), cameraSpeed*deltaTime*sin(45)});
        player.lastFaced = SW;
        moved = sfTrue;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD) && sfKeyboard_isKeyPressed(sfKeyS) && !moved){
        sfView_move(view, (sfVector2f){cameraSpeed*deltaTime*cos(45), cameraSpeed*deltaTime*sin(45)});
        player.lastFaced = SE;
        moved = sfTrue;
    }
    
    if (sfKeyboard_isKeyPressed(sfKeyA) && !moved){
        
        sfView_move(view, (sfVector2f){-cameraSpeed*deltaTime, 0});
        player.lastFaced = WEST;
        moved = sfTrue;

    }
    if (sfKeyboard_isKeyPressed(sfKeyD) && !moved){
        
        sfView_move(view, (sfVector2f){cameraSpeed*deltaTime, 0});
        player.lastFaced = EAST;
        moved = sfTrue;
    }
    if (sfKeyboard_isKeyPressed(sfKeyW) && !moved){
        
        sfView_move(view, (sfVector2f){0, -cameraSpeed*deltaTime});
        player.lastFaced = NORTH;
        moved = sfTrue;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS) && !moved){
        
        sfView_move(view, (sfVector2f){0, cameraSpeed*deltaTime});
        player.lastFaced = SOUTH;
        moved = sfTrue;
    }
    if (sfKeyboard_isKeyPressed(sfKeyLBracket)){
        sfView_zoom(view, 1 + 2 * deltaTime);
    }
    if (sfKeyboard_isKeyPressed(sfKeyRBracket)){
        sfView_zoom(view, 1 - 2 * deltaTime);
    }
    if (sfKeyboard_isKeyPressed(sfKeyLShift)){
        cameraSpeed = 250;
    } else {
        cameraSpeed = 100;
    }
    if (sfKeyboard_isKeyPressed(sfKeyF)){
        Player_Shoot(args, &player);
    }

    sfSprite_setPosition(player.playerSprite, sfView_getCenter(view));

    char title[255];
    sprintf(title, "Menace | FPS:%d", (int)(1/deltaTime));
    sfRenderWindow_setTitle(win, title);
    
    GameMap_Render(&map, view, win);
    sfRenderWindow_setView(win, view);
    Bullet_Update(args);
    sfRenderWindow_drawSprite(win, player.playerSprite, NULL);
}

void Loop_End(){
    GameMap_Destroy();
    Player_Destroy();
    Bullet_Destroy();
}