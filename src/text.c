#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "text.h"
#include "sprite.h"

Text* newText(SDL_Renderer* renderer, char* str, int x, int y)
{
    Text* text = calloc(1, sizeof(Text));
    text->rect = calloc(1, sizeof(SDL_Rect));

    int w = strlen(str) * 8;
    int h = 8;

    text->rect->x = x;
    text->rect->y = y;
    text->rect->w = w;
    text->rect->h = h;

    text->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    if (!text->texture)
        SDL_Log("Error creating text texture: %s\n", SDL_GetError());

    text->str = str;

    SDL_SetRenderTarget(renderer, text->texture);
    SDL_RenderClear(renderer);

    SDL_Texture* charMap = loadTexture("./res/sprites/chars/characters.PNG", renderer);
    if (!charMap)
        SDL_Log("Error retrieving character sprite: %s\n", SDL_GetError());

    SDL_Rect* src = calloc(1, sizeof(SDL_Rect));
    SDL_Rect* dst = calloc(1, sizeof(SDL_Rect));

    dst->h = 8;
    dst->w = 8;

    src->h = 8;
    src->w = 8;

    dst->y = 0;
    src->y = 0;

    size_t i;
    for (i = 0; i < strlen(text->str); i++)
    {
        if (text->str[i] - '0' <= 9)
            src->x = 8 * (text->str[i] - '0');
        else
            src->x = 8 * (10 + (text->str[i] - 'a'));

        dst->x = i * 8;
        SDL_RenderCopy(renderer, charMap, src, dst);
    }

    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    SDL_DestroyTexture(charMap);
    free(src);
    free(dst);

    return text;
}

void drawText(Text* text, SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, text->texture, NULL, text->rect);
    return;
}

void destroyText(Text* text)
{
    if (text->rect)
        free(text->rect);
    if (text->texture)
        SDL_DestroyTexture(text->texture);
    //if (text->str)
    //    free(text->str);

    free(text);
    return;
}
