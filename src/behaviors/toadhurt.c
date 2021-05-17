#include "entity.h"
#include "toader.h"
#include "behaviors/toadhurt.h"

ToadHurt* newToadHurt(Toad* toad)
{
    ToadHurt* toadHurt = malloc(sizeof(ToadHurt));
    toadHurt->toad = toad;

    return toadHurt;
}

void tickToadHurt(ToadHurt* th)
{
    th->toad->entity->position->x = 0;
    th->toad->entity->position->y = 0;
    th->toad->lives -= 1;
    return;
}

void destroyToadHurt(ToadHurt* th)
{
    if (!th)
        return;
    
    if (th->toad)
    {
        destroyToad(th->toad);
        th->toad = NULL;
    }
    free(th);
}