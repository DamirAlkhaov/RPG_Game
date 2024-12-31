#include <stdio.h>
#include <stdlib.h>
#include <SFML/System/Thread.h>
#include "GameWindow.h"
#include <time.h>

void main(){
    srand(time(NULL));
    
    sfRenderWindow* mWindow;
    
    GameWindow_Start(mWindow);
}
