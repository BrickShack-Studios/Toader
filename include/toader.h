#ifndef TOADER_H
#define TOADER_H

#include <SDL2/SDL.h>

typedef struct Toad
{
    SDL_Texture* texture;
    SDL_Rect* image;
    int velX;
    int velY;
} Toad;

Toad* newToad();

#endif
