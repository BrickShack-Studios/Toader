#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>

#include "screen.h"

typedef struct Text
{
    SDL_Texture* texture;
    SDL_Rect* rect;
    char* str;
} Text;

/**
   Allocates a new Text struct
*/

Text* newText(SDL_Renderer* renderer, char* str, int x, int y);

/**
   Draws a Text struct to the screen
*/

void drawText(Text* text, SDL_Renderer* renderer);

/**
   Frees all memory taken by a Text struct and its members
*/

void destroyText(Text* text);

#endif
