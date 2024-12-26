#include "GameLoop.h"
#include <SFML/System/Time.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Mouse.h>


float cameraSpeed = 100;

GameMap map;
Player player;
sfFont *dayDream_font;
sfText *text;


void Loop_Init(){
    GameMap_Init(&map);
    Player_Init(&player);
    Bullet_Init();
    dayDream_font = sfFont_createFromFile("fonts/Daydream.ttf");
    if (dayDream_font == NULL) puts("failed to load font.");
    text = sfText_create();
    sfText_setFont(text, dayDream_font);
    if (text == NULL) puts("failed to create text.");
    sfText_setString(text, "MENACE");
    sfText_scale(text, (sfVector2f){0.2, 0.2});
    sfText_setOutlineColor(text, sfBlack);
    sfText_setOutlineThickness(text, 10.f);
    puts("FUCK");
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
        sfText_scale(text, (sfVector2f){1 + 2 *deltaTime, 1 + 2*deltaTime});
    }
    if (sfKeyboard_isKeyPressed(sfKeyRBracket)){
        sfView_zoom(view, 1 - 2 * deltaTime);
        sfText_scale(text, (sfVector2f){1 - 2 *deltaTime, 1 - 2*deltaTime});
    }
    if (sfKeyboard_isKeyPressed(sfKeyLShift) && ((player.stamina > 0 && !player.cooldown) || (player.stamina >= 20 && player.cooldown))){
        cameraSpeed = 250;
        player.stamina -= 25 * deltaTime;
        if (player.stamina < 0) {player.stamina = 0; player.cooldown = sfTrue;}
        if (player.stamina >= 20) player.cooldown = sfFalse;
    } else {
        cameraSpeed = 100;
        player.stamina += 5 * deltaTime;
        if (player.stamina > 100) player.stamina = 100;
    }
    if (sfKeyboard_isKeyPressed(sfKeyF)){
        Player_Shoot(args, &player);
    }

    sfSprite_setPosition(player.playerSprite, sfView_getCenter(view));

    char title[255];
    sprintf(title, "Menace | FPS:%d", (int)(1/deltaTime));
    sfRenderWindow_setTitle(win, title);

    sfVector2f viewCenter = sfView_getCenter(view);
    sfVector2f viewSize = sfView_getSize(view);
    
    //screen coordinates (in pixels and centered)
    float viewLeft = (viewCenter.x - viewSize.x / 2) + 10 * sfText_getScale(text).x;
    float viewTop = (viewCenter.y - viewSize.y / 2) + 10 * sfText_getScale(text).x;
    float viewRight = (viewCenter.x + viewSize.x / 2);
    float viewBottom = (viewCenter.y + viewSize.y / 2);
    
    GameMap_Render(&map, view, win);
    sfRenderWindow_setView(win, view);
    Bullet_Update(args);
    sfRenderWindow_drawSprite(win, player.playerSprite, NULL);

    char textDT[20];
    sprintf_s(textDT, 20 * sizeof(char), "Stamina: %.0f", player.stamina);
    sfText_setString(text, textDT);

    sfText_setPosition(text, (sfVector2f){viewLeft, viewTop});
    sfRenderWindow_drawText(win, text, NULL);
}

void Loop_End(){
    GameMap_Destroy(&map);
    Player_Destroy();
    Bullet_Destroy();
}