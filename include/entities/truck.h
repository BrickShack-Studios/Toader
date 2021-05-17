#ifndef TRUCK_H
#define TRUCK_H

#include <SDL2/SDL.h>

#include "entity.h"
#include "tween.h"

typedef struct Truck
{
    Entity* entity;
    Tween* tween;
} Truck;

/**
   Allocates a new Truck struct using the renderer provided by the Screen.
 */
Truck* newTruck(SDL_Renderer* renderer);

/**
   Performs a tween of the given Truck and centers its hitbox.
*/
void tickTruck(Truck* truck);

/**
   Frees all memory taken up by the Truck struct and its members.
 */
void destroyTruck(Truck* truck);

#endif