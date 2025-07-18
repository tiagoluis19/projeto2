#include "AuxFuncs.h"
#include "PinsAndDefs.h"



extern INA226 currSens[];
extern NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> leds;
extern NeoGamma<NeoGammaTableMethod> gammaCorr;

extern uint8_t feederSensePins[];
extern uint8_t fireSolenoidPins[];
extern uint8_t closedSWPins[];
extern uint8_t openSWPins[];

extern RgbColor feedBackColors[];
extern TurretM turretMode;
extern FireMode fireMode;
extern FireRate fireRate;
extern bool safety;

extern uint64_t feedBackMillis;

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

void NeoPixelLoop(){
    if(millis() - feedBackMillis < 8000){ //Show feedback
        leds.ClearTo(RgbColor(0,0,0));
        leds.ClearTo(turretMode == GloveManual ? feedBackColors[2] : feedBackColors[0], 1, 2); //Auto/manual
        
        leds.ClearTo(true ? feedBackColors[2] : feedBackColors[0], 3, 4); //Right jam ok

        leds.ClearTo(feedBackColors[fireMode], 5, 6); //Fire mode
        leds.ClearTo(feedBackColors[fireRate], 7, 8); //Fire rate

        leds.ClearTo(true ? feedBackColors[2] : feedBackColors[0], 9, 10); //Left jam ok

        leds.SetPixelColor(0, true ? feedBackColors[2] : feedBackColors[0]); //Ammo state
        leds.SetPixelColor(11, true ? feedBackColors[2] : feedBackColors[0]); //Ammo state

        //leds.ClearTo(feedBackColors[1], 2, 3);
        //leds.ClearTo(feedBackColors[2], 4, 5);
        leds.Show();
    }else{
        SetRingColor(safety ? RgbColor(0,0,180) : RgbColor(180,0,0));
    }
}

//show jams, firerate, fire mode, safety, auto/manual, ammo