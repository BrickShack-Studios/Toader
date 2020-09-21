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

Lilypad* newLilypad(SDL_Renderer* renderer);

void tickLilypad(Lilypad* lilypad);

void destroyLilypad(Lilypad* lilypad);

#endif
