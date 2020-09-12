#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "animationmap.h"

typedef SDL_Rect Collider;

typedef struct Entity
{
    AnimationMap* aMap;
    SDL_Rect* position;
    Collider* hitbox;
} Entity;

/**
   Allocates all memory needed for an entity.
   \note The Entity's position is a pointer equal to its animation map's position. Changing one's values
         changes the other. This also means freeing the position of an entity is unnecessary.
 */
Entity* newEntity(unsigned int hitboxW, unsigned int hitboxH, unsigned int numAnimations);

/**
   Adjusts an Entity's hitbox so that it is centered over the middle of the AnimationMap's frame.
 */
void centerHitbox(Entity* entity);

/**
   Checks if two entities' hitboxes are overlapping.
   \return True if there's overlap between hitboxes, false otherwise
 */
bool isColliding(Entity* e1, Entity* e2);

/**
   A wrapper function for the animation map's draw function.
 */
void drawEntity(Entity* entity, SDL_Renderer* renderer);

/**
   Frees all memory associated with an Entity.
 */
void destroyEntity(Entity* entity);
#endif
