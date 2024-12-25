#include "GameLoop.h"
#include "GameMap.h"
#include "Player.h"s
#include <stdio.h>
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Mouse.h>

float cameraSpeed = 100;

GameMap map;
Player player;


void Loop_Init(){
    GameMap_Init(&map);
    Player_Init(&player);
}

void Loop_Update(ARGS *args, sfTime dt){
    float deltaTime = sfTime_asSeconds(dt);
    sfRenderWindow *win = args->window;
    sfView *view = args->view;

    // do keyboard stuff here
    if (sfKeyboard_isKeyPressed(sfKeyEscape)){
        sfRenderWindow_close(win);
    }  
    
    if (sfKeyboard_isKeyPressed(sfKeyA)){
        
        sfView_move(view, (sfVector2f){-cameraSpeed*deltaTime, 0});
        player.lastFaced = WEST;

    }
    if (sfKeyboard_isKeyPressed(sfKeyD)){
        
        sfView_move(view, (sfVector2f){cameraSpeed*deltaTime, 0});
        player.lastFaced = EAST;
    }
    if (sfKeyboard_isKeyPressed(sfKeyW)){
        
        sfView_move(view, (sfVector2f){0, -cameraSpeed*deltaTime});
        player.lastFaced = NORTH;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)){
        
        sfView_move(view, (sfVector2f){0, cameraSpeed*deltaTime});
        player.lastFaced = SOUTH;
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

    sfSprite_setPosition(player.playerSprite, sfView_getCenter(view));

    char title[255];
    sprintf(title, "Menace | FPS:%d", (int)(1/deltaTime));
    sfRenderWindow_setTitle(win, title);
    
    GameMap_Render(&map, view, win);
    sfRenderWindow_setView(win, view);
    sfRenderWindow_drawSprite(win, player.playerSprite, NULL);
}

void Loop_End(){
    GameMap_Destroy(&map);
    Player_Destroy(&player);
}