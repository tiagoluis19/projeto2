#include <Arduino.h>
#include "AuxFuncs.h"
#include "PinsAndDefs.h"

extern const  uint8_t feederSensePins[];
extern const  uint8_t fireSolenoidPins[];
extern const  uint8_t revIndxs[];
extern INA226 currSens[];

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(200);
  
  InitNeopixel();
  InitPins();
  InitPWM();

  delay(2500); //Prevents boot from being high when opening serial
}

void loop(){
    Serial.println("Press boot to start test");
    while(digitalRead(BTN_PIN)){
        yield();
    }


    for(uint8_t s = 0; s < WINGS; s++){
        Serial.println("Testing " + (s == 0) ? "Right wing:" : "Left wing:");
        SetRingColor((s == 0) ? RgbColor(0, 60, 127) : RgbColor(127, 60, 0));

        Serial.println("Laser On");
        digitalWrite(LASERS_PIN, 1);
        delay(2000);
        digitalWrite(LASERS_PIN, 0);
        Serial.println("Laser Off");
        delay(500);

        Serial.println("Revving");
        WritePWMDuty(revIndxs[s], 1.0f);
        delay(3000);
        Serial.print("Rev voltage: ");
        Serial.print(currSens[s].getBusVoltage(), 3);
        Serial.print("V Rev current: ");
        Serial.print(currSens[s].getCurrent_mA()/1000.0f, 3);
        Serial.println(" mA");
        WritePWMDuty(revIndxs[s], 0.0f);
        delay(500);

        Serial.println("Solenoid");
        for(uint8_t i=0; i < 15; i++){
            digitalWrite(fireSolenoidPins[s], 1);
            delay(100);
            digitalWrite(fireSolenoidPins[s], 0);
            delay(30);
        }


        
        uint8_t counts = 0;
        bool lastState = analogRead(feederSensePins[s]) > FEEDER_SENSE_ADC_THRESHOLD;
        uint64_t timer;
        Serial.println("Feeder");

        WritePWMDuty(FEEDER_MOTOR_INDX, 0.7f);
        
        timer = millis();
        while(millis() - timer < 2000){
            bool state = analogRead(feederSensePins[s]) > FEEDER_SENSE_ADC_THRESHOLD;

            if(state != lastState){
                counts++;
            }
            delay(10);
        }
        WritePWMDuty(FEEDER_MOTOR_INDX, 0.0f);
        Serial.println("Feeder counts: " + String(counts));
    }

    SetRingColor(RgbColor(0, 0, 0));

}