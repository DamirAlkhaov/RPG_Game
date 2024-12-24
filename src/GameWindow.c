#include "GameWindow.h"
#include "GameLoop.h"
#define WIDTH 800
#define HEIGHT 800

void createMainWindow(sfRenderWindow* myWindow){
    sfVideoMode vm = {WIDTH,HEIGHT};
    sfView *view = sfView_create();
    
    sfEvent event;
    myWindow = sfRenderWindow_create(vm, "Game", sfClose, NULL);
    sfRenderWindow_setVerticalSyncEnabled(myWindow, (sfBool)1);

    sfClock *cl = sfClock_create();
    sfTime elapsed;

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
        update(elapsed);

        //buffer
        sfRenderWindow_clear(myWindow, sfBlack);

        //display
        sfRenderWindow_display(myWindow);
    }

    
    sfView_destroy(view);
    sfRenderWindow_destroy(myWindow);
}
