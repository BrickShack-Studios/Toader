#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "entity.h"
#include "sprite.h"

Entity* newEntity(char* path, SDL_Renderer* renderer, unsigned int hitboxW, unsigned int hitboxH)
{
    Entity* entity = calloc(1, sizeof(Entity));
    entity->hitbox = calloc(1, sizeof(Collider));
    
    entity->sprite = newSprite(path, renderer);
    entity->rect = entity->sprite->rect;
    
    entity->hitbox->w = hitboxW;
    entity->hitbox->h = hitboxH;

    centerHitbox(entity);

    return entity;
}

void centerHitbox(Entity* entity)
{
    entity->hitbox->x = entity->rect->x + entity->rect->w / 4;
    entity->hitbox->y = entity->rect->y + entity->rect->h / 4;

    return;
}

bool isColliding(Collider* c1, Collider* c2)
{
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
    drawSprite(entity->sprite, renderer);

    return;
}

void destroyEntity(Entity* entity)
{
    if (entity->sprite)
    {
        destroySprite(entity->sprite);
        entity->sprite = NULL;

        // The rect isn't allocated: it's just tied to the sprite's rect.
        // Therefore, we don't need to free it, and it'll be destroyed
        // with the sprite
        entity->rect = NULL;
    }

    if (entity->hitbox)
    {
        free(entity->hitbox);
        entity->hitbox = NULL;
    }

    free(entity);
    return;
}