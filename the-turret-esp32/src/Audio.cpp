#include <Arduino.h>
#include "Audio.h"

#include "target_acquired.h"
#include "firing.h"
#include "hello_friend.h"
#include "gotcha.h"
#include "there_you_are.h"
#include "i_see_you.h"
#include "deploying.h"
#include "whos_there.h"
#include "are_you_still_there.h"
#include "target_lost.h"
#include "searching.h"
#include "can_i_help_you.h"
#include "goodbye.h"
#include "sleep_mode_activated.h"
#include "goodnight.h"
#include "nap_time.h"
#include "hibernating.h"

const unsigned char *targetFoundVoicelines[8] = {target_acquired_wav, firing_wav, hello_friend_wav, gotcha_wav, there_you_are_wav, i_see_you_wav, deploying_wav, whos_there_wav};
unsigned int targetFoundVoicelinesLen[8] = {target_acquired_wav_len, firing_wav_len, hello_friend_wav_len, gotcha_wav_len, there_you_are_wav_len, i_see_you_wav_len, deploying_wav_len, whos_there_wav_len};

const unsigned char *targetLostVoiceLines[4] = {are_you_still_there_wav, target_lost_wav, searching_wav, can_i_help_you_wav};
unsigned int targetLostVoiceLinesLen[4] = {are_you_still_there_wav_len, target_lost_wav_len, searching_wav_len, can_i_help_you_wav_len};

const unsigned char *closeVoiceLines[5] = {goodbye_wav, sleep_mode_activated_wav, goodnight_wav, nap_time_wav, hibernating_wav};
unsigned int closeVoiceLinesLen[5] = {goodbye_wav_len, sleep_mode_activated_wav_len, goodnight_wav_len, nap_time_wav_len, hibernating_wav_len};

extern ROMBackgroundAudioWAV audio;

void InitAudio(){
    audio.begin();
    audio.setGain(0.5); //Do not raise this or else clipping is guaranteed no matter the speaker...
}

void PlayAudio(const unsigned char music[], unsigned int len){
    audio.flush();
    audio.write(music, len);
}

void TargetFoundVoiceline(){
    uint8_t pick = random(0, sizeof(targetFoundVoicelines)/sizeof(targetFoundVoicelines[0]));

    PlayAudio(targetFoundVoicelines[pick], targetFoundVoicelinesLen[pick]);
}

void TargetLostVoiceline(){
    uint8_t pick = random(0, sizeof(targetLostVoiceLines)/sizeof(targetLostVoiceLines[0]));
    
    PlayAudio(targetLostVoiceLines[pick], targetLostVoiceLinesLen[pick]);
}

void CloseVoiceline(){
    uint8_t pick = random(0, sizeof(closeVoiceLines)/sizeof(closeVoiceLines[0]));
    
    PlayAudio(closeVoiceLines[pick], closeVoiceLinesLen[pick]);
}