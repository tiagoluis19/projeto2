//This sketch is used to calibrate the raw magnetometer and accelerometer data provided by the Adafruit LSM303DHLC sensor. With the help of these measured values one obtains
//a tilt compensated digital compass.
//A description of the calculation steps is given in the ST Application Note AN4508
//https://www.st.com/content/ccc/resource/technical/document/application_note/a0/f0/a0/62/3b/69/47/66/DM00119044.pdf/files/DM00119044.pdf/jcr:content/translations/en.DM00119044.pdf
//For the procedure for calibrating the sensor, see https://diydrones.com/profiles/blogs/advanced-hard-and-soft-iron-magnetometer-calibration-for-dummies
//or https://www.instructables.com/id/Easy-hard-and-soft-iron-magnetometer-calibration/
//Use my sketch file LSM303DHLC_Acc-and_Mag_Raw_Measurements_201218 for calibrating.
//Thanks to Yury Matselenak and Chris H for their contributions!

#include <WiFi.h>
#include "Wire.h"

#define ICM20948_ADDR 0x68
#include <ICM20948_WE.h>
ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);


float Mx, My, Mz; // Raw Magnetometer measurements
float Mxc, Myc, Mzc; // Calibrated Magnetometer measurements
float Mxcn, Mycn, Mzcn; // Normalized Magnetometer measurements


float Ax, Ay, Az; // Raw Accelerometer measurments
float Axc, Ayc, Azc;  // Calibrated Accelerometer mesurements
float Axcn, Aycn, Azcn; // Normalized Accelerometer measurements


float norm_a, norm_m;

double pitch, roll;
double pitch_print, roll_print;
double tiltcnf;

double Xh, Yh;  // Tilt compensated values for heading calculation
float headingct; // Calibrated and tilt compensated heading


//calibrated_values[3] is the global array where the calibrated data will be placed
//calibrated_values[3]: [0]=Xc, [1]=Yc, [2]=Zc
float calibrated_mag_values[3];
float calibrated_acc_values[3];

float alpha = 0.25; // Low-Pass Filtercoefficient

// Filtered Magnetometer measurements
float Mxcnf = 0;
float Mycnf = 0;
float Mzcnf = 0;

// Filtered Accelerometer measurements
float Axcnf = 0;
float Aycnf = 0;
float Azcnf = 0;


void setup()
{
  Serial.begin(115200);
  Wire.begin();

  WiFi.softAP("Turret", "idonthateyou");

  if(!myIMU.init()){
    Serial.println("ICM20948 does not respond");
  }
  else{
    Serial.println("ICM20948 is connected");
  }

  if(!myIMU.initMagnetometer()){
    Serial.println("Magnetometer does not respond");
  }
  else{
    Serial.println("Magnetometer is connected");
  }
}

