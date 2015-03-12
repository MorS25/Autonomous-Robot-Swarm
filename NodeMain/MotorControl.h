#ifndef MotorControl_h
#define MotorControl_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//Initialize PIN VALS for Motor Control
#define MOTOR_ONE_ENABLE      6
#define MOTOR_ONE_SET         8
#define MOTOR_TWO_ENABLE      5
#define MOTOR_TWO_SET         7
#define MOTOR_THREE_ENABLE    10
#define MOTOR_THREE_SET       12
#define MOTOR_FOUR_ENABLE     11
#define MOTOR_FOUR_SET        13

//Initialize PIN VALS for motor encoders
#define MOTOR_ONE_ENCODER     A0
#define MOTOR_TWO_ENCODER     A1
#define MOTOR_THREE_ENCODER   A2
#define MOTOR_FOUR_ENCODER    A3

class MotorControl {
  public:
    MotorControl(int MOTOR_SPEED);
    void DriveForward();
    void DriveBackward();
    void DriveLeft();
    void DriveRight();
    void RotateLeft();
    void RotateRight();
    void DriveStop();

  private:
    //Variable to control MOTOR SPEED
    int motorSpeed;
};

#endif
