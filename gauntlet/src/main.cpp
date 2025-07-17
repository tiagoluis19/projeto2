// this main function is responsible for initializing the Picovoice SDK, processing audio input, and handling wake word detection and inference results.
//this will be the basis of the gauntlet for controlling the turret both key products of this project


#include <Arduino.h>
#include <Arduino_BMI270_BMM150.h>

#include <Picovoice_EN.h>


#include "params.h"

#define BTN_PIN 3

#define MEMORY_BUFFER_SIZE (70 * 1024) //pico stuff

#define CONVERT_G_TO_MS2    9.80665f  //EI stuff
#define MAX_ACCEPTED_RANGE  2.0f 

// IMU stuff
float gyroX,             gyroY,              gyroZ,             // units dps (degrees per second)        // units dps
      gyroCorrectedRoll, gyroCorrectedPitch, gyroCorrectedYaw;  // units degrees (expect minor drift)

float gyroDriftX = 0.01f, gyroDriftY = -0.14f, gyroDriftZ = 0.05f;

long IMULast;
long lastIMUDeltaMs;

bool readIMU();
void CorrIMU();
void calibrateIMU(uint64_t, uint64_t);

static const char *ACCESS_KEY = "DLpSOMDCfmdoqWzfa/dFjuWtXfntd98N1+gHSXPSxPuAOOqZYZN2tg=="; // AccessKey string obtained from Picovoice Console (https://picovoice.ai/console/)

static pv_picovoice_t *handle = NULL;

static int8_t memory_buffer[MEMORY_BUFFER_SIZE] __attribute__((aligned(16)));

static const float PORCUPINE_SENSITIVITY = 0.75f;
static const float RHINO_SENSITIVITY = 0.65f;
static const float RHINO_ENDPOINT_DURATION_SEC = 1.0f;
static const bool RHINO_REQUIRE_ENDPOINT = true;

static void wake_word_callback(void) {
    Serial.println("Wake word detected!");
    Serial1.println("WD");
    digitalWrite(LEDR,0);
    osDelay(200);
    digitalWrite(LEDR,1);
    
}

char inference_str[50]; // buffer for inference results
char slot_str[50]; // buffer for slot values
char newstring[50]; // buffer for new string


static void inference_callback(pv_inference_t *inference) {
    Serial.println("{");
    Serial.print("    is_understood : ");
    Serial.println(inference->is_understood ? "true" : "false");
    digitalWrite(LEDB,!inference->is_understood);
    
    if (inference->is_understood) {
        
        Serial.print("    intent : ");
        Serial.println(inference->intent);
        strcpy(inference_str, inference->intent);
        Serial.print("    num_slots : ");
        if (inference->num_slots > 0) {
            Serial.println("    slots : {");
            for (int32_t i = 0; i < inference->num_slots; i++) {
                Serial.print("        ");
                Serial.print(inference->slots[i]);
                Serial.print(" : ");
                Serial.println(inference->values[i]);
                strcpy(slot_str, inference->values[i]);
            }
            Serial.println("    }");
        }
    }
    Serial.println("}\n");
    
    //newstring[sprintf(newstring,"0 I %s, S %s", inference_str, slot_str)] = 0;
    //Serial1.println(newstring); 
    String msg ="<" + String(inference->intent) + ">";
    
    if(inference->num_slots > 0){
        msg += "{" + String(inference->values[0]) + "}";
    }
    Serial1.println(msg);


    pv_inference_delete(inference);
    osDelay(200);
    digitalWrite(LEDB,1);
}

static void print_error_message(char **message_stack, int32_t message_stack_depth) {
    for (int32_t i = 0; i < message_stack_depth; i++) {
        Serial.println(message_stack[i]);
    }
}

void setup() {
    Serial.begin(115200);
    Serial1.begin(9600);
    
    
analogReadResolution(12); // set the resolution of the analog read to 12 bits

    pinMode(A1, INPUT); //pointer finger
    pinMode(A3, INPUT); //middle finger
    pinMode(A5, INPUT); //ring finger
    pinMode(A7, INPUT); //pinky finger

    pinMode(BTN_PIN, INPUT_PULLUP);

    IMU.begin();
    IMU.setContinuousMode();

    pinMode(LEDR,OUTPUT);
    pinMode(LEDB,OUTPUT);
    pinMode(LEDG, OUTPUT);
    
    digitalWrite(LEDG, 1);
    digitalWrite(LEDR,1);
    digitalWrite(LEDB,1);
    
    pv_status_t status = pv_audio_rec_init();
    if (status != PV_STATUS_SUCCESS) {
        Serial.print("Audio init failed with ");
        Serial.println(pv_status_to_string(status));
        while (1);
    }

    //calibrateIMU(1000, 2500);

    IMULast = micros();

    char **message_stack = NULL;
    int32_t message_stack_depth = 0;
    pv_status_t error_status;

    status = pv_picovoice_init(
        ACCESS_KEY,
        MEMORY_BUFFER_SIZE,
        memory_buffer,
        sizeof(KEYWORD_ARRAY),
        KEYWORD_ARRAY,
        PORCUPINE_SENSITIVITY,
        wake_word_callback,
        sizeof(CONTEXT_ARRAY),
        CONTEXT_ARRAY,
        RHINO_SENSITIVITY,
        RHINO_ENDPOINT_DURATION_SEC,
        RHINO_REQUIRE_ENDPOINT,
        inference_callback,
        &handle);
    if (status != PV_STATUS_SUCCESS) {
        Serial.print("Picovoice init failed with ");
        Serial.println(pv_status_to_string(status));

        error_status = pv_get_error_stack(&message_stack, &message_stack_depth);
        if (error_status != PV_STATUS_SUCCESS) {
            Serial.println("Unable to get Porcupine error state");
            while (1);
        }
        print_error_message(message_stack, message_stack_depth);
        pv_free_error_stack(message_stack);

        while (1);
    }

    const char *rhino_context = NULL;
    status = pv_picovoice_context_info(handle, &rhino_context);
    if (status != PV_STATUS_SUCCESS) {
        Serial.print("retrieving context info failed with");
        Serial.println(pv_status_to_string(status));
        while (1);
    }
    Serial.println("Wake word: 'hey Turret'");
    Serial.println(rhino_context);

  


}