void loop()
{
  xyzFloat gValue;
  xyzFloat gyr;
  xyzFloat magValue;
  xyzFloat accRaw;
  
  myIMU.readSensor();
  myIMU.getGValues(&gValue);
  myIMU.getAccRawValues(&accRaw);
  myIMU.getGyrValues(&gyr);
  myIMU.getMagValues(&magValue);
  float temp = myIMU.getTemperature();
  float resultantG = myIMU.getResultantG(&gValue);

  float values_from_magnetometer[3] = {magValue.x, magValue.y, magValue.z};
  float values_from_accelerometer[3] = {accRaw.x, accRaw.y, accRaw.z};


  //transformation_mag(values_from_magnetometer);

  Mxc = values_from_magnetometer[0];
  Myc = values_from_magnetometer[1];
  Mzc = values_from_magnetometer[2];

  //getRawValuesAcc();

  //transformation_acc(values_from_accelerometer);

  Axc = values_from_accelerometer[0];
  Ayc = values_from_accelerometer[1];
  Azc = values_from_accelerometer[2];

  //  Normalizing
  norm_m = sqrt(sq(Mxc) + sq(Myc) + sq(Mzc)); //original code did not appear to normalize, and this seems to help
  Mxcn = Mxc / norm_m;
  Mycn = Myc / norm_m;
  Mzcn = Mzc / norm_m;

  norm_a = sqrt(sq(Axc) + sq(Ayc) + sq(Azc)); //original code did not appear to normalize, and this seems to help
  Axcn = Axc / norm_a;
  Aycn = Ayc / norm_a;
  Azcn = Azc / norm_a;


  // Low-Pass filter magnetometer
  Mxcnf = Mxcn * alpha + (Mxcnf * (1.0 - alpha));
  Mycnf = Mycn * alpha + (Mycnf * (1.0 - alpha));
  Mzcnf = Mzcn * alpha + (Mzcnf * (1.0 - alpha));

  // Low-Pass filter accelerometer
  Axcnf = Axcn * alpha + (Axcnf * (1.0 - alpha));
  Aycnf = Aycn * alpha + (Aycnf * (1.0 - alpha));
  Azcnf = Azcn * alpha + (Azcnf * (1.0 - alpha));


  // Calculating pitch and roll angles following Application Note
  pitch = (double) asin((double) - Axcnf);
  pitch_print = pitch * 180 / PI;
  roll = (double) asin((double) Aycnf / cos((double) pitch));
  roll_print = roll * 180 / PI;


  //  Calculating heading with calibrated measurements not tilt compensated
  float headingc = (double)atan2((double)Myc, (double)Mxc) * 180 / PI;
  if (headingc < 0) {
    headingc = 360 + headingc;
  }

  //  Calculating tilt compensated heading
  Xh = Mxcnf * cos((double)pitch) + Mzcnf * sin((double)pitch);
  Yh = Mxcnf * sin((double)roll) * sin((double)pitch) + Mycnf * cos((double)roll) - Mzcnf * sin((double)roll) * cos((double)pitch);
  headingct = (atan2(Yh, Xh)) * 180 / PI;
  if (headingct < 0) {
    headingct = 360 + headingct;
  }


  //Calculating Tilt angle in degrees
  tiltcnf = (double)atan2((double)fabs(Azcnf), (double)Axcnf) * 180 / PI;

  Serial.flush();

  //// Display raw magnetometer values
  //Serial.println("Magnetometer raw measurements");
  //Serial.print("Mx: "); Serial.print(Mx); Serial.print("; ");
  //Serial.print("My: "); Serial.print(My); Serial.print("; ");
  //Serial.print("Mz: "); Serial.println(Mz);
//
  //// Display calibrated magnetometer values
  //Serial.println("Magnetometer calibrated measurements");
  //Serial.print("Mxc: "); Serial.print(Mxc); Serial.print("; ");
  //Serial.print("Myc: "); Serial.print(Myc); Serial.print("; ");
  //Serial.print("Mzc: "); Serial.println(Mzc);
  //Serial.println("--------------------------------------");
//
  //// Display raw accelerometer measurements in milliG
  //Serial.println("Accelerometer raw measurements");
  //Serial.print("Ax: "); Serial.print(Ax); Serial.print("; ");
  //Serial.print("Ay: "); Serial.print(Ay); Serial.print("; ");
  //Serial.print("Az: "); Serial.println(Az);
//
  //// Display calibrated accelerometer measurements in milliG
  //Serial.println("Accelerometer calibrated measurements");
  //Serial.print("Axc: "); Serial.print(Axc); Serial.print("; ");
  //Serial.print("Ayc: "); Serial.print(Ayc); Serial.print("; ");
  //Serial.print("Azc: "); Serial.println(Azc);
  //Serial.println("--------------------------------------");
//
  // Display Heading in degrees North = 0Â°--> 360Â° turning clockwise
  Serial.print ("Heading calibrated: "); Serial.println (headingc);
  Serial.print ("Heading tilt compensated: "); Serial.println (headingct);
  Serial.println("--------------------------------------");


  // Display Tilt angle in degrees
  Serial.print("Tilt raw: "); Serial.println((double)atan2((double)fabs(Az), (double)Ax) * 180 / PI);
  Serial.print("Tilt calibrated: "); Serial.println(tiltcnf);

  // Display Pitch and Roll angles in degrees
  Serial.print ("Pitch: "); Serial.println (pitch_print);
  Serial.print ("Roll: "); Serial.println (roll_print);
  Serial.println("--------------------------------------");
  Serial.println();


  delay(400);
}