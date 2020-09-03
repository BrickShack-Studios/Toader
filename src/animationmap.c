#include "animationmap.h"
#include "animation.h"

AnimationMap* newAnimationMap(int numAnimations)
{
    AnimationMap* animationMap = calloc(1, sizeof(AnimationMap));
    animationMap->animations = calloc(numAnimations, sizeof(Animation*));
    animationMap->numAnimations = numAnimations;
    return animationMap;
}

void setAnimation(AnimationMap* animationMap, int animation)
{
    animationMap->currentAnimation = animation;
    playAnimation(animationMap->animations[animation]);
    return;
}

void drawAnimationMap(AnimationMap* animationMap, SDL_Renderer* renderer, SDL_Rect* rect)
{
    drawAnimation(animationMap->animations[animationMap->currentAnimation], renderer, rect);
    return;
}

void destroyAnimationMap(AnimationMap* animationMap)
{
    if (animationMap->animations)
        while (animationMap->numAnimations)
            destroyAnimation(animationMap->animations[--animationMap->numAnimations]);

    free(animationMap->animations);
    free(animationMap);
    return;
}
