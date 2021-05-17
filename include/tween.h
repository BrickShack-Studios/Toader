#ifndef TWEEN_H
#define TWEEN_H

#include <stdbool.h>

#include <SDL2/SDL.h>

typedef struct Tween
{
  int* value;
  unsigned int startTime;
  unsigned int endTime;
  int startValue;
  int endValue;
  bool isActive;
} Tween;

/**
   Allocates a new Tween struct.
*/

Tween* newTween();

/**
   Initializes a passed Tween struct with the parameters provided.
*/

void initTween(Tween *tween, int* value, unsigned int duration, int startValue, int endValue);

/**
   Determines if a tween is still in progress. If it is, it performs a little step of the tween based on how much time remains.
   \note This currently uses linear interpolation only, but that can change in the future as we add more interpolations.
   \return true if still in progress, false otherwise.
*/

bool tickTween(Tween *tween);

/**
   Determines how far along x is in a given linear interpolation.
*/

int lerp(double x, int a, int b);

/**
   Frees all memory taken up by a Tween struct and its members.
*/

void destroyTween(Tween *tween);

#endif
