#define WINGS 2

// Firing/feeder settings

#define FIRE_ON_MS 70
#define FIRE_OFF_MS 30
#define FIRE_REV_MS 3000

#define FIRE_DELAY_SLOW 200
#define FIRE_DELAY_MEDIUM 60
#define FIRE_DELAY_FAST 5

#define FIRE_DELAY_BURST 1

#define PADDLE_IDLE_STOP_MS 5000
#define FIRE_REV_IDLE_COEF 0.7f
#define FIRE_REV_ACTIVE_COEF 1.0f

#define BBBALANCE_CLUMP_THRESHOLD 2
#define BBBALANCE_JAM_THRESHOLD 5

#define CLUMP_CLEAR_VIBRATE_MS 500
#define CLUMP_CLEAR_COOLDOWN_MS 1000

#define JAM_CLEAR_BACK_MS 130
#define JAM_CLEAR_VIBRATE_MS 500
#define JAM_CLEAR_COOLDOWN_MS 2000


#define FEEDER_SENSE_ADC_THRESHOLD 2000 //We have to do analogReads on the feederSense pins, this is the threshold at which it should count as HIGH
#define PADDLE_DETECT_DEBOUNCE_MS 30

// Motion core settings

#define PITCH_MAX_ANGLE 60.0f
#define PITCH_MIN_ANGLE -40.0f

#define YAW_MAX_ANGLE 33.0f
#define YAW_MIN_ANGLE -23.0f

#define CLOSE_ZEROING_TIME_MS 500
#define CLOSE_EXTRA_TIME_MS 30
#define CLOSE_EXTRA_SPEED 0.3f

#define PITCH_OFFSET_R 4.5
#define YAW_OFFSET_R 0

#define PITCH_OFFSET_L 0
#define YAW_OFFSET_L 0

// Misc Settings

#define MAX_TCP_CLIENTS 3

// Pin definitions

#define FEEDER_MOTOR_INDX 7
#define FEEDER_AUX_INDX 6 

#define FEEDER_SENSE_R 39
#define FEEDER_SENSE_L 36

#define REV_INDX_R 3
#define REV_INDX_L 12

#define FIRE_SOLENOID_PIN_R 18
#define FIRE_SOLENOID_PIN_L 19

//

#define ENDSTOP_OPEN_R 14
#define ENDSTOP_OPEN_L 32

#define ENDSTOP_CLOSE_R 12
#define ENDSTOP_CLOSE_L 27


#define EXPAND_SERVO_INDEX_R 0
#define EXPAND_SERVO_INDEX_L 15

#define PITCH_SERVO_INDEX_R 1
#define PITCH_SERVO_INDEX_L 14

#define YAW_SERVO_INDEX_R 2
#define YAW_SERVO_INDEX_L 13

//

#define LED_PIN 2 // Built in LED
#define LASERS_PIN 13
#define NEOPIXEL_RING_PIN 15
#define BTN_PIN 0

#define BCLK 26
#define LRCLK 33
#define DOUT 25


#ifndef ENUMS
    #define ENUMS
    // State machine enums
    //                0       1       2          3          4       5        6
    enum WingState {Unknown, Open, Closing, ClosingSlow, Closed, Opening, Zeroing};
    enum FireState {Ready, SolOn, SolOff};
    enum FeedState {Nominal, Jam, Clump, Cooldown};
    enum TurretM {Autonomous, GloveManual, Default};
    enum FireMode {Auto = 0, Burst = 1, Single = 2};
    enum FireRate {Fast = 0, Medium = 1, Slow = 2};

#endif