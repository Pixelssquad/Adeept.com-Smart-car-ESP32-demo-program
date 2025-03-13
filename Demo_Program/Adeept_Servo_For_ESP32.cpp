#include <Arduino.h>
#include "Adeept_Servo_For_ESP32.h"



/////////////////////PCA9685 drive area///////////////////////////////////
#define PCA9685_SDA 13         //Define SDA pins
#define PCA9685_SCL 14         //Define SCL pins
#ifndef PCA9685_ADDRESS
#define PCA9685_ADDRESS   0x40
#endif
#define SERVO_FREQUENCY    50        //Define the operating frequency of servo
#define PCA9685_CHANNEL_0  0         //Define PCA9685 channel to control servo 1
#define PCA9685_CHANNEL_1  1         //Define the PCA9685 channel to control servo 2
#define PCA9685_CHANNEL_2  2         //Define the PCA9685 channel to control servo 3
#define SERVO_MIDDLE_POINT 1500      //Define the middle position of the servo   
#define MOTOR_SPEED_MIN   -4095      //Define a minimum speed limit for wheels
#define MOTOR_SPEED_MAX   4095       //Define a maximum speed limit for wheels
#define PIN_MOTOR_M1_IN1  15         //Define the positive pole of M1
#define PIN_MOTOR_M1_IN2  14         //Define the negative pole of M1
#define PIN_MOTOR_M2_IN1  9          //Define the positive pole of M2
#define PIN_MOTOR_M2_IN2  8          //Define the negative pole of M2
#define PIN_MOTOR_M3_IN1  12         //Define the positive pole of M3
#define PIN_MOTOR_M3_IN2  13         //Define the negative pole of M3
#define PIN_MOTOR_M4_IN1  10         //Define the positive pole of M4
#define PIN_MOTOR_M4_IN2  11         //Define the negative pole of M4

PCA9685 pca9685;//Instantiate a PCA9685 object

//PCA9685 initialization
void PCA9685_Setup(void)
{
  Wire.begin(PCA9685_SDA, PCA9685_SCL);  
  
  Wire.beginTransmission(PCA9685_ADDRESS);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  
  pca9685.setupSingleDevice(Wire, PCA9685_ADDRESS);
  pca9685.setToFrequency(SERVO_FREQUENCY);
}

//Set the rotation parameters of servo 1, and the parameters are 0-180 degrees
void Servo_1_Angle(float angle)
{
  angle = constrain(angle, 0, 180);
  angle = map(angle, 0, 180, 102, 512);
  pca9685.setChannelPulseWidth(PCA9685_CHANNEL_0, int(angle));
}

//Set the rotation parameters of servo 2, and the parameters are 0-180 degrees
void Servo_2_Angle(float angle)
{
  angle = constrain(angle, 0, 180);
  angle = map(angle, 0, 180, 102, 512);
  pca9685.setChannelPulseWidth(PCA9685_CHANNEL_1, int(angle));
}

// Set the rotation parameters of servo 2, and the parameters are 0-180 degrees
void Servo_3_Angle(float angle)
{
  angle = constrain(angle, 0, 180);
  angle = map(angle, 0, 180, 102, 512);
  pca9685.setChannelPulseWidth(PCA9685_CHANNEL_2, int(angle));
}

//Servo sweep function
void Servo_Sweep(int servo_id, int angle_start, int angle_end)
{
    angle_start = constrain(angle_start, 0, 180);
    angle_end = constrain(angle_end, 0, 180);

  if (angle_start > angle_end)
  {
    for (int i = angle_start; i >= angle_end; i--)
    {
      if (servo_id == 1)
        Servo_1_Angle(i);
      else if (servo_id == 2)
        Servo_2_Angle(i);
      else if (servo_id == 3)
        Servo_3_Angle(i);
      delay(10);
    }
  }
  if (angle_start < angle_end)
  {
    for (int i = angle_start; i <= angle_end; i++)
    {
      if (servo_id == 1)
        Servo_1_Angle(i);
      else if (servo_id == 2)
        Servo_2_Angle(i);
      delay(10);
    }
  }
}
