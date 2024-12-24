#include "GameLoop.h"
#include "GameMap.h"
#include <stdio.h>
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Mouse.h>

#define CAMERA_SPEED 500

GameMap map;

void Loop_Init(){
    GameMap_Init(&map);
}

void Loop_Update(ARGS *args, sfTime dt){
    float deltaTime = sfTime_asSeconds(dt);
    sfRenderWindow *win = args->window;
    sfView *view = args->view;

    // do keyboard stuff here
    if (sfKeyboard_isKeyPressed(sfKeyEscape)){
        sfRenderWindow_close(win);
    }  
    // probably should make the camera as a class and add a move function.
    if (sfKeyboard_isKeyPressed(sfKeyA)){
        
        sfView_move(view, (sfVector2f){-CAMERA_SPEED*deltaTime, 0});

    }
    if (sfKeyboard_isKeyPressed(sfKeyD)){
        
        sfView_move(view, (sfVector2f){CAMERA_SPEED*deltaTime, 0});

    }
    if (sfKeyboard_isKeyPressed(sfKeyW)){
        
        sfView_move(view, (sfVector2f){0, -CAMERA_SPEED*deltaTime});

    }
    if (sfKeyboard_isKeyPressed(sfKeyS)){
        
        sfView_move(view, (sfVector2f){0, CAMERA_SPEED*deltaTime});
        
    }

    GameMap_Render(&map, view, win);
    sfRenderWindow_setView(win, view);
}

void Loop_End(){
    GameMap_Destroy(&map);
}