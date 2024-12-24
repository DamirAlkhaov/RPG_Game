// where all the mfing game logic happens
#pragma once
#include <SFML/System/Time.h>
#include <SFML/Graphics.h>

void Loop_Init();

//Update game logic function, takes in sfTime which is Delta Time.
void Loop_Update(sfRenderWindow *win, sfView *view, sfTime e);

void Loop_End();