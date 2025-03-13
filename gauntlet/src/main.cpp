#include <Arduino.h>
#include "Arduino_LSM9DS1.h"

//leitura dos dados GUARDAR O TERMINAL EM CSV

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, World!");
  IMU.begin();
  //4 pinos input dos halls
  //pinos para led laser e power bank module

  Serial.println("Timestamp,Accel_X,Accel_Y,Accel_Z,Gyro_X,Gyro_Y,Gyro_Z");
}



void loop() {

  float ax, ay, az; //accelerometer data
  float gx, gy, gz; //gyroscope data

  static unsigned long startTime = millis();
  
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      IMU.readAcceleration(ax, ay, az);
      IMU.readGyroscope(gx, gy, gz);

      unsigned long timestamp = millis() - startTime;
      
      Serial.print(timestamp);
      Serial.print(",");
      Serial.print(ax, 6); Serial.print(",");
      Serial.print(ay, 6); Serial.print(",");
      Serial.print(az, 6); Serial.print(",");
      Serial.print(gx, 6); Serial.print(",");
      Serial.print(gy, 6); Serial.print(",");
      Serial.println(gz, 6);
  }

  delay(10); // Adjust sampling rate (100 Hz) //tempo de cooldown entre gestos

 
}


