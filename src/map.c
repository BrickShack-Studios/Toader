#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "map.h"
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
    SpriteMap* map = malloc(sizeof(SpriteMap));
    map->tile = malloc(height * sizeof(Sprite**));

    int i;
    for (i = 0; i < height; i++)
	map->tile[i] = calloc(width, sizeof(Sprite*));

    map->width = width;
    map->height = height;
    map->tileWidth = tileWidth;
    map->tileHeight = tileHeight;

    return map;
}

Sprite* charToSprite(char c, Screen* screen)
{
    switch (c)
    {
        case 'g':
	    return newSprite("./res/sprites/bg/grass_middle.png", screen);
	    break;
        case 's':
	    return newSprite("./res/sprites/bg/sidewalk.png", screen);
	    break;
        case ' ':
	    return NULL;
	    break;
        default:
	    printf("Error: Unknown sprite character code '%c'\n", c);
    }

    return NULL;
}

SpriteMap* newSpriteMapFromArray(const char** arr, int arrWidth, int arrHeight, int tileWidth, int tileHeight, Screen* screen)
{
    SpriteMap* map = newSpriteMap(arrWidth, arrHeight, tileWidth, tileHeight);

    int x, y;
    for (y = 0; y < arrHeight; y++)
	for (x = 0; x < arrWidth; x++)
	{	    
	    map->tile[y][x] = charToSprite(arr[y][x], screen);
	    if (map->tile[y][x])
	    {
		map->tile[y][x]->rect->w = tileWidth;
		map->tile[y][x]->rect->h = tileHeight;
		map->tile[y][x]->rect->x = x * tileWidth;
		map->tile[y][x]->rect->y = y * tileHeight;
	    }
	}

    return map;
}

SpriteMap* createWorldMap(Screen* screen)
{
    SpriteMap* map = newSpriteMapFromArray(WORLD, 14, 15, 16, 16, screen);
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
