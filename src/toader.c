#include <stdlib.h>

#include <SDL2/SDL.h>

#include "animation.h"
#include "animationmap.h"
#include "screen.h"
#include "sprite.h"
#include "toader.h"

Toad* newToad(Screen* screen)
{
    // calloc() zeroes everything out, initializing it all for us
    Toad* toad = calloc(1, sizeof(Toad));
    toad->rect = calloc(1, sizeof(SDL_Rect));
    toad->tween = newTween();

    toad->rect->h = 16;
    toad->rect->w = 16;
    addToaderAnimation(screen, toad);
    return toad;
}

void destroyToad(Toad* toad)
{
    if (toad->animationMap)
        destroyAnimationMap(toad->animationMap);
    if (toad->tween)
        destroyTween(toad->tween);

    toad->animationMap = NULL;
    toad->tween = NULL;
    free(toad);
    return;
}

void addToaderAnimation(Screen* screen, Toad* toad)
{
    toad->animationMap = newAnimationMap(4);
    toad->animationMap->animations[0] = newAnimation(screen, "./res/sprites/toader/toaderUpAnimation.PNG\0", 2, 16, 16, 250);
    toad->animationMap->animations[1] = newAnimation(screen, "./res/sprites/toader/toaderDownAnimation.PNG\0", 2, 16, 16, 250);
    toad->animationMap->animations[2] = newAnimation(screen, "./res/sprites/toader/toaderLeftAnimation.PNG\0", 2, 16, 16, 250);
    toad->animationMap->animations[3] = newAnimation(screen, "./res/sprites/toader/toaderRightAnimation.PNG\0", 2, 16, 16, 250);
    return;
}
