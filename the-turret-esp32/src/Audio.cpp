#include <Arduino.h>
#include "Audio.h"

#include "target_acquired.h"
#include "firing.h"
#include "hello_friend.h"
#include "gotcha.h"
#include "there_you_are.h"
#include "i_see_you.h"

const unsigned char *targetFoundVoicelines[6] = {target_acquired_wav, firing_wav, hello_friend_wav, gotcha_wav, there_you_are_wav, i_see_you_wav};
unsigned int targetFoundVoicelinesLen[6] = {target_acquired_wav_len, firing_wav_len, hello_friend_wav_len, gotcha_wav_len, there_you_are_wav_len, i_see_you_wav_len};

extern ROMBackgroundAudioWAV audio;

void InitAudio(){
    audio.begin();
    audio.setGain(0.4);
}

void PlayAudio(const unsigned char music[], unsigned int len){
    audio.flush();
    audio.write(music, len);
}

void TargetFoundVoiceline(){
    uint8_t pick = random(0, 6);
    PlayAudio(targetFoundVoicelines[pick], targetFoundVoicelinesLen[pick]);
}