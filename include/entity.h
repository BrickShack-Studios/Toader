#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

#include "sprite.h"

typedef SDL_Rect Collider;

typedef struct Entity
{
    Sprite* sprite;
    SDL_Rect* rect;
    Collider* hitbox;
} Entity;

/**
   Creates a new entity from a sprite path.
 */
Entity* newEntity(char* path, SDL_Renderer* renderer, unsigned int hitboxW, unsigned int higboxH);

/**
   Adjusts an Entity's hitbox so that it is centered over the middle of the sprite.
 */
void centerHitbox(Entity* entity);

/**
   A wrapper function for the sprite's drawSprite() function.
 */
void drawEntity(Entity* entity, SDL_Renderer* renderer);

/**
   Frees all memory associated with an Entity.
 */
void destroyEntity(Entity* entity);
#endif
