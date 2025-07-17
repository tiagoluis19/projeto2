#include "Server.h"
#include "PinsAndDefs.h"

extern float pitch;
extern float yaw;

extern bool fire;
extern bool doRev;

extern WingState targetWingStates[];

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
      static bool maintenanceMode = false;
      maintenanceMode = !maintenanceMode;
      
      if(maintenanceMode){
        targetWingStates[0] = Open;
        targetWingStates[1] = Open;
      }else{
        targetWingStates[0] = Closed;
        targetWingStates[1] = Closed;
      }

    }

  }else{
    if(msg.startsWith("P")){
      String pSubstr = msg.substring(1, msg.indexOf('Y'));
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