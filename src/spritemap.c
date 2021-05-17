#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "spritemap.h"
#include "sprite.h"
#include "screen.h"

const char* WORLD[15] =
{
    "gggggggggggggg",
    "g g g g g g g ",
    "              ",
    "              ",
    "              ",
    "              ",
    "              ",
    "              ",
    "ssssssssssssss",
    "              ",
    "              ",
    "              ",
    "              ",
    "              ",
    "ssssssssssssss"
};

SpriteMap* newSpriteMap(int width, int height, int tileWidth, int tileHeight)
{
    SpriteMap* spriteMap = malloc(sizeof(SpriteMap));
    spriteMap->tile = malloc(height * sizeof(Sprite**));

    int i;
    for (i = 0; i < height; i++)
	spriteMap->tile[i] = calloc(width, sizeof(Sprite*));

    spriteMap->width = width;
    spriteMap->height = height;
    spriteMap->tileWidth = tileWidth;
    spriteMap->tileHeight = tileHeight;

    return spriteMap;
}

Sprite* charToSprite(char c, SDL_Renderer* renderer)
{
    switch (c)
    {
        case 'g':
            return newSprite("./res/sprites/bg/grass_middle.png", renderer);
            break;
        case 's':
            return newSprite("./res/sprites/bg/sidewalk.png", renderer);
            break;
        case ' ':
            return NULL;
            break;
        default:
            SDL_Log("Error: Unknown sprite character code '%c'\n", c);
    }

    return NULL;
}

SpriteMap* newSpriteMapFromArray(const char** arr, int arrWidth, int arrHeight, int tileWidth, int tileHeight, SDL_Renderer* renderer)
{
    SpriteMap* spriteMap = newSpriteMap(arrWidth, arrHeight, tileWidth, tileHeight);
    spriteMap->charTile = arr;

    int x, y;
    for (y = 0; y < arrHeight; y++) 
    {
        for (x = 0; x < arrWidth; x++)
        { 
            spriteMap->tile[y][x] = charToSprite(arr[y][x], renderer);
            if (spriteMap->tile[y][x])
            {
                spriteMap->tile[y][x]->rect->w = tileWidth;
                spriteMap->tile[y][x]->rect->h = tileHeight;
                spriteMap->tile[y][x]->rect->x = x * tileWidth;
                spriteMap->tile[y][x]->rect->y = y * tileHeight;
            }
        }
    }

    return spriteMap;
}

SpriteMap* createWorldMap(SDL_Renderer* renderer)
{
    SpriteMap* map = newSpriteMapFromArray(WORLD, 14, 15, 16, 16, renderer);
    return map;
}

void drawSpriteMap(SpriteMap* map, SDL_Renderer* renderer)
{
    int x, y;
    for (y = 0; y < map->height; y++)
        for (x = 0; x < map->width; x++)
            if (map->tile[y][x])
                drawSprite(map->tile[y][x], renderer);

    return;
}

void destroySpriteMap(SpriteMap* map)
{
    int x, y;
    for (y = 0; y < map->height; y++)
    {
        for (x = 0; x < map->width; x++)
            if (map->tile[y][x])
                destroySprite(map->tile[y][x]);

        free(map->tile[y]);
    }

    free(map->tile);
    free(map);

    return;
}
