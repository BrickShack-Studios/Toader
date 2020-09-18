#include <stdlib.h>

#include "animation.h"
#include "animationmap.h"
#include "entities/lilypad.h"
#include "entity.h"
#include "tween.h"

Lilypad* newLilypad(SDL_Renderer* renderer)
{
    Lilypad* lilypad = malloc(sizeof(Lilypad));
    lilypad->entity = newEntity(16, 14, 1);
    lilypad->tween = newTween();

    lilypad->entity->aMap->animations[0] = newAnimation(renderer, "./res/sprites/entities/lilypad.png", 2, 16, 16, 750);

    return lilypad;
}

void tickLilypad(Lilypad* lilypad)
{
    if (lilypad->tween->isActive)
    {
        tickTween(lilypad->tween);
    }
    else
    {
        lilypad->entity->position->x = -16;
        lilypad->entity->position->y = 32 + (rand() % 6) * 16;
        initTween(lilypad->tween, &lilypad->entity->position->x, 5000, lilypad->entity->position->x, 16 * 16);
    }
    
    return;
}

void destroyLilypad(Lilypad* lilypad)
{
    if (!lilypad)
        return;

    if (lilypad->entity)
    {
        destroyEntity(lilypad->entity);
        lilypad->entity = NULL;
    }

    if (lilypad->tween)
    {
        destroyTween(lilypad->tween);
        lilypad->tween = NULL;
    }

    free(lilypad);
    return;
}
