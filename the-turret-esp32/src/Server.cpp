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
extern bool safety;
extern uint16_t burstCount;
extern uint16_t fireDelays[];

uint64_t feedBackMillis = 0;

extern WingState targetWingStates[];

extern TurretM turretMode;
extern FireMode fireMode;
extern FireRate fireRate;

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
  
  if(res.intent.length()>0)
    Serial.println("Intent: " + res.intent);
  if(res.slot.length()>0)
    Serial.println("Slot: " + res.slot);

  if(res.intent.length()){
    if(res.intent.startsWith("maintenance")){
      turretMode = Default;

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
    }else if(res.intent.startsWith("rateoffire")){
      if(res.slot.startsWith("slow")){
        fireRate = Slow;

      }else if(res.slot.startsWith("medium")){
        fireRate = Medium;

      }else if(res.slot.startsWith("fast")){
        fireRate = Fast;
      }
      Serial.println("Set firerate to: " + String(fireRate));

    }else if(res.intent.startsWith("safety")){
      if(res.slot.startsWith("on")){
        safety = true;
      }else if(res.slot.startsWith("off")){
        safety = false;
      }
      Serial.println("Safety " + safety ? "on" : "off");
    
    }else if(res.intent.startsWith("feedback")){
      feedBackMillis = millis();
    }else if(res.intent.startsWith("cakeisalie")){
      PlayAudio(i_dont_hate_you_wav, i_dont_hate_you_wav_len);
      Serial.println("hate");
    
    }else if(res.intent.startsWith("returnauto")){
      turretMode = Autonomous;
      targetWingStates[0] = Closed;
      targetWingStates[1] = Closed;
      fire = false;
      doRev = false;

    }else if(res.intent.startsWith("controlovr")){
        turretMode = GloveManual;
        fire = false;
        doRev = false;
        targetWingStates[0] = Open;
        targetWingStates[1] = Open;

    }else if(res.intent.startsWith("openstatus")){
      if(res.slot.startsWith("deploy")){
        targetWingStates[0] = Open;
        targetWingStates[1] = Open;

      }else if(res.slot.startsWith("retract")){
        targetWingStates[0] = Closed;
        targetWingStates[1] = Closed;
      }
    }else if(res.intent.startsWith("mode")){
        Serial.println("Firemode");

        if(res.slot.startsWith("auto")){
            fireMode = Auto;
            Serial.println("Firemode to full");
        }else if(res.slot.startsWith("single")){
            fireMode = Single;
            Serial.println("Firemode to single");
        }else if(res.slot.startsWith("burst")){
            fireMode = Burst;
            Serial.println("Firemode to burst");
        }
    }

  }else{ // NOT a intent-slot command
    if(msg.startsWith("P") && turretMode == GloveManual){
      String pSubstr = msg.substring(1, msg.indexOf('Y'));
      String ySubstr = msg.substring(msg.indexOf('Y') + 1);
      pitch = pSubstr.toFloat();
      yaw = ySubstr.toFloat();
    }else if(msg.startsWith("B")){
      burstCount = msg.substring(1).toInt();
      
    }else if(msg.startsWith("open")){
      targetWingStates[0] = Open;
      targetWingStates[1] = Open;
      
    }else if(msg == "close"){
      targetWingStates[0] = Closed;
      targetWingStates[1] = Closed;

    }else if(msg.startsWith("Aopen") && turretMode == Autonomous){
      targetWingStates[0] = Open;
      targetWingStates[1] = Open;
      
    }else if(msg == "Aclose" && turretMode == Autonomous){
      targetWingStates[0] = Closed;
      targetWingStates[1] = Closed;

    }else if(msg.startsWith("ArevOn") && turretMode == Autonomous){
      doRev = true;

    }else if(msg.startsWith("ArevOff") && turretMode == Autonomous){
      doRev = false;

    }else if(msg.startsWith("AfireOn") && turretMode == Autonomous){
      fire = true;

    }else if(msg.startsWith("AfireOff") && turretMode == Autonomous){
      fire = false;

    }else if(msg.startsWith("voiceline_found")){
      //TargetFoundVoiceline(); Commented: speaker makes the voicelines sad, plus it's crashing for some reason

    }else if(msg.startsWith("revOn")){
      doRev = true;

    }else if(msg.startsWith("revOff")){
      doRev = false;

    }else if(msg.startsWith("fireOn")){
      fire = true;

    }else if(msg.startsWith("fireOff")){
      fire = false;

    }else if(msg.startsWith("AP") && turretMode == Autonomous){
      String pSubstr = msg.substring(2, msg.indexOf('Y'));
      String ySubstr = msg.substring(msg.indexOf('Y') + 1);
      pitch = pSubstr.toFloat();
      yaw = ySubstr.toFloat();
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