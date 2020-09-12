#ifndef ANIMATIONMAP_H
#define ANIMATIONMAP_H

#include "animation.h"

typedef struct AnimationMap
{
    Animation** animations;
    SDL_Rect* position;
    unsigned int numAnimations;
    unsigned int currentAnimation;
} AnimationMap;

/**
   Allocates a new AnimationMap with a provided number of animations
*/

AnimationMap* newAnimationMap(unsigned int numAnimations);

/**
   Sets the current animation to be played
*/

void setAnimation(AnimationMap* animationMap, unsigned int animation);

/**
   Draws an Animation from an AnimationMap to the screen
*/

void drawAnimationMap(AnimationMap* animationMap, SDL_Renderer* renderer);

/**
   Frees all memory taken by an AnimationMap struct and its members
*/

void destroyAnimationMap(AnimationMap* animationMap);

#endif
