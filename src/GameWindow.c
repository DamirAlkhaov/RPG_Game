#include "GameWindow.h"
#include "Args.h"
#include "GameLoop.h"
#include <stdio.h>
#define WIDTH 800
#define HEIGHT 800
float zoomI = 1;

void GameWindow_Start(sfRenderWindow* myWindow){
    float ratioX = (float)1920/WIDTH;
    float ratioY = (float)1080/HEIGHT;
    printf("%f\n", ratioY);
    sfVideoMode vm = {sfVideoMode_getDesktopMode().width / ratioX, sfVideoMode_getDesktopMode().height / ratioY};
    sfView *view = sfView_create();
    
    sfEvent event;
    myWindow = sfRenderWindow_create(vm, "Game", sfClose, NULL);
    sfRenderWindow_setVerticalSyncEnabled(myWindow, (sfBool)1);

    sfClock *cl = sfClock_create();
    sfTime elapsed;

    Loop_Init();

    ARGS args = {myWindow, view, &event};

    while (sfRenderWindow_isOpen(myWindow)){
        elapsed = sfClock_restart(cl);
        //window events
        while (sfRenderWindow_pollEvent(myWindow, &event)){
            if (event.type == sfEvtClosed){
                sfRenderWindow_close(myWindow);
            }
            if (event.type == sfEvtMouseWheelScrolled){
                
                zoomI = zoomI + zoomI * (float)event.mouseWheel.delta;
                printf("%f\n", zoomI);
            }
            //if (event.type == sfEvtResized){
            //    sfView_setSize(view, (sfVector2f){event.size.width, event.size.height});
            //}
        }

        //buffer
        sfRenderWindow_clear(myWindow, sfBlack);

        //Game update
        Loop_Update(&args, elapsed);

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
