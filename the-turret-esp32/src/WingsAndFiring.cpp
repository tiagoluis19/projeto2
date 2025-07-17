#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "PCA9685.h"
#include "AuxFuncs.h"
#include "PinsAndDefs.h"



extern PCA9685 pwm;
extern PCA9685_ServoEval pwmServo;

extern uint8_t closedSWPins[];
extern uint8_t openSWPins[];

extern uint8_t expServoIndxs[];
extern uint8_t pitchServoIndxs[];
extern uint8_t yawServoIndxs[];

extern uint8_t feederSensePins[];
extern uint8_t fireSolenoidPins[];
extern uint8_t revIndxs[];

extern float pitchOffts[];
extern float yawOffts[];

float pitch = 0;
float yaw = 0;

bool fire = false;
bool doRev = false;
uint16_t fireDelay = 10;

WingState wingStates[WINGS] = {};
WingState targetWingStates[2] = {};
uint64_t timer[WINGS] = {};

float pitches[WINGS] = {};
float yaws[WINGS] = {};

bool revStartDebounce[WINGS] = {};
uint64_t revStartMs[WINGS] = {};
FireState fireStates[WINGS] = {};
uint64_t fireTimer[WINGS] = {};
uint8_t nextFire = 0;
uint64_t paddleMovementMs = 0;

bool lastPaddleState[WINGS] = {};
uint64_t lastPaddleDebounceMillis[WINGS] = {};
int16_t BBBalance[WINGS] = {};
FeedState feedStates[WINGS] = {};
uint64_t feedTimer[WINGS] = {};

void WingLoop(){
  digitalWrite(LASERS_PIN, doRev);

  for(uint8_t i = 0; i < WINGS; i++){
    if(wingStates[i] != targetWingStates[i]){

      if(targetWingStates[i] == Closed){ //=====-----

        if(wingStates[i] == Open || wingStates[i] == Opening){
          bool shouldWait = wingStates[i] == Open;
          wingStates[i] = Zeroing;

          WriteServo(pitchServoIndxs[i], pitchOffts[i]);
          WriteServo(yawServoIndxs[i], yawOffts[i]);

          timer[i] = millis() + (shouldWait ? CLOSE_ZEROING_TIME_MS : 0);

        }else if(wingStates[i] == Zeroing){
          if(millis() >= timer[i]){
            WriteServoSpeed(expServoIndxs[i], 1.0f);
            wingStates[i] = Closing;
          }
          
        }else if(wingStates[i] == Closing){
          if(digitalRead(closedSWPins[i])){
            WriteServoSpeed(expServoIndxs[i], CLOSE_EXTRA_SPEED);
            wingStates[i] = ClosingSlow; //Begin close slow, keep going slower for a little longer so we're truly at end of travel
            timer[i] = millis() + CLOSE_EXTRA_TIME_MS;
          }

        }else if(wingStates[i] == ClosingSlow){
          if(millis() >= timer[i]){
            
            WriteServoSpeed(expServoIndxs[i], 0.0f);
            wingStates[i] = Closed;
            Serial.println("Closed");
          }
        }


      }else if(targetWingStates[i] == Open){ //=====-----
        WriteServoSpeed(expServoIndxs[i], -0.9f);
        wingStates[i] = Opening;
        

        if(!digitalRead(openSWPins[i])){
          wingStates[i] = Open;
          WriteServoSpeed(expServoIndxs[i], 0.0f);
          Serial.println("Open");
        }
      }
    }

    if(wingStates[i] == Open){
        float p = pitches[i] + pitchOffts[i];
        if(i == 1)
            p *= -1.0f;
        
        float y = yaws[i] + yawOffts[i];
        if(i == 0)
            y = constrain(yaws[i], YAW_MIN_ANGLE, YAW_MAX_ANGLE);
        else
            y = constrain(yaws[i], -YAW_MAX_ANGLE, -YAW_MIN_ANGLE);

        WriteServo(pitchServoIndxs[i], constrain(-p, PITCH_MIN_ANGLE, PITCH_MAX_ANGLE));
        WriteServo(yawServoIndxs[i], y);
    }

  }
}

void FireLoop(){
    for(uint8_t i = 0; i < WINGS; i++){
        if(doRev){
            if(!revStartDebounce[i]){
                revStartDebounce[i] = true;
                
                paddleMovementMs = millis();
                revStartMs[i] = millis() + FIRE_REV_MS;
            }

            if(fire){
                WritePWMDuty(revIndxs[i], FIRE_REV_ACTIVE_COEF);
            }else{
                WritePWMDuty(revIndxs[i], FIRE_REV_IDLE_COEF);
            }

            if(fireStates[i] == Ready && millis() >= revStartMs[i]){
                if(fire && nextFire == i){

                    fireStates[i] = SolOn;
                    digitalWrite(fireSolenoidPins[i], HIGH);
                    //digitalWrite(LED_PIN, LOW);
                    paddleMovementMs = millis();
                    fireTimer[i] = millis() + FIRE_ON_MS;
                }
            }else if(fireStates[i] == SolOn){
                if(millis() > fireTimer[i]){
                    fireStates[i] = SolOff;
                    digitalWrite(fireSolenoidPins[i], LOW);
                    //digitalWrite(LED_PIN, HIGH);
                    fireTimer[i] = millis() + FIRE_OFF_MS + fireDelay;
                }
            }else if(fireStates[i] == SolOff){
                if(millis() > fireTimer[i]){
                    fireStates[i] = Ready;
                    BBBalance[i] -= 1;

                    if(nextFire == i){
                        nextFire++;
                        if(nextFire == WINGS){
                            nextFire = 0;
                        }
                    }
                }
            }



        }else{
            revStartDebounce[i] = false;
            BBBalance[i] = 0;
            WritePWMDuty(revIndxs[i], 0.0f);
            digitalWrite(fireSolenoidPins[i], LOW);
        }
    }
}

