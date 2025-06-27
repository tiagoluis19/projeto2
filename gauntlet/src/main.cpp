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
    Serial.begin(9600);
    analogReadResolution(12); //set the resolution of the analog read to 12 bits
    while (!Serial);

   

    if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }
     Serial.println(IMU.accelerationSampleRate()); //set the sample rate of the IMU to 100Hz
    Serial.println(IMU.gyroscopeSampleRate());

    pinMode(A1, INPUT); //pointer   finger
    pinMode(A3, INPUT); //middle    finger 
    pinMode(A5, INPUT); //ring      finger 
    pinMode(A7, INPUT); //pinky     finger 

    pinMode(LEDR, OUTPUT); //LED for visual feedback
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);


};

Recorder recorder = {0}; //initial state is idle

void loop(){

int limit = 2400;
int user_time=100;//in milliseconds



    switch (recorder.state){
    case 0: //idle state waits for user input to start recording getures
            //indicated by green LED
        digitalWrite(LEDG, HIGH); //turn on green LED
       
          
        if(analogRead(A1)<=limit)
            recorder.state = 1; //if pointer finger is up then start the recording session
        break;

    case 1: //recording state records the gestures and transmits them via UART
            //indicated by red LED
         //delay to give time to the user

        
        digitalWrite(LEDR, HIGH); //turn on red LED
        
        

        

        //read the IMU data
        

        IMU.readAcceleration(ax, ay, az);
        IMU.readGyroscope(gx, gy, gz);  // attention must me in radians

        Serial.print(ax);Serial.print(";");Serial.print(ay);Serial.print(";");Serial.print(az);Serial.print(";");Serial.print(gx);Serial.print(";");Serial.print(gy);Serial.print(";");Serial.print(gz);Serial.println(";");

        if(analogRead(A7)<=limit){ //if the user sends the stop command then stop the recording session
            recorder.state = 0; 


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
}


