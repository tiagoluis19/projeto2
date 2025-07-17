// this main function is responsible for initializing the Picovoice SDK, processing audio input, and handling wake word detection and inference results.
//this will be the basis of the gauntlet for controlling the turret both key products of this project


#include <Arduino.h>
#include <Arduino_BMI270_BMM150.h>

#include <Picovoice_EN.h>


#include "params.h"

#define MEMORY_BUFFER_SIZE (70 * 1024) //pico stuff

#define CONVERT_G_TO_MS2    9.80665f  //EI stuff
#define MAX_ACCEPTED_RANGE  2.0f 



static const char *ACCESS_KEY = "DLpSOMDCfmdoqWzfa/dFjuWtXfntd98N1+gHSXPSxPuAOOqZYZN2tg=="; // AccessKey string obtained from Picovoice Console (https://picovoice.ai/console/)

static pv_picovoice_t *handle = NULL;

static int8_t memory_buffer[MEMORY_BUFFER_SIZE] __attribute__((aligned(16)));

static const float PORCUPINE_SENSITIVITY = 0.75f;
static const float RHINO_SENSITIVITY = 0.65f;
static const float RHINO_ENDPOINT_DURATION_SEC = 1.0f;
static const bool RHINO_REQUIRE_ENDPOINT = true;

static void wake_word_callback(void) {
    Serial.println("Wake word detected!");
    Serial1.println("wwu");
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
    
    newstring[sprintf(newstring,"0 I %s, S %s", inference_str, slot_str)] = 0;

    Serial1.println(newstring); 
    
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

    IMU.begin();
    IMU.setContinuousMode();

    pinMode(LEDR,OUTPUT);
    pinMode(LEDB,OUTPUT);

    digitalWrite(LEDR,1);
    digitalWrite(LEDB,1);
    pv_status_t status = pv_audio_rec_init();
    if (status != PV_STATUS_SUCCESS) {
        Serial.print("Audio init failed with ");
        Serial.println(pv_status_to_string(status));
        while (1);
    }

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


char IMUstring[70];
  float ax, ay, az;     
    float gx, gy, gz; 
    float mx, my, mz; 
float mxold, myold, mzold;

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

    




if((analogRead(A1) <= 2400) && (analogRead(A3)<=2400)) { 
    //for manual mode movement o the servos   prolly activate with sec override as SR latch

    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);  
    static uint64_t timestamp=0;
    if(millis()-timestamp>110){
        IMU.readMagneticField(mx, my, mz);
        timestamp= millis();
    }

        
        Serial1.println("<1 A:"+String(ax)+", "+String(ay)+", "+String(az)+ " G:" +String(gx)+", "+String(gy)+", "+String(gz) + " M:" +String(mx)+", "+String(my)+", "+String(mz)+">" ); // send the IMU data to the serial port
    
    
    delay(50);
    

}
}


