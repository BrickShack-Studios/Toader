#ifndef TOADER_H
#define TOADER_H

#include <SDL2/SDL.h>

#include "sprite.h"
#include "screen.h"

typedef struct Toad
{
    Sprite* sprite;
    int velX;
    int velY;
} Toad;

/**
   Allocates a new Toad struct using the renderer provided by the Screen
 */
Toad* newToad(Screen* screen);

/**
   Frees all memory taken up by the Toad struct and its members
 */
void destroyToad(Toad* toad);

#endif
