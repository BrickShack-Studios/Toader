#include "entity.h"
#include "toader.h"
#include "behaviors/toadstick.h"

ToadStick* newToadStick(int x, int y, int w, int h)
{
    ToadStick* ts = malloc(sizeof(ToadStick));
    ts->hitbox = malloc(sizeof(Collider));
    ts->lastPosition = malloc(sizeof(Collider));
    
    ts->hitbox->x = x;
    ts->hitbox->y = y;
    ts->hitbox->w = w;
    ts->hitbox->h = h;

    ts->toad = NULL;
    ts->latched = false;

    return ts;
}

void tickToadStick(ToadStick* ts)
{
    if (!ts->toad)
        return;
    
    if (ts->toad->tween->isActive)
    {
        ts->latched = false;
        return;
    }

    int centeredX = ts->hitbox->x + ts->hitbox->w / 2;
    int centeredY = ts->hitbox->y + ts->hitbox->h / 2;
    
    if (!ts->latched)
    {
        ts->latched = true;
        ts->lastPosition->x = centeredX;
        ts->lastPosition->y = centeredY;
    }

    ts->toad->entity->position->x += centeredX - ts->lastPosition->x;
    ts->toad->entity->position->y += centeredY - ts->lastPosition->y;

    ts->lastPosition->x = centeredX;
    ts->lastPosition->y = centeredY;

    return;
}

void destroyToadStick(ToadStick* ts)
{
    if (!ts)
        return;

    if (ts->hitbox)
    {
        free(ts->hitbox);
        ts->hitbox = NULL;
    }

    if (ts->lastPosition)
    {
        free(ts->lastPosition);
        ts->lastPosition = NULL;
    }

    free(ts);
    return;
}
