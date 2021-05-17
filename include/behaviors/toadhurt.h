#ifndef TOAD_HURT
#define TOAD_HURT

#include <stdbool.h>

#include "entity.h"
#include "toader.h"

typedef struct ToadHurt
{
    struct Toad* toad;
} ToadHurt;

/**
   Allocates a new Toad Hurt struct using the renderer provided by the Screen.
 */
ToadHurt* newToadHurt(Toad* toad);

/**
   Removes a life from the toad and resets its position.
*/
void tickToadHurt(ToadHurt* th);

/**
   Frees all memory taken up by the Toad Hurt struct and its members.
 */
void destroyToadHurt(ToadHurt* th);

#endif
