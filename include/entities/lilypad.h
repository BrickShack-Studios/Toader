#ifndef LILYPAD_H
#define LILYPAD_H

#include <SDL2/SDL.h>

#include "entity.h"
#include "tween.h"

#include "behaviors/toadstick.h"

typedef struct Lilypad
{
    Entity* entity;
    Tween* tween;
    ToadStick* toadStick;
} Lilypad;

/**
   Allocates a new Lilypad struct using the renderer provided by the Screen.
 */
Lilypad* newLilypad(SDL_Renderer* renderer);

/**
   Performs a tween of the given Lilypad and centers its hitbox.
*/
void tickLilypad(Lilypad* lilypad);

/**
   Frees all memory taken up by the Lilypad struct and its members.
 */
void destroyLilypad(Lilypad* lilypad);

#endif
