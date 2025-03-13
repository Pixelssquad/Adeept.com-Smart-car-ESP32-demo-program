#ifndef CAR_H
#define CAR_H

#include <Arduino.h>
#include <PCA9685.h>

void PCA9685_Close_Com_Address(void);//Close the PCA9685 public address

/////////////////////PCA9685 drive area//////////////////////////////////////
void PCA9685_Setup(void);              //servo initialization
void Servo_1_Angle(float angle);     //Set the rotation parameters of servo 1, and the parameters are 0-180 degrees
void Servo_2_Angle(float angle);     //Set the rotation parameters of servo 2, and the parameters are 0-180 degrees
void Servo_2_Angle(float angle);
void Servo_Sweep(int servo_id, int angle_start, int angle_end);//Servo sweep function;



#endif
