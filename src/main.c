#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "entity.h"
#include "spritemap.h"
#include "screen.h"
#include "sprite.h"
#include "toader.h"
#include "tween.h"
#include "text.h"

#include "entities/lilypad.h"

#include "behaviors/toadstick.h"

const unsigned int MILLISECONDS_PER_FRAME = 1000 / 60;

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
    Mix_Quit();
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

    int nearestX = (int)((float)toad->entity->position->x / 16.0f + 0.5f) * 16;
    int nearestY = (int)((float)toad->entity->position->y / 16.0f + 0.5f) * 16;

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_w:
            case SDLK_UP:
                if (inBounds(toad->entity->position->x, toad->entity->position->y - 16))
                {
                    Mix_PlayChannel(-1, toad->soundMap->sounds[HOP], 0);
                    initTween(toad->tween, &toad->entity->position->y, 200, toad->entity->position->y, nearestY - 16);
                    initTween(toad->tween2, &toad->entity->position->x, 200, toad->entity->position->x, nearestX);
                    setAnimation(toad->entity->aMap, JUMP_UP);
                }
                break;
            case SDLK_a:
            case SDLK_LEFT:
                if (inBounds(toad->entity->position->x - 16, toad->entity->position->y))
                {
                    Mix_PlayChannel(-1, toad->soundMap->sounds[HOP], 0);
                    initTween(toad->tween, &toad->entity->position->x, 200, toad->entity->position->x, nearestX - 16);
                    initTween(toad->tween2, &toad->entity->position->y, 200, toad->entity->position->y, nearestY);
                    setAnimation(toad->entity->aMap, JUMP_LEFT);
                }
                break;
            case SDLK_s:
            case SDLK_DOWN:
                if (inBounds(toad->entity->position->x, toad->entity->position->y + 16))
                {
                    Mix_PlayChannel(-1, toad->soundMap->sounds[HOP], 0);
                    initTween(toad->tween, &toad->entity->position->y, 200, toad->entity->position->y, nearestY + 16);
                    initTween(toad->tween2, &toad->entity->position->x, 200, toad->entity->position->x, nearestX);
                    setAnimation(toad->entity->aMap, JUMP_DOWN);
                }
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                if (inBounds(toad->entity->position->x + 16, toad->entity->position->y))
                { 
                    Mix_PlayChannel(-1, toad->soundMap->sounds[HOP], 0);
                    initTween(toad->tween, &toad->entity->position->x, 200, toad->entity->position->x, nearestX + 16);
                    initTween(toad->tween2, &toad->entity->position->y, 200, toad->entity->position->y, nearestY);
                    setAnimation(toad->entity->aMap, JUMP_RIGHT);
                }
                break;
        }
    }
    return;
}

int main(int argc, char* argv[])
{
    Screen* screen = init();
    SpriteMap* worldMap = createWorldMap(screen->renderer);
    Toad* toad = newToad(screen->renderer);

    if (!screen)
    {
        SDL_Log("Failed to initialize\n");
        goto cleanup;
    }

    bool quit = false;
    SDL_Event e;

    Text* nut = newText(screen->renderer, "nut", 6, 9);

    unsigned int frameCount = 0;
    unsigned int currentTime = SDL_GetTicks();
    unsigned int lastFrame = currentTime;
    unsigned int lastPrint = currentTime;

    Lilypad* lilypad = newLilypad(screen->renderer);

    const unsigned int numToadSticks = 1;
    ToadStick** toadSticks = calloc(numToadSticks, sizeof(ToadStick*));
    toadSticks[0] = lilypad->toadStick;
    
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
        tickTween(toad->tween2);
        tickLilypad(lilypad);

        unsigned int i;
        bool touchedToadStick = false;
        centerHitbox(toad->entity);
        for (i = 0; i < numToadSticks; i++)
        {
            //SDL_Log("ToadStick at (%i, %i)\nToader at (%i, %i)\n\n", toadSticks[i]->hitbox->x, toadSticks[i]->hitbox->y, toad->entity->hitbox->x, toad->entity->hitbox->y);
            if (isColliding_c(toadSticks[i]->hitbox, toad->entity->hitbox))
            {
                //SDL_Log("Collision!\n");
                touchedToadStick = true;
                if (toadSticks[i] != toad->toadStick)
                {
                    if (toad->toadStick)
                        toad->toadStick->toad = NULL;
                    
                    toad->toadStick = toadSticks[i];
                    toad->toadStick->toad = toad;
                }

                break;
            }
        }

        if (touchedToadStick)
            tickToadStick(toad->toadStick);
        else if (toad->toadStick)
        {
            toad->toadStick->toad = NULL;
            toad->toadStick = NULL;
        }
        
        SDL_RenderClear(screen->renderer);

        drawSpriteMap(worldMap, screen->renderer);
        
        drawEntity(lilypad->entity, screen->renderer);
        drawEntity(toad->entity, screen->renderer);
        
        drawText(nut, screen->renderer);

        SDL_RenderPresent(screen->renderer);

        frameCount++;

        currentTime = SDL_GetTicks();
        if (currentTime - lastFrame < MILLISECONDS_PER_FRAME)
            SDL_Delay(MILLISECONDS_PER_FRAME - (currentTime - lastFrame));
        
        lastFrame = currentTime;
        if (currentTime - lastPrint >= 1000)
        {
            SDL_Log("FPS: %u\n", frameCount);
            frameCount = 0;
            lastPrint = currentTime;
        }

        lastFrame = currentTime;
    }

cleanup:
    destroyText(nut);
    cleanup(screen, toad);
    destroySpriteMap(worldMap);
    destroyLilypad(lilypad);

    argv[argc - 1][0] = 0; // Does nothing except cheekily remove warnings
    return 0;
}
