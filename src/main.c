#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

// Pretty sure these are the right dimensions based on counting how many 8x8 tiles there were
#define SCREEN_WIDTH 224
#define SCREEN_HEIGHT 240

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	printf("Error initializing SDL: %s\n", SDL_GetError());
	goto cleanup;
    }

    window = SDL_CreateWindow("Toader", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
	printf("Error creating window: %s\n", SDL_GetError());
        goto cleanup;
    }

    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);

cleanup:
    
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
