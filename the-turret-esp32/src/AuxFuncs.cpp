#include "AuxFuncs.h"
#include "PinsAndDefs.h"



extern INA226 currSens[];
extern NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> leds;
extern NeoGamma<NeoGammaTableMethod> gammaCorr;

extern uint8_t feederSensePins[];
extern uint8_t fireSolenoidPins[];
extern uint8_t closedSWPins[];
extern uint8_t openSWPins[];


void InitPWM(){
    Wire.begin();

    pwm.resetDevices();       // Resets all PCA9685 devices on i2c line

    pwm.init();               // Initializes module using default totem-pole driver mode, and default disabled phase balancer
    pwm.setPWMFreqServo();    // 50Hz provides standard 20ms servo phase length



    if(!currSens[0].begin())
        Serial.println("Failed to init right current sensor");
    
    if(!currSens[1].begin())
        Serial.println("Failed to init left current sensor");

    currSens[0].setMaxCurrentShunt(1, 0.01);
    currSens[1].setMaxCurrentShunt(1, 0.01);
}


void InitPins(){
    pinMode(LASERS_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    
    for(uint8_t i = 0; i < WINGS; i++){
        pinMode(feederSensePins[i], INPUT);
        pinMode(fireSolenoidPins[i], OUTPUT);
        pinMode(closedSWPins[i], INPUT_PULLUP);
        pinMode(openSWPins[i], INPUT_PULLUP);
    }
}

void InitNeopixel(){
    leds.Begin();
    leds.Show();
}

void WriteServo(uint8_t indx, float pos){
    pwm.setChannelPWM(indx, pwmServo.pwmForAngle(pos));
}

void WriteServoSpeed(uint8_t indx, float s){
    pwm.setChannelPWM(indx, pwmServo.pwmForSpeed(s));
}

void WritePWMDuty(uint8_t indx, float val){
    uint16_t v = constrain(val * 4096, 0, 4096);
    pwm.setChannelPWM(indx, v);
}

void SetRingColor(RgbColor color){
    color = gammaCorr.Correct(color);
    leds.ClearTo(color);
    leds.Show();
}