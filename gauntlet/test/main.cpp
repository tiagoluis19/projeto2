// this main function is responsible for initializing the Picovoice SDK, processing audio input, and handling wake word detection and inference results.
//this will be the basis of the gauntlet for controlling the turret both key products of this project


#include <Arduino.h>
#include <LSM9DS1.h>

#include <Picovoice_EN.h>

#include "params.h"

#define MEMORY_BUFFER_SIZE (70 * 1024)

static const char *ACCESS_KEY = "DLpSOMDCfmdoqWzfa/dFjuWtXfntd98N1+gHSXPSxPuAOOqZYZN2tg=="; // AccessKey string obtained from Picovoice Console (https://picovoice.ai/console/)

static pv_picovoice_t *handle = NULL;

static int8_t memory_buffer[MEMORY_BUFFER_SIZE] __attribute__((aligned(16)));

static const float PORCUPINE_SENSITIVITY = 0.75f;
static const float RHINO_SENSITIVITY = 0.5f;
static const float RHINO_ENDPOINT_DURATION_SEC = 1.0f;
static const bool RHINO_REQUIRE_ENDPOINT = true;

static void wake_word_callback(void) {
    Serial.println("Wake word detected!");
    
}

static void inference_callback(pv_inference_t *inference) {
    Serial.println("{");
    Serial.print("    is_understood : ");
    Serial.println(inference->is_understood ? "true" : "false");
    if (inference->is_understood) {
        Serial.print("    intent : ");
        Serial.println(inference->intent);
        if (inference->num_slots > 0) {
            Serial.println("    slots : {");
            for (int32_t i = 0; i < inference->num_slots; i++) {
                Serial.print("        ");
                Serial.print(inference->slots[i]);
                Serial.print(" : ");
                Serial.println(inference->values[i]);
            }
            Serial.println("    }");
        }
    }
    Serial.println("}\n");
    pv_inference_delete(inference);
}

static void print_error_message(char **message_stack, int32_t message_stack_depth) {
    for (int32_t i = 0; i < message_stack_depth; i++) {
        Serial.println(message_stack[i]);
    }
}

void setup() {
    Serial.begin(9600);
    while (!Serial);
    
    Serial.println("Picovoice EN Example");
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT); 
    pinMode(LEDB, OUTPUT); 


    digitalWrite(LEDR, 1);

    delay(1000); // Wait for 1 second to ensure the serial connection is established

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
    Serial.println("Wake word: 'hey computer'");
    Serial.println(rhino_context);

    digitalWrite(LEDR, 0);
    digitalWrite(LEDG, 1);
}

void loop() {

    
    
    digitalWrite(LEDB, 1);
    const int16_t *buffer = pv_audio_rec_get_new_buffer();
    digitalWrite(LEDG, 0);
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
                digitalWrite(LEDR, 1);
                delay(1000); // Keep the LED on for 1 second
                digitalWrite(LEDR, 0);
            }
        }
    }
}

