#include "GameWindow.h"
#include "GameLoop.h"
#include "GameMap.h"
#include <stdio.h>
#define WIDTH 800
#define HEIGHT 800
#define SCALE 5

void createMainWindow(sfRenderWindow* myWindow){
    sfVideoMode vm = {WIDTH,HEIGHT};
    sfView *view = sfView_create();
    
    sfEvent event;
    myWindow = sfRenderWindow_create(vm, "Game", sfClose, NULL);
    sfRenderWindow_setVerticalSyncEnabled(myWindow, (sfBool)1);

    sfClock *cl = sfClock_create();
    sfTime elapsed;

    GameMap map;
    GameMap_Init(&map);

    while (sfRenderWindow_isOpen(myWindow)){
        elapsed = sfClock_restart(cl);
        //window events
        while (sfRenderWindow_pollEvent(myWindow, &event)){
            if (event.type == sfEvtClosed){
                sfRenderWindow_close(myWindow);
            }
            if (event.type == sfEvtResized){
                sfVector2f scrnSize = (sfVector2f){(float)event.size.width, (float)event.size.height};
                sfView_setSize(view, scrnSize);
                scrnSize.x /= 2; scrnSize.y /= 2;
                sfView_setCenter(view, scrnSize);
                
                sfRenderWindow_setView(myWindow, view);
            }
        }

        //Game update
        update(myWindow, elapsed);

        //buffer
        sfRenderWindow_clear(myWindow, sfBlack);
        
        //map rendering (put in a seperate file later.)
        for (int i = 0; i < map.size; i++){
            for (int j = 0; j < map.size; j++){
                sfSprite_setScale(map.tiles[i][j]->sprite, (sfVector2f){SCALE, SCALE});
                sfSprite_setPosition(map.tiles[i][j]->sprite, (sfVector2f){i*16*SCALE, j*16*SCALE});
                renderTile(myWindow, map.tiles[i][j]);
            }
        }

        //fps title would be better if I made this into a easier function and used it in the Game Loop function.
        char title[255];
        sprintf(title, "Game | FPS:%d", (int)(1/sfTime_asSeconds(elapsed)));
        sfRenderWindow_setTitle(myWindow, title);

        //display
        sfRenderWindow_display(myWindow);
    }

    
    sfView_destroy(view);
    sfRenderWindow_destroy(myWindow);
    GameMap_Destroy(&map);
}
