#include "GameWindow.h"
#include "Args.h"
#include "GameLoop.h"
#include <stdio.h>
#define WIDTH 800
#define HEIGHT 800

void GameWindow_Start(sfRenderWindow* myWindow){
    float ratioX = (float)1920/WIDTH;
    float ratioY = (float)1080/HEIGHT;
    sfVideoMode vm = {sfVideoMode_getDesktopMode().width / ratioX, sfVideoMode_getDesktopMode().width / ratioX};
    sfView *view = sfView_create();
    
    sfEvent event;
    myWindow = sfRenderWindow_create(vm, "Game", sfClose, NULL);
    //sfRenderWindow_setVerticalSyncEnabled(myWindow, (sfBool)1);

    sfClock *cl = sfClock_create();
    sfTime elapsed;

    Loop_Init();

    ARGS args = {myWindow, view, &event};

    sfView_zoom(view, 0.2);
    sfView_setCenter(view, (sfVector2f){400/5,400/5});

    while (sfRenderWindow_isOpen(myWindow)){
        elapsed = sfClock_restart(cl);
        //window events
        while (sfRenderWindow_pollEvent(myWindow, &event)){
            if (event.type == sfEvtClosed){
                sfRenderWindow_close(myWindow);
            }

            //if (event.type == sfEvtResized){
            //    sfView_setSize(view, (sfVector2f){event.size.width, event.size.height});
            //}
        }

        //buffer
        sfRenderWindow_clear(myWindow, sfBlack);

        //Game update
        Loop_Update(&args, elapsed);

        //display
        sfRenderWindow_display(myWindow);
    }

    
    sfView_destroy(view);
    sfRenderWindow_destroy(myWindow);
    Loop_End();
}
