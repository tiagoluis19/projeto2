// this main function is responsible for initializing the Picovoice SDK, processing audio input, and handling wake word detection and inference results.
//this will be the basis of the gauntlet for controlling the turret both key products of this project


#include <Arduino.h>
#include <Arduino_BMI270_BMM150.h>

#include <Picovoice_EN.h>
#include <gestureyay_inferencing.h>

#include "params.h"

#define MEMORY_BUFFER_SIZE (70 * 1024) //pico stuff

#define CONVERT_G_TO_MS2    9.80665f  //EI stuff
#define MAX_ACCEPTED_RANGE  2.0f 
static bool debug_nn = false;


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
    Serial.begin(115200);
    while (!Serial);
    
    IMU.begin();
    IMU.setContinuousMode();

    Serial.println("Picovoice EN Example");
  

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

  if (EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME != 6) {
        ei_printf("ERR: EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME should be equal to 6 (the 6 sensor axes)\n");
        return;
    }


}

float ei_get_sign(float number) {
    return (number >= 0.0) ? 1.0 : -1.0;
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

            }
        }
    }

    // gestures go here

    float buffer1[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = { 0 };

    for (size_t ix = 0; ix < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; ix += 3) {
        // Determine the next tick (and then sleep later)
        uint64_t next_tick = micros() + (EI_CLASSIFIER_INTERVAL_MS * 1000);

        IMU.readAcceleration(buffer1[ix], buffer1[ix + 1], buffer1[ix + 2]);
        IMU.readGyroscope(buffer1[ix + 3], buffer1[ix + 4], buffer1[ix + 5]);

        for (int i = 0; i < 3; i++) {
            if (fabs(buffer[ix + i]) > MAX_ACCEPTED_RANGE) {
                buffer1[ix + i] = ei_get_sign(buffer[ix + i]) * MAX_ACCEPTED_RANGE;
            }
        }

        buffer1[ix + 0] *= CONVERT_G_TO_MS2;
        buffer1[ix + 1] *= CONVERT_G_TO_MS2;
        buffer1[ix + 2] *= CONVERT_G_TO_MS2;

        delayMicroseconds(next_tick - micros());
    }

    signal_t signal;
    int err = numpy::signal_from_buffer(buffer1, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
    if (err != 0) {
        ei_printf("Failed to create signal from buffer (%d)\n", err);
        return;
    }

    ei_impulse_result_t result = { 0 };

    err = run_classifier(&signal, &result, debug_nn);
    if (err != EI_IMPULSE_OK) {
        ei_printf("ERR: Failed to run classifier (%d)\n", err);
        return;
    }

    // print the predictions
    ei_printf("Predictions ");
    ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
        result.timing.dsp, result.timing.classification, result.timing.anomaly);
    ei_printf(": \n");
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);
    }
#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("    anomaly score: %.3f\n", result.anomaly);
#endif
}


#if !defined(EI_CLASSIFIER_SENSOR) || EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_FUSION
#error "Invalid model for current sensor"
#endif