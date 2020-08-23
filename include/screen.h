#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>

extern const int MAX_FPS;
extern const int TICKS_PER_FRAME;

typedef struct Screen
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int width;
    int height;
} Screen;

/**
   Initializes a new Screen* object with resolution of 224x240
 */
Screen* init();

#endif
