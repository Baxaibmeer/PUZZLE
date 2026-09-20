#include "audio.h"
#include "raylib.h"
#include "globals.h"

//Sound moveSound;
bool isMuted = false;

void LoadGameSound() {
    InitAudioDevice();
    moveSound = LoadSound("click.wav");
}


void ToggleMute() {
    isMuted = !isMuted;
}

bool IsMuted() {
    return isMuted;
}

void PlayMoveSound() {
    if (!isMuted) PlaySound(moveSound);
}

void CloseAudio() {
    UnloadSound(moveSound);
    CloseAudioDevice();
}
