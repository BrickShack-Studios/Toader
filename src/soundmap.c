#include "soundmap.h"

#include <stdio.h>

SoundMap* newSoundMap(int numSounds)
{
    SoundMap* soundMap = calloc(1, sizeof(SoundMap*));
    soundMap->sounds = calloc(numSounds, sizeof(Mix_Chunk*));
    soundMap->numSounds = numSounds;
}

void destroySoundMap(SoundMap* soundMap)
{
    while (soundMap->numSounds)
        Mix_FreeChunk(soundMap->sounds[--soundMap->numSounds]);
    free(soundMap);
    return;
}
