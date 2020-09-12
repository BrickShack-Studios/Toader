#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "entity.h"
#include "animationmap.h"

Entity* newEntity(unsigned int hitboxW, unsigned int hitboxH, unsigned int numAnimations)
{
    Entity* entity = calloc(1, sizeof(Entity));
    entity->hitbox = calloc(1, sizeof(Collider));
    
    entity->aMap = newAnimationMap(numAnimations);
    entity->position = entity->aMap->position;
    
    entity->hitbox->w = hitboxW;
    entity->hitbox->h = hitboxH;

    centerHitbox(entity);

    return entity;
}

void centerHitbox(Entity* entity)
{
    entity->hitbox->x = entity->position->x + entity->position->w / 4;
    entity->hitbox->y = entity->position->y + entity->position->h / 4;

    return;
}

bool isColliding(Entity* e1, Entity* e2)
{
    centerHitbox(e1);
    centerHitbox(e2);

    Collider* c1 = e1->hitbox;
    Collider* c2 = e2->hitbox;
    
    int c1LeftSide = c1->x;
    int c2LeftSide = c2->x;

    int c1RightSide = c1LeftSide + c1->w;
    int c2RightSide = c2LeftSide + c2->w;

    int c1TopSide = c1->y;
    int c2TopSide = c2->y;

    int c1BottomSide = c1TopSide + c1->h;
    int c2BottomSide = c2TopSide + c2->h;

    if (c1LeftSide >= c2RightSide)
        return false;
    if (c1RightSide <= c2LeftSide)
        return false;
    if (c1BottomSide <= c2TopSide)
        return false;
    if (c1TopSide >= c2BottomSide)
        return false;

    return true;
}

void drawEntity(Entity* entity, SDL_Renderer* renderer)
{
    drawAnimationMap(entity->aMap, renderer);

    return;
}

void destroyEntity(Entity* entity)
{
    if (entity->aMap)
    {
        destroyAnimationMap(entity->aMap);
        entity->aMap = NULL;

        // The position isn't allocated: it's just tied to the animation map's position.
        // Therefore, we don't need to free it, and it'll be destroyed
        // with the animation map.
        entity->position = NULL;
    }

    if (entity->hitbox)
    {
        free(entity->hitbox);
        entity->hitbox = NULL;
    }

    free(entity);
    return;
}
