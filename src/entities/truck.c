#include <stdlib.h>

#include "animation.h"
#include "animationmap.h"
#include "entity.h"
#include "tween.h"

#include "entities/truck.h"

Truck* newTruck(SDL_Renderer* renderer) {
    Truck* truck = malloc(sizeof(Truck));

    truck->entity = newEntity(16, 16, 1);
    truck->tween = newTween();

    truck->entity->aMap->animations[0] = newAnimation(renderer, "./res/sprites/entities/truck.png", 1, 16, 16, 300);
    
    return truck;
}

void tickTruck(Truck* truck) {
    if (truck->tween->isActive)
    {
        tickTween(truck->tween);
    }
    else 
    {
        truck->entity->position->x = 0;
        truck->entity->position->y = 16;
        initTween(truck->tween, &truck->entity->position->x, 3000, truck->entity->position->x, 16 * 16);
    }

    centerHitbox(truck->entity);
    return;
}

void destroyTruck(Truck* truck) {
    if (!truck) 
        return;

    if (truck->entity) {
        destroyEntity(truck->entity);
        truck->entity = NULL;
    }

    if (truck->tween) {
        destroyTween(truck->tween);
        truck->tween = NULL;
    }

    free(truck);
    return;
}
