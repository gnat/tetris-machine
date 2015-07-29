#include "master.h"

/* Input capping, so input actions wont activate more then 1 time per keypress. */
bool cap_move_left;
bool cap_move_right;
bool cap_flip_brick;
bool cap_move_left_wasd;
bool cap_move_right_wasd;
bool cap_flip_brick_wasd;

/**
* Input. Detect any user events.
*/
void Input()
{
    /* Reset all "one press, one action" keyboard input variables. */
    move_left = false;
    move_right = false;
    flip_brick = false;
    
    SDL_PollEvent(&event); /* Check input for this frame. */

    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                running = false;
            break;
            
            /* Arrow keys. */
            case SDLK_LEFT:
                if(!cap_move_left)
                    move_left = true;
                cap_move_left = true;
            break; 
            
            case SDLK_RIGHT:
                if(!cap_move_right)
                    move_right = true;
                cap_move_right = true;
            break;
            
            case SDLK_UP:
                if(!cap_flip_brick)
                    flip_brick = true;
                cap_flip_brick = true;
            break;
            
            case SDLK_DOWN:
                /* No capping for move down as this key can be held down. */
                move_down = true;
            break;
            
            /* WASD keys. */
            case SDLK_a:
                if(!cap_move_left_wasd)
                    move_left = true;
                cap_move_left_wasd = true;
            break; 
            
            case SDLK_d:
                if(!cap_move_right_wasd)
                    move_right = true;
                cap_move_right_wasd = true;
            break;
            
            case SDLK_w:
                if(!cap_flip_brick_wasd)
                    flip_brick = true;
                cap_flip_brick_wasd = true;
            break;
            
            case SDLK_s:
                /* No capping for move down as this key can be held down. */
                move_down = true;
            break;
        }
    }

    if(event.type == SDL_KEYUP)
    {
        switch(event.key.keysym.sym)
        {
            /* Arrow Key Style */
            case SDLK_LEFT:
                cap_move_left = false;
            break; 
            
            case SDLK_RIGHT:
                cap_move_right = false;
            break;
            
            case SDLK_UP:
                cap_flip_brick = false;
            break;
            
            case SDLK_DOWN:
                move_down = false;
            break;
            
            /* WASD Style */
            case SDLK_a:
                cap_move_left_wasd = false;
            break; 
            
            case SDLK_d:
                cap_move_right_wasd = false;
            break;
            
            case SDLK_w:
                cap_flip_brick_wasd = false;
            break;
            
            case SDLK_s:
                move_down = false;
            break;
        }
    }

    if(event.type == SDL_QUIT)
        running = false;
}
