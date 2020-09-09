#include <stdlib.h>

#include <SDL2/SDL.h>

#include "animation.h"
#include "animationmap.h"
#include "screen.h"
#include "sprite.h"
#include "toader.h"

Toad* newToad(SDL_Renderer* renderer)
{
    // calloc() zeroes everything out, initializing it all for us
    Toad* toad = calloc(1, sizeof(Toad));
    toad->rect = calloc(1, sizeof(SDL_Rect));
    toad->tween = newTween();
    toad->soundMap = newSoundMap(4);

    toad->rect->h = 16;
    toad->rect->w = 16;

    addToaderSound(toad);
    addToaderAnimation(renderer, toad);
    return toad;
}

void destroyToad(Toad* toad)
{
    if (toad->animationMap)
        destroyAnimationMap(toad->animationMap);
    if (toad->tween)
        destroyTween(toad->tween);
    if (toad->soundMap)
        destroySoundMap(toad->soundMap);

    toad->animationMap = NULL;
    toad->soundMap = NULL;
    toad->tween = NULL;
    free(toad);
    return;
}

void addToaderAnimation(SDL_Renderer* renderer, Toad* toad)
{
    toad->animationMap = newAnimationMap(4);
    toad->animationMap->animations[0] = newAnimation(renderer, "./res/sprites/toader/toaderUpAnimation.PNG\0", 2, 16, 16, 250);
    toad->animationMap->animations[1] = newAnimation(renderer, "./res/sprites/toader/toaderDownAnimation.PNG\0", 2, 16, 16, 250);
    toad->animationMap->animations[2] = newAnimation(renderer, "./res/sprites/toader/toaderLeftAnimation.PNG\0", 2, 16, 16, 250);
    toad->animationMap->animations[3] = newAnimation(renderer, "./res/sprites/toader/toaderRightAnimation.PNG\0", 2, 16, 16, 250);
    return;
}

void addToaderSound(Toad* toad)
{
    toad->soundMap->sounds[0] = Mix_LoadWAV("./res/sound/hop.wav");
    toad->soundMap->sounds[1] = Mix_LoadWAV("./res/sound/lifeup.wav");
    toad->soundMap->sounds[2] = Mix_LoadWAV("./res/sound/splat.wav");
    toad->soundMap->sounds[3] = Mix_LoadWAV("./res/sound/splash.wav");
    return;
}
