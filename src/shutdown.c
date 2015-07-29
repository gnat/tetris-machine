#include "master.h"

/**
* Shutdown. Close SDL and other API's. Free any allocated heap.
*/
void Shutdown()
{
    /* Free texture data. */
    int i;
    for(i = 0; i < TEXTURE_COUNT; i++)
        free(textures[i]);
        
    /* glDeleteTextures( 1, &texture ); */ /* Not really needed in this case. OGL deletes its own stuff */  

    /* Free audio data.*/
    for(i = 0; i < SOUND_COUNT; i++)
        FMOD_Sound_Release(sounds[i]);

    /* Close APIs */
    FMOD_System_Close(fmod_system);
    FMOD_System_Release(fmod_system);
    SDL_Quit();
}
