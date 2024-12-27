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

sfTexture *crateTXT;
sfRectangleShape *rect;

void Loop_Init(){
    GameMap_Init(&map);
    Player_Init(&player);
    Bullet_Init();
    UI_Init(&player);

    //placeholder for collision tests
    crateTXT = sfTexture_createFromFile("textures/crate.png", NULL);
    rect = sfRectangleShape_create();
    sfRectangleShape_setSize(rect, (sfVector2f){32,32});
    //sfRectangleShape_setFillColor(rect, sfBlack);
    sfRectangleShape_setOrigin(rect, (sfVector2f){16, 16});
    sfRectangleShape_setPosition(rect, (sfVector2f){16+32,16+64});
    sfRectangleShape_setTexture(rect, crateTXT, 0);
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
            
        }
        if (sfKeyboard_isKeyPressed(sfKeyRBracket)){
            sfView_zoom(view, 1 - 2 * deltaTime);
            
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
    
    // collisions (PLACEHOLDER TESTING)
    float deltaX = sfView_getCenter(view).x - sfRectangleShape_getPosition(rect).x;
    float deltaY = sfView_getCenter(view).y - sfRectangleShape_getPosition(rect).y;

    float intersectX = abs(deltaX) - (31);
    float intersectY = abs(deltaY) - (31);   

    //printf("%f %f\n", intersectX, intersectY);
    if (intersectX < 0 && intersectY < 0){
        float push = 0.2;
        if (intersectX > intersectY){
            if (deltaX > 0) {
                sfView_move(view, (sfVector2f){-intersectX * (1 - push), 0.f});
                sfRectangleShape_move(rect, (sfVector2f){intersectX * push, 0.f});
            } else {
                sfView_move(view, (sfVector2f){intersectX* (1 - push), 0.f});
                sfRectangleShape_move(rect, (sfVector2f){-intersectX * push, 0.f});
            }
            
        } else {
            if (deltaY > 0) {
                sfView_move(view, (sfVector2f){0.f, -intersectY* (1 - push)});
                sfRectangleShape_move(rect, (sfVector2f){0.f, intersectY * push});
            } else {
                sfView_move(view, (sfVector2f){0.f, intersectY* (1 - push)});
                sfRectangleShape_move(rect, (sfVector2f){0.f, -intersectY* push});
            }
            
        }
    }

    // update player sprite pos
    sfSprite_setPosition(player.playerSprite, sfView_getCenter(view));

    //rendering
    GameMap_Render(&map, view, win);
    sfRenderWindow_drawRectangleShape(win, rect, NULL);
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
    sfRectangleShape_destroy(rect);
    sfTexture_destroy(crateTXT);
}