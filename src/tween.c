#include <stdlib.h>
#include <stdbool.h>

#include "tween.h"

Tween* newTween()
{
    Tween* tween = calloc(1, sizeof(Tween));
    return tween;
}

void initTween(Tween *tween, int *value, clock_t duration, int startValue, int endValue)
{
    tween->value = value;
    tween->startTime = clock();
    tween->endTime = tween->startTime + duration;
    tween->startValue = startValue;
    tween->endValue = endValue;
    tween->isActive = true;
    return;
}

int lerp(double x, int a, int b)
{
    return ((1.0 - x) * a) + (x * b);
}

bool tickTween(Tween *tween)
{
    if (!tween->isActive)
        return false;

    clock_t time = clock();
    if (time >= tween->endTime)
    {
        *(tween->value) = tween->endValue;
        tween->isActive = false;
        return false;
    }

    *(tween->value) = lerp((double) (time - tween->startTime) / (tween->endTime - tween->startTime), tween->startValue, tween->endValue);
    return true;
}

void destroyTween(Tween *tween)
{
    free(tween);

    return;
}
