#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>

#include "sprite.h"

extern const char* WORLD[15];

typedef struct SpriteMap
{
    Sprite*** tile;
    int height;
    int width;
    int tileHeight;
    int tileWidth;
} SpriteMap;

/**
   Creates an empty SpriteMap* that can hold `width x height` `Sprite*`s, each having size
`tileWidth * tileHeight`

   \note Not every position in the SpriteMap needs to be filled. Null values are to be
         expected and need to be accounted for. You'll notice that many functions which
         operate on SpriteMaps are careful to account for potential null values.
 */
SpriteMap* newSpriteMap(int width, int height, int tileWidth, int tileHeight);

/**
   Creates a new SpriteMap* and fills it with sprites by parsing a 2D char array
 */
SpriteMap* newSpriteMapFromArray(const char** arr, int arrWidth, int arrHeight, int tileWidth, int tileHeight, Screen* screen);

/**
   Creates the gameplay area specifically
 */
SpriteMap* createWorldMap(Screen* screen);

/**
   Batch draws every sprite in the sprite map with one call
 */
void drawSpriteMap(SpriteMap* map, SDL_Renderer* renderer);

/**
   Frees all memory associated with the sprite map

   \warning This includes all `Sprite*`s
 */
void destroySpriteMap(SpriteMap* map);

#endif
