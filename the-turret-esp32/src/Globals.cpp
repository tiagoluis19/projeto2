#include <Arduino.h>
#include <PCA9685.h>
#include <INA226.h>
#include <NeoPixelBus.h>
#include <BackgroundAudioWAV.h>
#include <ESP32I2SAudio.h>
#include "PinsAndDefs.h"


PCA9685 pwm(Wire); //Default 0x40 Address
PCA9685_ServoEval pwmServo;


INA226 currSens[2] = {INA226(0x41), INA226(0x44)};

NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> leds(12, NEOPIXEL_RING_PIN);
NeoGamma<NeoGammaTableMethod> gammaCorr;

TurretM turretMode = Manual;

ESP32I2SAudio i2sAudio(BCLK, LRCLK, DOUT); // BCLK, LRCLK, DOUT (,MCLK)
ROMBackgroundAudioWAV audio(i2sAudio);

uint8_t feederSensePins[2] = {FEEDER_SENSE_R, FEEDER_SENSE_L};
uint8_t fireSolenoidPins[2] = {FIRE_SOLENOID_PIN_R, FIRE_SOLENOID_PIN_L};

uint8_t revIndxs[2] = {REV_INDX_R, REV_INDX_L};


uint8_t expServoIndxs[2] = {EXPAND_SERVO_INDEX_R, EXPAND_SERVO_INDEX_L};
uint8_t pitchServoIndxs[2] = {PITCH_SERVO_INDEX_R, PITCH_SERVO_INDEX_L};
uint8_t yawServoIndxs[2] = {YAW_SERVO_INDEX_R, YAW_SERVO_INDEX_L};

uint8_t closedSWPins[2] = {ENDSTOP_CLOSE_R, ENDSTOP_CLOSE_L};
uint8_t openSWPins[2] = {ENDSTOP_OPEN_R, ENDSTOP_OPEN_L};

float pitchOffts[2] = {PITCH_OFFSET_R, PITCH_OFFSET_L};
float yawOffts[2] = {YAW_OFFSET_R, YAW_OFFSET_L};