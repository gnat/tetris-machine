#include "master.h"

/**
* Call the Logic function of the current Screen.
*/
void Logic()
{
    switch(screen_current)
    {
        case SCREEN_GAMEPLAY:
            ScreenGameplayLogic();
        break;
    }
} 
