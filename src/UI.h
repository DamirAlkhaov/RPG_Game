#pragma once
#include <SFML/Window.h>
#include "Args.h"
#include "Player.h"

void UI_Init(Player *player);

void UI_Update(ARGS *args);

void UI_SetZoom(float zoomDT);

void UI_Destroy();