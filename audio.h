#ifndef AUDIO_H
#define AUDIO_H

extern bool isMuted;

void LoadGameSound();
void ToggleMute();
bool IsMuted();
void PlayMoveSound();
void CloseAudio();
//void LoadGameSound();
//void UnloadGameSound();

#endif
