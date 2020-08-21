#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>

typedef struct Screen
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int width;
    int height;
} Screen;

Screen* init();

#endif