void loop() {

    
    
   
    const int16_t *buffer = pv_audio_rec_get_new_buffer();
   
    if (buffer) {
        const pv_status_t status = pv_picovoice_process(handle, buffer);
         

        if (status != PV_STATUS_SUCCESS) {
            Serial.print("Picovoice process failed with ");
            Serial.println(pv_status_to_string(status));
            char **message_stack = NULL;
            int32_t message_stack_depth = 0;
            pv_get_error_stack(
                &message_stack,
                &message_stack_depth);
            for (int32_t i = 0; i < message_stack_depth; i++) {
                Serial.println(message_stack[i]);
            }
            pv_free_error_stack(message_stack);
            while (1){
                    Serial.println("Error in Picovoice processing, halting execution.");
            }
        }
    }


  if (readIMU()) {
    long currentTime = micros();
    lastIMUDeltaMs = currentTime - IMULast; // expecting this to be ~104Hz +- 4%
    IMULast = currentTime;

    CorrIMU();
  }

    static bool lastFingerState = false;
    static bool lastFireState = false;
    static uint64_t lastGyroMs = 0;
    //(analogRead(A1) <= 2500) && 
    if((analogRead(A3)<=2300)) { 
        //for manual mode movement o the servos prolly activate with sec override as SR latch
        
        if(!lastFingerState){
            lastFingerState = true;
            Serial1.println("revOn");
        }

        bool fireState = !digitalRead(BTN_PIN);
        if(fireState != lastFireState){
            lastFireState = fireState;

            if(fireState){
                Serial1.println("fireOn");
            }else{
                Serial1.println("fireOff");
            }
        }

        //order is "wrong" on purpose
        digitalWrite(LEDG, 0);
        if(millis() - lastGyroMs > 30){
            Serial1.println("P" +String(gyroCorrectedRoll)+"Y"+String(-gyroCorrectedPitch)); // send the IMU data to the serial port
        }
    }else{
        digitalWrite(LEDG, 1);

        if(lastFingerState){
            lastFingerState = false;
            Serial1.println("revOff");
            Serial1.println("fireOff");
        }

        if(!digitalRead(BTN_PIN)){
            gyroCorrectedRoll = 0;
            gyroCorrectedPitch = 0;
            gyroCorrectedYaw = 0;
        }
    }

    //Serial.println("  " + String(analogRead(A1)) + "  " + String(analogRead(A3)) + "  " + String(analogRead(A5)) + "  " + String(analogRead(A7)));
    //delay(50);
}


void calibrateIMU(uint64_t delayMillis, uint64_t calibrationMillis) {

  int calibrationCount = 0;

  delay(delayMillis); // to avoid shakes after pressing reset button

  float sumX = 0, sumY = 0, sumZ = 0;
  uint64_t startTime = millis();
  while (millis() < startTime + calibrationMillis) {
    if (readIMU()) {
      // in an ideal world gyroX/Y/Z == 0, anything higher or lower represents drift
      sumX += gyroX;
      sumY += gyroY;
      sumZ += gyroZ;

      calibrationCount++;
    }
  }

  if (calibrationCount == 0) {
    Serial.println("Failed to calibrate");
  }

  gyroDriftX = sumX / calibrationCount;
  gyroDriftY = sumY / calibrationCount;
  gyroDriftZ = sumZ / calibrationCount;

  Serial.println("Gyro drift: X:" + String(gyroDriftX) + " Y:" + String(gyroDriftY) + " Z:" + String(gyroDriftZ));
  delay(1000);
}

bool readIMU() {
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable() ) {
    IMU.readGyroscope(gyroX, gyroY, gyroZ);
    return true;
  }
  return false;
}


void CorrIMU() {
  float lastFrequency = (float) 1000000.0 / lastIMUDeltaMs;

  gyroCorrectedRoll = gyroCorrectedRoll + ((gyroX - gyroDriftX) / lastFrequency);
  gyroCorrectedPitch = gyroCorrectedPitch + ((gyroY - gyroDriftY) / lastFrequency);
  gyroCorrectedYaw = gyroCorrectedYaw + ((gyroZ - gyroDriftZ) / lastFrequency);
}