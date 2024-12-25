// where all the mfing game logic happens
#pragma once
#include "GameMap.h"
#include "Player.h"


void Loop_Init();

//Update game logic function, takes in sfTime which is Delta Time.
void Loop_Update(ARGS *arg);

void Loop_End();