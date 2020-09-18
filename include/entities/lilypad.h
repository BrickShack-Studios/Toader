#ifndef LILYPAD_H
#define LILYPAD_H

#include <SDL2/SDL.h>

#include "entity.h"
#include "tween.h"

typedef struct Lilypad
{
    Entity* entity;
    Tween* tween;
} Lilypad;

Lilypad* newLilypad(SDL_Renderer* renderer);

void tickLilypad(Lilypad* lilypad);

void destroyLilypad(Lilypad* lilypad);

#endif
