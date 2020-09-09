#ifndef TOADER_H
#define TOADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "animationmap.h"
#include "animation.h"
#include "sprite.h"
#include "screen.h"
#include "soundmap.h"
#include "tween.h"

enum ToadAnimation
{
  JUMP_UP,
  JUMP_DOWN,
  JUMP_LEFT,
  JUMP_RIGHT
};

enum ToadSound
{
    HOP,
    LIFEUP,
    SPLAT,
    SPLASH
};

typedef struct Toad
{
    AnimationMap* animationMap;
    Tween* tween;
    SDL_Rect* rect;
    SoundMap* soundMap;
    enum ToadSound soundState;
    enum ToadAnimation animationState;
} Toad;

/**
   Allocates a new Toad struct using the renderer provided by the Screen
 */
Toad* newToad(SDL_Renderer* renderer);

/**
   Frees all memory taken up by the Toad struct and its members
 */
void destroyToad(Toad* toad);

/**
   Adds animations to a Toad's AnimationMap
*/

void addToaderAnimation(SDL_Renderer* renderer, Toad* toad);

/**
   Adds sounds to a Toad's SoundMap
*/

void addToaderSound(Toad* toad);

#endif
