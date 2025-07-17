#include <Arduino.h>
//#include <AsyncTCP.h>
#include <WiFiUdp.h>

struct IntentAndSlot {
    String intent;
    String slot;
};

void InitServer();
void ServerLoop();
void ParseCommand(const String&);
IntentAndSlot ParseIntent(const String&);