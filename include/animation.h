#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>

#include "screen.h"
#include "sprite.h"
#include "tween.h"

#include <time.h>

typedef struct Animation
{
    Sprite* strip;
    SDL_Rect* currentFrame;
    Tween* tween;
    int frameCount;
    int frame;
    clock_t duration;
} Animation;

/**
   Allocates a new Animation using the provided parameters
*/

Animation* newAnimation(Screen* screen, const char* spriteFilePath, int frames, int height, int width, clock_t duration);

/**
   Draws an Animation from an AnimationMap to the screen
*/

void drawAnimation(Animation* animation, SDL_Renderer* renderer, SDL_Rect* rect);

/**
   Initalizes an Animation's Tween struct
*/

void playAnimation(Animation* animation);

/**
   Frees all memory taken up by an Animation struct and its members
*/

void destroyAnimation(Animation* animation);

#endif
