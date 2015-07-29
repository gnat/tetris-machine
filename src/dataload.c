#include "master.h"

TEXTURE* textures[TEXTURE_COUNT];
FMOD_SOUND *sounds[SOUND_COUNT];

/**
* LoadTexture. Loads texture image from file for use with SDL/OpenGL.
* @param Texture file name.
* @return Pointer to allocated TEXTURE.
*/
TEXTURE* LoadTexture(char *filename) 
{
    SDL_Surface* surface;
    GLuint textureid;
    int mode;

    surface = IMG_Load(filename);
    
    /* Or if you don't use SDL_image you can use SDL_LoadBMP here instead:
    surface = SDL_LoadBMP(filename); */

    /* Could not load image! */
    if (!surface) 
    {
        printf("Could not load image: %s", filename);
        return 0;
    }
    
    /* Work out what format to tell glTexImage2D to use... */
    if (surface->format->BytesPerPixel == 3) /* RGB 24bit */
    { 
        mode = GL_RGB;
    } 
    else if (surface->format->BytesPerPixel == 4) /* RGBA 32bit */
    { 
        mode = GL_RGBA;
    } 
    else 
    {
        printf("Could not determine pixel format of image: %s", filename);
        SDL_FreeSurface(surface);
        return 0;
    }

    /* Create one texture name. */
    glGenTextures(1, &textureid);

    /* Tell OpenGL to use the generated texture name */
    glBindTexture(GL_TEXTURE_2D, textureid);

    /* Read from the SDL surface and put it into an OpenGL texture. */
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

    /* Set up texture filters. */
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    /* Allocate memory for Texture structure and fill it up. */
    TEXTURE* texture = (TEXTURE*)malloc(sizeof(TEXTURE));
    
    /* Could not allocate memory. */
    if (!texture)
    {
        printf("Could not create TEXTURE struct for image: %s", filename);
        return 0;
    }
    
    /* Set up TEXTURE structure. */
    texture->width = surface->w;
    texture->height = surface->h;
    texture->id = textureid;
    
    /* Clean up. */
    SDL_FreeSurface(surface);
    
    /* Return pointer to image structure. */
    return texture;
}

/**
* LoadSound. Loads audio from file for use with FMOD.
* @param Audio file name.
* @return Pointer to allocated FMOD_SOUND.
*/
FMOD_SOUND* LoadSound(char *filename) 
{
    FMOD_SOUND* sound;
    FMOD_RESULT result;

    result = FMOD_System_CreateSound(fmod_system, filename, FMOD_CREATESAMPLE, 0, &sound); 
   
    FMODErrorCheck(result); /* Could not load sound? */
    
    return sound;
}

/**
* LoadData. Bulk loads all of our image and sound data.
*/
void LoadData()
{
    /* Load image textures. */
    textures[TEX_HEADER] = LoadTexture("data/textures/header.png");
    textures[TEX_BACKGROUND] = LoadTexture("data/textures/background.png");
    textures[TEX_NUMBERS] = LoadTexture("data/textures/numbers.png");
    textures[TEX_STARLIT] = LoadTexture("data/textures/starlit.png");
    textures[TEX_STARBLANK] = LoadTexture("data/textures/starblank.png");
    textures[TEX_GAMEOVER] = LoadTexture("data/textures/gameover.png");
    /* Load audio sounds. */
    sounds[SOUND_BRICKMOVE] = LoadSound("data/sounds/brickmove.ogg");
    sounds[SOUND_BRICKLAND] = LoadSound("data/sounds/brickland.ogg");
    sounds[SOUND_GAMEOVER] = LoadSound("data/sounds/gameover.ogg");
} 
