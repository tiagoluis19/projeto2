#include "Server.h"
#include "PinsAndDefs.h"
#include "Audio.h"

#include "radio.h"
#include "i_dont_hate_you.h"

extern ROMBackgroundAudioWAV audio;

extern float pitch;
extern float yaw;

extern bool fire;
extern bool doRev;

extern WingState targetWingStates[];

extern TurretM turretMode;

WiFiUDP udp;

void InitServer(){
    udp.begin(21);
}

void ServerLoop(){
  const uint8_t buffSize = 50;
  uint8_t buff[buffSize];

  if(udp.parsePacket()){
    uint32_t len = udp.read(buff, buffSize-1);
    buff[len] = 0;
    
    ParseCommand(String((char*) buff));
  }
}

void ParseCommand(const String& msg){
  Serial.println(msg);

  IntentAndSlot res = ParseIntent(msg);
  
  if(res.intent.length()){
    if(res.intent.startsWith("maintenance")){
      turretMode = Manual;

      pitch = 0.0f;
      yaw = 0.0f;

      if(targetWingStates[0] == Closed){
        targetWingStates[0] = Open;
        targetWingStates[1] = Open;
      }else{
        targetWingStates[0] = Closed;
        targetWingStates[1] = Closed;
      }

    }else if(res.intent.startsWith("sing")){
        if(res.slot.length() > 0){
          if(res.slot.startsWith("portal radio music")){
            PlayAudio(radio_wav, radio_wav_len);
            Serial.println("Radio");

          }else if(res.slot.startsWith("turret opera")){
            //PlayAudio(portal_opera_wav, portal_opera_wav_len);
            Serial.println("Radio");
          }
        }
    }else if(res.intent.startsWith("cakeisalie")){
      PlayAudio(i_dont_hate_you_wav, i_dont_hate_you_wav_len);
      Serial.println("hate");

    }else if(res.intent.startsWith("controlovr")){
      if(turretMode == GloveManual){
        turretMode = Manual;
        targetWingStates[0] = Closed;
        targetWingStates[1] = Closed;
      }else{
        turretMode = GloveManual;
        targetWingStates[0] = Open;
        targetWingStates[1] = Open;
      }
    }

  }else{
    if(msg.startsWith("P") && turretMode == GloveManual){
      String pSubstr = msg.substring(1, msg.indexOf('Y'));
      String ySubstr = msg.substring(msg.indexOf('Y') + 1);
      pitch = pSubstr.toFloat();
      yaw = ySubstr.toFloat();

    }else if(msg.startsWith("open")){
      targetWingStates[0] = Open;
      targetWingStates[1] = Open;
      
    }else if(msg == "close"){
      targetWingStates[0] = Closed;
      targetWingStates[1] = Closed;

    }else if(msg.startsWith("revOn")){
      doRev = true;

    }else if(msg.startsWith("revOff")){
      doRev = false;

    }else if(msg.startsWith("fireOn")){
      fire = true;

    }else if(msg.startsWith("fireOff")){
      fire = false;
    }
  }

  /*if(msg.startsWith("open")){
    targetWingStates[0] = Open;
    targetWingStates[1] = Open;
  }else if(msg == "close"){
    targetWingStates[0] = Closed;
    targetWingStates[1] = Closed;
  }else if(msg == "revOn"){
    doRev = true;
  }else if(msg == "revOff"){
    doRev = false;
  }else if(msg == "fireOn"){
    fire = true;
  }else if(msg == "fireOff"){
    fire = false;
  }else if(msg.startsWith("P")){
    String pSubstr = msg.substring(1, msg.indexOf('Y'));
    String ySubstr = msg.substring(msg.indexOf('Y') + 1);
    pitch = pSubstr.toFloat();
    yaw = ySubstr.toFloat();
  }
    */
}

IntentAndSlot ParseIntent(const String& msg){
  IntentAndSlot out;

  int16_t intEndIndx = msg.indexOf(">");
  if(msg.startsWith("<") && intEndIndx > 0 ){
    out.intent = msg.substring(1, intEndIndx);
    //Serial.println("parse int: " + out.intent);

    int16_t slotStartIndx = msg.indexOf("{");
    int16_t slotEndIndx  = msg.indexOf("}");

    if(slotStartIndx > 0 && slotEndIndx > 0){
      out.slot = msg.substring(slotStartIndx+1, slotEndIndx);
      //Serial.println("parse slot: " + out.slot);
    }
  }

  return out;
}