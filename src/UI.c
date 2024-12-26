#include "UI.h"
#include <stdio.h>

sfFont *dayDream_font;
sfText *staminaText;
float lastViewSize = 200;

void UI_CreateText(sfText *text){
    sfText_setFont(text, dayDream_font);
    if (text == NULL) puts("failed to create text.");
    sfText_scale(text, (sfVector2f){0.2, 0.2});
    sfText_setOutlineColor(text, sfBlack);
    sfText_setOutlineThickness(text, 10.f);
}

void UI_Init(ARGS *args){
    dayDream_font = sfFont_createFromFile("fonts/Daydream.ttf");
    if (dayDream_font == NULL) puts("failed to load font.");
    staminaText = sfText_create();
    UI_CreateText(staminaText);
}

void UI_Update(ARGS *args, Player *player){
    // get view coords
    sfVector2f viewCenter = sfView_getCenter(args->view);
    sfVector2f viewSize = sfView_getSize(args->view);
    //screen coordinates (in pixels and centered)
    float viewLeft = (viewCenter.x - viewSize.x / 2) + 10 * sfText_getScale(staminaText).x;
    float viewTop = (viewCenter.y - viewSize.y / 2) + 10 * sfText_getScale(staminaText).x;
    float viewRight = (viewCenter.x + viewSize.x / 2);
    float viewBottom = (viewCenter.y + viewSize.y / 2);
    // stamina text
    char textStamina[20];
    sprintf_s(textStamina, 20 * sizeof(char), "Stamina: %.0f", player->stamina);
    sfText_setString(staminaText, textStamina);

    // positioning and scaling the text according to view.
    sfText_setPosition(staminaText, (sfVector2f){viewLeft, viewTop});
    sfText_scale(staminaText, (sfVector2f){viewSize.x/lastViewSize, viewSize.y/lastViewSize});
    lastViewSize = viewSize.x;

    // drawing text.
    sfRenderWindow_drawText(args->window, staminaText, NULL);
}

void UI_Destroy(ARGS *args){
    sfFont_destroy(dayDream_font);
    sfText_destroy(staminaText);
}