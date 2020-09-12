#include <stdlib.h>

#include <SDL2/SDL.h>

#include "animation.h"
#include "animationmap.h"
#include "entity.h"
#include "screen.h"
#include "sprite.h"
#include "toader.h"

Toad* newToad(SDL_Renderer* renderer)
{
    // calloc() zeroes everything out, initializing it all for us
    Toad* toad = calloc(1, sizeof(Toad));
    
    toad->entity = newEntity(5, 5, 4);
    toad->tween = newTween();
    toad->soundMap = newSoundMap(4);

    addToaderSound(toad);
    addToaderAnimation(toad, renderer);
    
    return toad;
}

void addToaderAnimation(Toad* toad, SDL_Renderer* renderer)
{
    toad->entity->aMap->animations[0] = newAnimation(renderer, "./res/sprites/toader/toaderUpAnimation.png", 2, 16, 16, 200);
    toad->entity->aMap->animations[1] = newAnimation(renderer, "./res/sprites/toader/toaderDownAnimation.png", 2, 16, 16, 200);
    toad->entity->aMap->animations[2] = newAnimation(renderer, "./res/sprites/toader/toaderLeftAnimation.png", 2, 16, 16, 200);
    toad->entity->aMap->animations[3] = newAnimation(renderer, "./res/sprites/toader/toaderRightAnimation.png", 2, 16, 16, 200);
    
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

void destroyToad(Toad* toad)
{
    if (toad->tween)
        destroyTween(toad->tween);
    if (toad->soundMap)
        destroySoundMap(toad->soundMap);
    if (toad->entity)
        destroyEntity(toad->entity);

    toad->entity = NULL;
    toad->soundMap = NULL;
    toad->tween = NULL;
    
    free(toad);
    return;
}
