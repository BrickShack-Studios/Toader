#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "screen.h"
#include "sprite.h"

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer)
{
    SDL_Texture* texture = NULL;

    SDL_Surface* surface = IMG_Load(path);
    if (!surface)
    {
        SDL_Log("Error loading %s. Error: %s\n", path, IMG_GetError());
        goto end;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        SDL_Log("Error creating texture from %s. Error: %s\n", path, SDL_GetError());
        goto end;
    }

end:

    if (surface)
        SDL_FreeSurface(surface);

    return texture;
}

Sprite* newSprite(const char* path, SDL_Renderer* renderer)
{
    Sprite* sprite = calloc(1, sizeof(Sprite));

    sprite->texture = loadTexture(path, renderer);
    sprite->rect = calloc(1, sizeof(SDL_Rect));

    SDL_QueryTexture(sprite->texture, NULL, NULL, &sprite->rect->w, &sprite->rect->h);

    return sprite;
}

void drawSprite(Sprite* sprite, SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, sprite->texture, NULL, sprite->rect);
    return;
}

void destroySprite(Sprite* sprite)
{
    if (sprite->texture)
    {
        SDL_DestroyTexture(sprite->texture);
        sprite->texture = NULL;
    }

    if (sprite->rect)
    {
        free(sprite->rect);
        sprite->rect = NULL;
    }

    free(sprite);
    return;
}
