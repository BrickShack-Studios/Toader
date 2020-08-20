#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

// Pretty sure these are the right dimensions based on counting how many 8x8 tiles there were
#define SCREEN_WIDTH 224
#define SCREEN_HEIGHT 240

typedef struct Screen
{
    SDL_Window* window;
    SDL_Surface* screenSurface;
} Screen;

typedef struct Toad
{
    SDL_Surface* toader;
    int posX;
    int posY;
    int velX;
    int velY;
} Toad;

Screen* init()
{
    Screen* screen = malloc(sizeof(Screen));

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Could not initialize. Error: %s\n", SDL_GetError());
        free(screen);
        goto end;
    }

    screen->window = SDL_CreateWindow("Toader", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!screen->window)
    {
        printf("Window could not be created. Error: %s\n", SDL_GetError());
        free(screen);
        goto end;
    }

    screen->screenSurface = SDL_GetWindowSurface(screen->window);

end:
    return screen;
}

bool loadMedia(Toad* toad)
{
    bool success = true;

    toad->toader = SDL_LoadBMP("res/bmp/toader.bmp");
    if (!toad->toader)
    {
        printf("Unable to load %s. Error: %s\n", "res/bmp/toader.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

void cleanup(Screen* screen, Toad* toad)
{
    if (toad->toader)
    {
        SDL_FreeSurface(toad->toader);
        toad->toader = NULL;
    }

    if (screen->window)
    {
        SDL_DestroyWindow(screen->window);
        screen->window = NULL;
    }

    free(screen);
    SDL_Quit();
    return;
}

void keyEvents(Toad* toad, SDL_Event e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_w:
            case SDLK_UP:
                toad->velY -= 1;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                toad->velX -= 1;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                toad->velY += 1;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                toad->velX += 1;
                break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_w:
            case SDLK_UP:
                toad->velY += 1;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                toad->velX += 1;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                toad->velY -= 1;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                toad->velX -= 1;
                break;
        }
    }
    return;
}

int main(int argc, char* argv[])
{
    Screen* screen = init();
    Toad* toad;

    if (!screen)
    {
        printf("Failed to initialize\n");
        goto cleanup;
    }

    if (!loadMedia(toad))
    {
        printf("Failed to load media\n");
        goto cleanup;
    }

    SDL_BlitSurface(toad->toader, NULL, screen->screenSurface, NULL);
    SDL_UpdateWindowSurface(screen->window);

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while(SDL_PollEvent(&e))
        {
            //User requests quit
            if(e.type == SDL_QUIT)
                quit = true;
        }
        keyEvents(toad, e);
    }

cleanup:
    cleanup(screen, toad);
    return 0;
}
