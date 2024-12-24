#include "GameLoop.h"
#include <stdio.h>
#include <SFML/Window/Keyboard.h>
#define CAMERA_SPEED 300



void update(sfRenderWindow *win, sfTime dt){
    float deltaTime = sfTime_asSeconds(dt);

    // do keyboard stuff here
    if (sfKeyboard_isKeyPressed(sfKeyEscape)){
        sfRenderWindow_close(win);
    }  
    // probably should make the camera as a class and add a move function.
    if (sfKeyboard_isKeyPressed(sfKeyA)){
        sfView *view = sfRenderWindow_getView(win);
        sfView_move(view, (sfVector2f){-CAMERA_SPEED*deltaTime, 0});
        sfRenderWindow_setView(win, view);
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)){
        sfView *view = sfRenderWindow_getView(win);
        sfView_move(view, (sfVector2f){CAMERA_SPEED*deltaTime, 0});
        sfRenderWindow_setView(win, view);
    }
    if (sfKeyboard_isKeyPressed(sfKeyW)){
        sfView *view = sfRenderWindow_getView(win);
        sfView_move(view, (sfVector2f){0, -CAMERA_SPEED*deltaTime});
        sfRenderWindow_setView(win, view);
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)){
        sfView *view = sfRenderWindow_getView(win);
        sfView_move(view, (sfVector2f){0, CAMERA_SPEED*deltaTime});
        sfRenderWindow_setView(win, view);
    }
}