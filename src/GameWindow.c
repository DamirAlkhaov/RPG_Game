#include "GameWindow.h"
#include "GameLoop.h"
#include <stdio.h>
#define WIDTH 800
#define HEIGHT 800

void GameWindow_Start(sfRenderWindow* myWindow){
    sfVideoMode vm = {WIDTH,HEIGHT};
    sfView *view = sfView_create();
    
    sfEvent event;
    myWindow = sfRenderWindow_create(vm, "Game", sfClose, NULL);
    sfRenderWindow_setVerticalSyncEnabled(myWindow, (sfBool)1);

    sfClock *cl = sfClock_create();
    sfTime elapsed;

    Loop_Init();

    while (sfRenderWindow_isOpen(myWindow)){
        elapsed = sfClock_restart(cl);
        //window events
        while (sfRenderWindow_pollEvent(myWindow, &event)){
            if (event.type == sfEvtClosed){
                sfRenderWindow_close(myWindow);
            }
        }

        //buffer
        sfRenderWindow_clear(myWindow, sfBlack);

        //Game update
        Loop_Update(myWindow, view, elapsed);

        //fps title would be better if I made this into a easier function and used it in the Game Loop function.
        char title[255];
        sprintf(title, "Game | FPS:%d", (int)(1/sfTime_asSeconds(elapsed)));
        sfRenderWindow_setTitle(myWindow, title);

        //display
        sfRenderWindow_display(myWindow);
    }

    
    sfView_destroy(view);
    sfRenderWindow_destroy(myWindow);
    Loop_End();
}
