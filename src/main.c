#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Pretty sure these are the right dimensions based on counting how many 8x8 tiles there were
#define SCREEN_WIDTH 224
#define SCREEN_HEIGHT 240

typedef struct Screen
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int width;
    int height;
} Screen;

typedef struct Toad
{
    SDL_Texture* texture;
    SDL_Rect* image;
    int velX;
    int velY;
} Toad;

Toad* newToad()
{
    // calloc() zeroes everything out, initializing it all for us
    Toad* toad = calloc(1, sizeof(Toad));
    return toad;
}

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

SDL_Texture* loadTexture(const char* path, Screen* screen)
{
    SDL_Texture* texture = NULL;

    SDL_Surface* surface = IMG_Load(path);
    if (!surface)
    {
        printf("Error loading %s. Error: %s\n", path, IMG_GetError());
        goto end;
    }

    texture = SDL_CreateTextureFromSurface(screen->renderer, surface);
    if (!texture)
    {
        printf("Error creating texture from %s. Error: %s\n", path, SDL_GetError());
        goto end;
    }

end:

    if (surface)
        SDL_FreeSurface(surface);

    return texture;
}

bool loadMedia(Toad* toad, Screen* screen)
{
    bool success = true;

    toad->texture = loadTexture("res/sprites/toader/toader.png", screen);
    if (!toad->texture)
    {
        printf("Unable to load %s. Error: %s\n", "res/sprites/toader/toader.png", SDL_GetError());
        success = false;
    }

    toad->image = calloc(1, sizeof(SDL_Rect*));

    toad->image->x = 0;
    toad->image->y = 0;
    toad->image->w = 16;
    toad->image->h = 16;

    return success;
}

void cleanup(Screen* screen, Toad* toad)
{
    if (toad->texture)
    {
        SDL_DestroyTexture(toad->texture);
        toad->texture = NULL;
    }

    if (screen->window)
    {
        SDL_DestroyWindow(screen->window);
        screen->window = NULL;
    }

    if (screen->renderer)
    {
        SDL_DestroyRenderer(screen->renderer);
        screen->renderer = NULL;
    }

    if (screen->texture)
    {
        SDL_DestroyTexture(screen->texture);
        screen->texture = NULL;
    }

    free(screen);
    free(toad);
    IMG_Quit();
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

void move(Toad* toad, Screen* screen)
{
    if (toad->image->x + toad->velX <= SCREEN_WIDTH && toad->image->x + toad->velX >= 0)
        toad->image->x += toad->velX;
    if (toad->image->y + toad->velY <= SCREEN_HEIGHT && toad->image->y + toad->velY >= 0)
        toad->image->y += toad->velY;
    return;
}

int main(int argc, char* argv[])
{
    Screen* screen = init();
    Toad* toad = newToad();

    if (!screen)
    {
        printf("Failed to initialize\n");
        goto cleanup;
    }

    if (!loadMedia(toad, screen))
    {
        printf("Failed to load media\n");
        goto cleanup;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while(SDL_PollEvent(&e))
        {
            //User requests quit
            if(e.type == SDL_QUIT)
                quit = true;

            keyEvents(toad, e);
        }

        move(toad, screen);

        SDL_RenderClear(screen->renderer);
        SDL_RenderCopy(screen->renderer, toad->texture, NULL, toad->image);
        SDL_RenderPresent(screen->renderer);
    }

cleanup:
    cleanup(screen, toad);
    return 0;
}
