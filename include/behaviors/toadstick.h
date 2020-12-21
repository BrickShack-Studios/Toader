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

ToadStick* newToadStick(int x, int y, int w, int h);

void tickToadStick(ToadStick* ts);

void destroyToadStick(ToadStick* ts);

#endif
