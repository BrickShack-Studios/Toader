#include <stdlib.h>

#include "animation.h"

Animation* newAnimation(SDL_Renderer* renderer, const char* spriteFilePath, int frames, int height, int width, unsigned int duration)
{
    Animation* animation = calloc(1, sizeof(Animation));
    animation->currentFrame = calloc(1, sizeof(SDL_Rect));
    animation->position = calloc(1, sizeof(SDL_Rect));

    animation->currentFrame->h = height;
    animation->currentFrame->w = width;

    animation->position->h = height;
    animation->position->w = width;

    animation->duration = duration;
    animation->frameCount = frames;
    animation->frame = 0;
    animation->strip = newSprite(spriteFilePath, renderer);
    animation->tween = newTween();
    
    return animation;
}

void drawAnimation(Animation* animation, SDL_Renderer* renderer)
{
    if (!tickTween(animation->tween))
        animation->frame = 0;

    animation->currentFrame->x = animation->currentFrame->w * animation->frame;
    SDL_RenderCopy(renderer, animation->strip->texture, animation->currentFrame, animation->position);
    return;
}

void playAnimation(Animation* animation)
{
    initTween(animation->tween, &animation->frame, animation->duration, 0, animation->frameCount);
    return;
}

void destroyAnimation(Animation* animation)
{
    if (animation->strip)
        destroySprite(animation->strip);
    if (animation->tween)
        destroyTween(animation->tween);
    if (animation->currentFrame)
        free(animation->currentFrame);
    if (animation->position)
        free(animation->position);

    free(animation);
    return;
}
