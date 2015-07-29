#ifndef _MASTER_H_
#define _MASTER_H_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <SDL/SDL_image.h>
#include "fmod.h"
#include "fmod_errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>

#define DEBUG

/* Undefine SDL main so console output works. */
#ifdef DEBUG
    #ifdef main
    #undef main
    #endif
#endif

#include "game.h"
#include "init.h"
#include "dataload.h"
#include "shutdown.h"
#include "input.h"
#include "sound.h"
#include "logic.h"
#include "drawing.h"
#include "timer.h"
#include "screen_gameplay.h"

#endif
