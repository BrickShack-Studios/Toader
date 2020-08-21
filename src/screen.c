#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "screen.h"

Screen* init()
{
    Screen* screen = malloc(sizeof(Screen));
    screen->width = 224;
    screen->height = 240;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Could not initialize. Error: %s\n", SDL_GetError());
        free(screen);
        goto end;
    }

    screen->window = SDL_CreateWindow("Toader", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen->width, screen->height, SDL_WINDOW_SHOWN);
    if (!screen->window)
    {
        printf("Window could not be created. Error: %s\n", SDL_GetError());
        free(screen);
        goto end;
    }

    screen->renderer = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);
    if (!screen->renderer)
    {
        printf("Renderer could not be created. Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(screen->window);
        free(screen);
        goto end;
    }

    SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 255);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_Image could not initialize. Error: %s", IMG_GetError());
        SDL_DestroyRenderer(screen->renderer);
        SDL_DestroyWindow(screen->window);
        free(screen);
    }

end:
    return screen;
}
