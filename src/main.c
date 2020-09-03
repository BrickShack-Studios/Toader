#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "animation.h"
#include "map.h"
#include "screen.h"
#include "sprite.h"
#include "toader.h"
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

void move(Screen* screen, Toad* toad, SDL_Event e)
{
    if (toad->tween->isActive)
        return;

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_w:
            case SDLK_UP:
                if (inBounds(toad->rect->x, toad->rect->y - 16))
                {
                    initTween(toad->tween, &toad->rect->y, 500, toad->rect->y, toad->rect->y - 16);
                    setAnimation(toad->animationMap, JUMP_UP);
                }
                break;
            case SDLK_a:
            case SDLK_LEFT:
                if (inBounds(toad->rect->x - 16, toad->rect->y))
                {
                    initTween(toad->tween, &toad->rect->x, 500, toad->rect->x, toad->rect->x - 16);
                    setAnimation(toad->animationMap, JUMP_LEFT);
                }
                break;
            case SDLK_s:
            case SDLK_DOWN:
                if (inBounds(toad->rect->x, toad->rect->y + 16))
                {
                    initTween(toad->tween, &toad->rect->y, 500, toad->rect->y, toad->rect->y + 16);
                    setAnimation(toad->animationMap, JUMP_DOWN);
                }
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                if (inBounds(toad->rect->x + 16, toad->rect->y))
                {
                    initTween(toad->tween, &toad->rect->x, 500, toad->rect->x, toad->rect->x + 16);
                    setAnimation(toad->animationMap, JUMP_RIGHT);
                }
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

            move(screen, toad, e);
        }
        tickTween(toad->tween);

        SDL_RenderClear(screen->renderer);

        drawSpriteMap(worldMap, screen->renderer);

        drawAnimationMap(toad->animationMap, screen->renderer, toad->rect);

        SDL_RenderPresent(screen->renderer);
    }

cleanup:
    cleanup(screen, toad);
    destroySpriteMap(worldMap);
    return 0;
}
