#pragma once
#include <SFML/Window.h>
#include <SFML/Graphics.h>

sfVector2f Collision_Check(sfVector2f obj, sfVector2f obj2);

sfBool Collision_Check_Bullets(sfVector2f obj, sfVector2f obj2);