void FeedLoop(){
    for(uint8_t i = 0; i < WINGS; i++){
        bool paddle = digitalRead(feederSensePins[i]);
        if(paddle != lastPaddleState[i]){
            if(millis() - lastPaddleDebounceMillis[i] > PADDLE_DETECT_DEBOUNCE_MS){
                lastPaddleState[i] = paddle;

                if(paddle){
                    lastPaddleDebounceMillis[i] = millis();
                    BBBalance[i] += 1;
                    paddleMovementMs = millis();
                }
            }
        }

        if(feedStates[i] == Nominal){
            if(doRev && (millis() - paddleMovementMs < PADDLE_IDLE_STOP_MS) ){
                WritePWMDuty(FEEDER_MOTOR_INDX, 0.7f);
                WritePWMDuty(FEEDER_AUX_INDX, 1.0f);
            }else{
                WritePWMDuty(FEEDER_MOTOR_INDX, 0.0f);
                WritePWMDuty(FEEDER_AUX_INDX, 0.0f);
            }
                
                /*
            if(BBBalance[i] > BBBALANCE_CLUMP_THRESHOLD){
                feedStates[i] = Clump;
                WritePWMDuty(FEEDER_AUX_INDX, 1.0f);
                feedTimer[i] = millis() + CLUMP_CLEAR_VIBRATE_MS;

            }else if(BBBalance[i] < -BBBALANCE_JAM_THRESHOLD){
                Serial.println("jam time");
                feedStates[i] = Jam;
                WritePWMDuty(FEEDER_AUX_INDX, 1.0f);
                //FeedMotorsSpeed(-255);
                feedTimer[i] = millis();
            }
            */

        }else if(feedStates[i] == Clump){
            WritePWMDuty(FEEDER_MOTOR_INDX, 0.8f);
            if(millis() > feedTimer[i]){
                WritePWMDuty(FEEDER_AUX_INDX, 0.0f);
                feedStates[i] = Cooldown;
                feedTimer[i] = millis() + CLUMP_CLEAR_COOLDOWN_MS;
            }

        }else if(feedStates[i] == Jam){
            Serial.println("we jammin");
            if(millis() > (feedTimer[i] + JAM_CLEAR_BACK_MS)){
                WritePWMDuty(FEEDER_MOTOR_INDX, 1.0f);
                Serial.println("go back no more");
            }

            if(millis() > (feedTimer[i] + JAM_CLEAR_VIBRATE_MS)){
                WritePWMDuty(FEEDER_AUX_INDX, 0.0f);
                feedStates[i] = Cooldown;
                feedTimer[i] = millis() + JAM_CLEAR_COOLDOWN_MS;
            }

        }else if(feedStates[i] == Cooldown){
            WritePWMDuty(FEEDER_AUX_INDX, 1.0f);
            if(millis() > feedTimer[i]){
                feedStates[i] = Nominal;
                BBBalance[i] = 0;
            }
        }
    }
}


void setup() {
    Serial.begin(115200);
    Serial.setTimeout(200);

    InitPins();
    InitPWM();
    InitNeopixel();
    SetRingColor(RgbColor(180,0,0));

    WiFi.softAP("Turret", "idonthateyou");

    for(uint8_t i = 0; i < WINGS; i++){ 
        targetWingStates[i] = Closed;
        wingStates[i] = Unknown;

        if(digitalRead(closedSWPins[i]) && digitalRead(openSWPins[i])){
        wingStates[i] = Closed;
        }
    }
    InitServer();
    
    delay(2500); //Prevents boot from being high when opening serial
    Serial.println(WiFi.softAPIP());
}

void loop() {

    ServerLoop();

    if(Serial.available()){
        char r = Serial.read();

        if(r == 'i'){
            pitch += 1.0f;
        }else if(r == 'k'){
            pitch -= 1.0f;
        }else if(r == 'j'){
            yaw += 1.0f;
        }else if(r == 'l'){
            yaw -= 1.0f;
        }else if(r == 'y'){
            doRev = true;
            fire = true;
        }else if(r == 'h'){
            doRev = false;
            fire = false;
        }else if(r == 't'){
            doRev = true;

        }else if (r == 'u'){
            targetWingStates[0] = Closed;
            targetWingStates[1] = Closed;
        }else if (r == 'o'){
            targetWingStates[0] = Open;
            targetWingStates[1] = Open;
        }

        pitch = constrain(pitch, PITCH_MIN_ANGLE, PITCH_MAX_ANGLE); 
        yaw = constrain(yaw, -YAW_MAX_ANGLE, YAW_MAX_ANGLE); //using the negative of min as max is intentional

        pitches[0] = pitch;
        pitches[1] = pitch;

        yaws[0] = yaw;
        yaws[1] = yaw;
    }

    WingLoop();
    FireLoop();
    FeedLoop();

    static uint64_t sendMillis = 0;
    if(millis() - sendMillis > 100){
        //Serial.println("RIGHT: P: " + String(pitch) + " Y: " + String(yaw) + " S: " + String(wingStates[0]) + " T: " + String(targetWingStates[0]) + " O: " + String(digitalRead(openSWPins[0])) + " C: " + String(digitalRead(closedSWPins[0])));
        //Serial.println("LEFT: P: " + String(pitch) + " Y: " + String(yaw) + " S: " + String(wingStates[1]) + " T: " + String(targetWingStates[1]) + " O: " + String(digitalRead(openSWPins[1])) + " C: " + String(digitalRead(closedSWPins[1])));
        
        sendMillis = millis();
    } 
}