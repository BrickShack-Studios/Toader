#ifndef TOADER_H
#define TOADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "animationmap.h"
#include "animation.h"
#include "entity.h"
#include "screen.h"
#include "soundmap.h"
#include "tween.h"
#include "behaviors/toadstick.h"

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
    Entity* entity;
    Tween* tween;
    Tween* tween2;
    SoundMap* soundMap;
    struct ToadStick* toadStick;
    enum ToadSound soundState;
    enum ToadAnimation animationState;
} Toad;

/**
   Allocates a new Toad struct using the renderer provided by the Screen
 */
Toad* newToad(SDL_Renderer* renderer);

/**
   Adds animations to a Toad's AnimationMap
*/

void addToaderAnimation(Toad* toad, SDL_Renderer* renderer);

/**
   Adds sounds to a Toad's SoundMap
*/

void addToaderSound(Toad* toad);

/**
   Frees all memory taken up by the Toad struct and its members
 */
void destroyToad(Toad* toad);

#endif
