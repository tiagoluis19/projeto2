#include <Arduino.h>
#include <PCA9685.h>
#include <NeoPixelBus.h>
#include <INA226.h>



extern PCA9685 pwm;
extern PCA9685_ServoEval pwmServo;

void InitPWM();

void InitPins();

void InitNeopixel();

void WriteServo(uint8_t indx, float pos);

void WriteServoSpeed(uint8_t indx, float s);

void WritePWMDuty(uint8_t, float);

void SetRingColor(RgbColor);

void NeoPixelLoop();