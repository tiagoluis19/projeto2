#include "Audio.h"

extern ROMBackgroundAudioWAV audio;

void InitAudio(){
    audio.begin();
    audio.setGain(0.4);
}

void PlayAudio(const unsigned char music[], unsigned int len){
    audio.flush();
    audio.write(music, len);
}