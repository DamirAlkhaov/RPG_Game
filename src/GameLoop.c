#include "GameLoop.h"
#include "GameMap.h"
#include <stdio.h>
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Mouse.h>

#define CAMERA_SPEED 5000

GameMap map;

void Loop_Init(){
    GameMap_Init(&map);
}

void Loop_Update(ARGS *args, sfTime dt){
    float deltaTime = sfTime_asSeconds(dt);
    sfRenderWindow *win = args->window;
    sfView *view = args->view;

    //printf("dt: %f\n", deltaTime);

    // do keyboard stuff here
    if (sfKeyboard_isKeyPressed(sfKeyEscape)){
        sfRenderWindow_close(win);
    }  
    
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
    if (sfKeyboard_isKeyPressed(sfKeyLBracket)){
        sfView_zoom(view, 1 + 2 * deltaTime);
    }
    if (sfKeyboard_isKeyPressed(sfKeyRBracket)){
        sfView_zoom(view, 1 - 2 * deltaTime);
    }

    char title[255];
    sprintf(title, "Game | FPS:%d", (int)(1/deltaTime));
    sfRenderWindow_setTitle(win, title);

    GameMap_Render(&map, view, win);
    sfRenderWindow_setView(win, view);
}

void Loop_End(){
    GameMap_Destroy(&map);
}