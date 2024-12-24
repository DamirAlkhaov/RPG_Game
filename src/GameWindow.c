#include "GameWindow.h"
#define WIDTH 800
#define HEIGHT 800

void createMainWindow(sfRenderWindow* myWindow){
    sfVideoMode vm = {WIDTH,HEIGHT};
    sfView *view = sfView_create();
    
    sfEvent event;
    myWindow = sfRenderWindow_create(vm, "Game", sfClose, NULL);
    sfRenderWindow_setFramerateLimit(myWindow, 60);

    while (sfRenderWindow_isOpen(myWindow)){
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

        sfRenderWindow_clear(myWindow, sfBlack);

        sfRenderWindow_display(myWindow);
    }

    
    sfView_destroy(view);
    sfRenderWindow_destroy(myWindow);
}
