#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "screen.h"

typedef struct Sprite
{
    SDL_Texture* texture;
    SDL_Rect* rect;
} Sprite;

/**
   Given a path to an image file and a screen to obtain a renderer from, loads
the image into an SDL_Texture* from disk.

   \note The image must be a PNG due to flags set with the SDL_image library
 */
SDL_Texture* loadTexture(const char* path, Screen* screen);

/**
   Allocates all memory required to load a Sprite* from a path to an image, and
then loads it
 */
Sprite* newSprite(const char* path, Screen* screen);

/**
   A convenience function which handles drawing a Sprite at its location
with its size
 */
void drawSprite(Sprite* sprite, SDL_Renderer* renderer);

/**
   Frees all memory used by a Sprite struct
 */
void destroySprite(Sprite* sprite);

#endif
