#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "toader.h"
#include "screen.h"
#include "sprite.h"
#include "map.h"
#include "tween.h"

#include "macros.h"

void cleanup(Screen* screen, Toad* toad)
{
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

    if (toad)
        destroyToad(toad);

    free(screen);
    IMG_Quit();
    SDL_Quit();
    return;
}

bool inBounds(int x, int y)
{
    return ((x >= 0 && x <= 208) && (y >= 0 && y <= 224));
}

void move(Toad* toad, SDL_Event e)
{
    if (toad->tween->isActive)
        return;
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_w:
            case SDLK_UP:
                if (inBounds(toad->sprite->rect->x, toad->sprite->rect->y - 16))
                    initTween(toad->tween, &toad->sprite->rect->y, normalizeTime(200), toad->sprite->rect->y, toad->sprite->rect->y - 16);
                break;
            case SDLK_a:
            case SDLK_LEFT:
                if (inBounds(toad->sprite->rect->x - 16, toad->sprite->rect->y))
                    initTween(toad->tween, &toad->sprite->rect->x, normalizeTime(200), toad->sprite->rect->x, toad->sprite->rect->x - 16);
                break;
            case SDLK_s:
            case SDLK_DOWN:
                if (inBounds(toad->sprite->rect->x, toad->sprite->rect->y + 16))
                    initTween(toad->tween, &toad->sprite->rect->y, normalizeTime(200), toad->sprite->rect->y, toad->sprite->rect->y + 16);
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                if (inBounds(toad->sprite->rect->x + 16, toad->sprite->rect->y))
                    initTween(toad->tween, &toad->sprite->rect->x, normalizeTime(200), toad->sprite->rect->x, toad->sprite->rect->x + 16);
                break;
        }
    }
    return;
}

int main(int argc, char* argv[])
{
    Screen* screen = init();
    SpriteMap* worldMap = createWorldMap(screen);
    Toad* toad = newToad(screen);

    if (!screen)
    {
        SDL_Log("Failed to initialize\n");
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

            move(toad, e);
        }
	tickTween(toad->tween);
	
        SDL_RenderClear(screen->renderer);

        drawSpriteMap(worldMap, screen->renderer);
        drawSprite(toad->sprite, screen->renderer);

        SDL_RenderPresent(screen->renderer);
    }

cleanup:
    cleanup(screen, toad);
    destroySpriteMap(worldMap);
    return 0;
}
