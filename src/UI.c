#include "UI.h"
#include <stdio.h>

sfFont *dayDream_font;
sfText *staminaText;
sfText *healthText;
Player *playerPointer;
float lastViewSize = 200;

void UI_CreateText(sfText *text, float scale){
    sfText_setFont(text, dayDream_font);
    if (text == NULL) puts("failed to create text.");
    sfText_scale(text, (sfVector2f){scale * 0.2, scale * 0.2});
    sfText_setOutlineColor(text, sfBlack);
    sfText_setOutlineThickness(text, 10.f);
}

void UI_PositionText(sfVector2f viewCenter, sfVector2f viewSize, sfText *text, sfVector2f pos){
    //screen coordinates (in pixels and centered)
    float viewLeft = (viewCenter.x - viewSize.x / 2) + pos.x * sfText_getScale(text).x;
    float viewTop = (viewCenter.y - viewSize.y / 2) + pos.y * sfText_getScale(text).x;

    // positioning and scaling the text according to view.
    sfText_setPosition(text, (sfVector2f){viewLeft, viewTop});
    sfText_scale(text, (sfVector2f){viewSize.x/lastViewSize, viewSize.y/lastViewSize});
}

void UI_Init(Player *playerP){
    dayDream_font = sfFont_createFromFile("fonts/Daydream.ttf");
    if (dayDream_font == NULL) puts("failed to load font.");
    staminaText = sfText_create();
    healthText = sfText_create();
    UI_CreateText(staminaText, 1);
    UI_CreateText(healthText, 1);
    playerPointer = playerP;
}

void UI_Update(ARGS *args){
    // get view coords
    sfVector2f viewCenter = sfView_getCenter(args->view);
    sfVector2f viewSize = sfView_getSize(args->view);
    
    UI_PositionText(viewCenter, viewSize, staminaText, (sfVector2f){10, 10});
    UI_PositionText(viewCenter, viewSize, healthText, (sfVector2f){10,700});
    lastViewSize = viewSize.x;

    char textStamina[20];
    sprintf_s(textStamina, 20 * sizeof(char), "Stamina: %.0f", playerPointer->stamina);
    sfText_setString(staminaText, textStamina);

    char textHealth[20];
    sprintf_s(textHealth, 20 * sizeof(char), "Health: %.0f", playerPointer->health);
    sfText_setString(healthText, textHealth);
    // drawing text.
    sfRenderWindow_drawText(args->window, staminaText, NULL);
    sfRenderWindow_drawText(args->window, healthText, NULL);
}

void UI_Destroy(ARGS *args){
    sfFont_destroy(dayDream_font);
    sfText_destroy(staminaText);
    sfText_destroy(healthText);
}