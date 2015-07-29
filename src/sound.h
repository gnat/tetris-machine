#ifndef _SOUND_H_
#define _SOUND_H_

extern FMOD_SYSTEM *fmod_system;

extern void FMODErrorCheck(FMOD_RESULT result);
extern void SetupSound();
extern void PlaySound(FMOD_SOUND *sound);
extern void MuteAllSound();

#endif
