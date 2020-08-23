#include <stdlib.h>

#include <SDL2/SDL.h>

#include "toader.h"
#include "sprite.h"
#include "screen.h"

Toad* newToad(Screen* screen)
{
    // calloc() zeroes everything out, initializing it all for us
    Toad* toad = calloc(1, sizeof(Toad));
    toad->sprite = newSprite("./res/sprites/toader/toader.png", screen);

    toad->sprite->rect->w = 16;
    toad->sprite->rect->h = 16;
    
    return toad;
}

void destroyToad(Toad* toad)
{
    if (toad->sprite)
    {
	destroySprite(toad->sprite);
	toad->sprite = NULL;
    }

    free(toad);
    return;
}
