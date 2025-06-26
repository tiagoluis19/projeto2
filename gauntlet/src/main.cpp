//this will be the code for gesture recording using LSM9DS1 IMU sensor
//the data collected by this code will be used in edge impulse
//for model cration and testing
//if using this its best to collect arround 15-20 minutes of data

#include <Arduino.h>
#include <Arduino_BMI270_BMM150.h>
#include <neotimer.h>
#include <SensorFusion.h>



SF fusion;
float deltat;
float ax, ay, az; //acceleration
float gx, gy, gz; //gyroscope
float pitch, roll, yaw; //angles


struct Recorder {
    int state; // 0: wait, 1: recording
    
};

timer_t timer; //timer for user input

Neotimer secTimer_10 = Neotimer(10000); //10 seconds timer for user input


void setup(){
    Serial.begin(115200);
    while (!Serial);

    if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }
    


    pinMode(A1, INPUT); //pointer   finger
    pinMode(A3, INPUT); //middle    finger 
    pinMode(A5, INPUT); //ring      finger 
    pinMode(A7, INPUT); //pinky     finger 

    pinMode(LEDR, OUTPUT); //LED for visual feedback
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);


};


void loop(){

int limit;
int user_time;//in milliseconds

Recorder recorder = {0}; //initial state is idle

    switch (recorder.state){
    case 0: //idle state waits for user input to start recording getures
            //indicated by green LED
        digitalWrite(LEDG, HIGH); //turn on green LED    
        if(analogRead(A1)==limit)
            recorder.state = 1; //if pointer finger is up then start the recording session
        break;

    case 1: //recording state records the gestures and transmits them via UART
            //indicated by red LED
        delay(user_time); //delay to give time to the user

        
        digitalWrite(LEDR, HIGH); //turn on red LED
        secTimer_10.start(); //start the timer
        

        if(secTimer_10.done()){
            secTimer_10.stop();
            digitalWrite(LEDB, HIGH);
            digitalWrite(LEDR, LOW);
            delay(1000);
            digitalWrite(LEDB, LOW);
            recorder.state = 0; //return to idle state
            break; //exit the case
        }

        //read the IMU data
        

        IMU.readAcceleration(ax, ay, az);
        IMU.readGyroscope(gx, gy, gz);  // attention must me in radians

        gx = gx * DEG_TO_RAD; gy = gy * DEG_TO_RAD; gz = gz * DEG_TO_RAD;

        deltat = fusion.deltatUpdate();

        fusion.MahonyUpdate(gx, gy, gz, ax, ay, az, deltat); //update the fusion algorithm

        pitch = fusion.getPitch();   // results in degrees   to use radians use getPitchRadians() and so on
        roll = fusion.getRoll();
        yaw = fusion.getYaw();

        Serial.print(pitch);Serial.print(";");Serial.print(roll);Serial.print(";");Serial.print(yaw);Serial.println(";");




        break;
    
    default: //in case shit hits the fan
             //indicated by no led

        digitalWrite(LEDR, LOW);
        digitalWrite(LEDG, LOW);
        digitalWrite(LEDB, LOW);
        
        while(true){

            Serial.println("error somethong went wrong restart the board");
            delay(1000);

        };

        break;
    }

};


