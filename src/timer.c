#include "master.h"

float time_delta;
long long last_ms;

/**
* Setup Timers. Setup SDL Timers for game use.
*/
void SetupTimers()
{
    time_delta = 0.0f;
    last_ms = SDL_GetTicks();
}

/**
* Update Timers. Update SDL timers every frame.
*/
void UpdateTimers()
{
    /* Free the spare CPU cycles. */
    sleep(0);

    /* Find the frame time delta. */
    time_delta = 0;
    if(SDL_GetTicks() > last_ms)
    {
        time_delta = SDL_GetTicks() - last_ms;
        last_ms = SDL_GetTicks();
    }
}
