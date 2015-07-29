#include "master.h"
#include "fmod.h"

FMOD_SYSTEM *fmod_system;
FMOD_CHANNEL *fmod_channel = 0;

/**
* Helper for FMOD error checking.
*/
void FMODErrorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

/**
* SetupSound. Sets up FMOD.
*/
void SetupSound()
{
    FMOD_RESULT result;
    unsigned int version = 0;

    result = FMOD_System_Create(&fmod_system);
    FMODErrorCheck(result);

    result = FMOD_System_GetVersion(fmod_system, &version);
    FMODErrorCheck(result);

    if (version < FMOD_VERSION)
    {
        printf("Error: You are using the wrong library version!  You should be using FMOD %.02f\n", FMOD_VERSION);
        exit(-1);
    }

    result = FMOD_System_Init(fmod_system, 32, FMOD_INIT_NORMAL, NULL);
    FMODErrorCheck(result);
}

/**
* PlaySound. Call FMOD to play specified sound.
*/
void PlaySound(FMOD_SOUND* sound)
{
    FMOD_System_PlaySound(fmod_system, FMOD_CHANNEL_FREE, sound, 0, &fmod_channel);
} 

/**
* MuteAllSound. Stop sounds all at once.
*/
void MuteAllSound()
{
    //FSOUND_StopSound(FSOUND_ALL);
} 
