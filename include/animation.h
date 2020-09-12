#ifndef ANIMATION_H
#define ANIMATION_H

#include <time.h>

#include <SDL2/SDL.h>

#include "screen.h"
#include "sprite.h"
#include "tween.h"

typedef struct Animation
{
    Sprite* strip;
    SDL_Rect* currentFrame;
    SDL_Rect* position;
    Tween* tween;
    int frameCount;
    int frame;
    unsigned int duration;
} Animation;

/**
   Allocates a new Animation using the provided parameters
*/

Animation* newAnimation(SDL_Renderer* renderer, const char* spriteFilePath, int frames, int height, int width, unsigned int duration);

/**
   Draws an Animation from an AnimationMap to the screen
*/

void drawAnimation(Animation* animation, SDL_Renderer* renderer);

/**
   Initalizes an Animation's Tween struct
*/

void playAnimation(Animation* animation);

/**
   Frees all memory taken up by an Animation struct and its members
*/

void destroyAnimation(Animation* animation);

#endif
