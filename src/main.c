#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "toader.h"
#include "screen.h"
#include "sprite.h"
#include "map.h"

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
    if (toad->sprite->rect->x + toad->sprite->rect->w + toad->velX <= screen->width && toad->sprite->rect->x + toad->velX >= 0)
        toad->sprite->rect->x += toad->velX;
    if (toad->sprite->rect->y + toad->sprite->rect->h + toad->velY <= screen->height && toad->sprite->rect->y + toad->velY >= 0)
        toad->sprite->rect->y += toad->velY;
    return;
}

int main(int argc, char* argv[])
{
    Screen* screen = init();
    SpriteMap* worldMap = createWorldMap(screen);
    Toad* toad = newToad(screen);

    if (!screen)
    {
        printf("Failed to initialize\n");
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

	drawSpriteMap(worldMap, screen->renderer);
        drawSprite(toad->sprite, screen->renderer);
	
        SDL_RenderPresent(screen->renderer);
    }

cleanup:
    cleanup(screen, toad);
    destroySpriteMap(worldMap);
    return 0;
}
