#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "screen.h"

// TODO: figure out how C timers interact with SDL to get FPS capping working
//const int MAX_FPS = 60;
//const int TICKS_PER_FRAME = 1000;

Screen* init()
{
    Screen* screen = malloc(sizeof(Screen));
    screen->width = 224;
    screen->height = 240;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL Could not initialize. Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(screen->window);
        free(screen);
        goto end;
    }

    screen->window = SDL_CreateWindow("Toader", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen->width, screen->height, SDL_WINDOW_SHOWN);
    if (!screen->window)
    {
        SDL_Log("Window could not be created. Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(screen->window);
        free(screen);
        goto end;
    }

    screen->renderer = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);
    if (!screen->renderer)
    {
        SDL_Log("Renderer could not be created. Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(screen->window);
        free(screen);
        goto end;
    }

    SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 255);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        SDL_Log("SDL_Image could not initialize. Error: %s", IMG_GetError());
        SDL_DestroyRenderer(screen->renderer);
        SDL_DestroyWindow(screen->window);
        free(screen);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        SDL_DestroyRenderer(screen->renderer);
        SDL_DestroyWindow(screen->window);
        free(screen);
    }

end:
    return screen;
}
