#ifndef _DATALOAD_H_
#define _DATALOAD_H_

extern void LoadData();

/* Texture type. */
typedef struct
{
    GLuint id;
    int width, height;
} TEXTURE;

/* Texture atlas. */
enum { TEX_HEADER, TEX_BACKGROUND, TEX_NUMBERS, TEX_STARLIT, TEX_STARBLANK, TEX_GAMEOVER, TEXTURE_COUNT };
extern TEXTURE* textures[TEXTURE_COUNT];

/* Sound atlas. */
enum { SOUND_BRICKMOVE, SOUND_BRICKLAND, SOUND_GAMEOVER, SOUND_COUNT };
extern FMOD_SOUND* sounds[SOUND_COUNT];

#endif
