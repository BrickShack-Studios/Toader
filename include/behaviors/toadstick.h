#ifndef TOADSTICK_H
#define TOADSTICK_H

#include <stdbool.h>

#include "entity.h"
#include "toader.h"

typedef struct ToadStick
{
    struct Toad* toad;
    Collider* hitbox;
    Collider* lastPosition;
    bool latched;
} ToadStick;


/**
   Allocates a new Toad Stick struct using the parameters provided.
 */
ToadStick* newToadStick(int x, int y, int w, int h);

void tickToadStick(ToadStick* ts);

/**
   Frees all memory taken up by the Toad Stick struct and its members.
 */
void destroyToadStick(ToadStick* ts);

#endif
