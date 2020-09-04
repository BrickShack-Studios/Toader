#ifndef SOUNDMAP_H
#define SOUNDMAP_H

#include <SDL2/SDL_mixer.h>

typedef struct SoundMap
{
    Mix_Chunk** sounds;
    int numSounds;
} SoundMap;

/**
   Allocates a new SoundMap with a provided amount of sounds
*/

SoundMap* newSoundMap(int numSounds);

/**
   Frees all memory taken by a SoundMap struct and its members
*/

void destroySoundMap(SoundMap* soundMap);

#endif
