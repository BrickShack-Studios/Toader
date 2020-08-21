#include <stdlib.h>

#include <SDL2/SDL.h>

#include "toader.h"

Toad* newToad()
{
    // calloc() zeroes everything out, initializing it all for us
    Toad* toad = calloc(1, sizeof(Toad));
    return toad;
}
