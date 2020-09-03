#ifndef TOADER_H
#define TOADER_H

#include <SDL2/SDL.h>

#include "animationmap.h"
#include "animation.h"
#include "sprite.h"
#include "screen.h"
#include "tween.h"

enum ToadAnimation
{
  JUMP_UP,
  JUMP_DOWN,
  JUMP_LEFT,
  JUMP_RIGHT
};

typedef struct Toad
{
    AnimationMap* animationMap;
    Tween* tween;
    SDL_Rect* rect;
    int numAnimations;
    enum ToadAnimation state;
} Toad;

/**
   Allocates a new Toad struct using the renderer provided by the Screen
 */
Toad* newToad(Screen* screen);

/**
   Frees all memory taken up by the Toad struct and its members
 */
void destroyToad(Toad* toad);

/**
   Adds animations to a Toad's AnimationMap
*/

void addToaderAnimation(Screen* screen, Toad* toad);

#endif
