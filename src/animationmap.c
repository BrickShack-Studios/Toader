#include <stdio.h>

#include "animationmap.h"
#include "animation.h"

/*
  Something that might be interesting to try in the future would be to make the AnimationMap go in
and free each Animation's position rect, and replace it with a pointer to the AnimationMap's position rect.
This would remove the ability to have animations with different sizes, but is that really necessary?

Consider that one potential experiment.
 */

AnimationMap* newAnimationMap(unsigned int numAnimations)
{
    AnimationMap* animationMap = calloc(1, sizeof(AnimationMap));
    
    animationMap->animations = calloc(numAnimations, sizeof(Animation*));
    animationMap->position = calloc(1, sizeof(SDL_Rect));
    
    animationMap->numAnimations = numAnimations;
    
    return animationMap;
}

void setAnimation(AnimationMap* animationMap, unsigned int animation)
{
    animationMap->currentAnimation = animation;
    
    animationMap->position->w = animationMap->animations[animation]->position->w;
    animationMap->position->h = animationMap->animations[animation]->position->h;
    
    playAnimation(animationMap->animations[animation]);
    return;
}

void drawAnimationMap(AnimationMap* animationMap, SDL_Renderer* renderer)
{
    animationMap->animations[animationMap->currentAnimation]->position->x = animationMap->position->x;
    animationMap->animations[animationMap->currentAnimation]->position->y = animationMap->position->y;
    
    drawAnimation(animationMap->animations[animationMap->currentAnimation], renderer);
    return;
}

void destroyAnimationMap(AnimationMap* animationMap)
{
    if (animationMap->animations)
    {
        while (animationMap->numAnimations)
            destroyAnimation(animationMap->animations[--animationMap->numAnimations]);

        free(animationMap->animations);
    }
        

    if (animationMap->position)
        free(animationMap->position);

    
    free(animationMap);
    return;
}
