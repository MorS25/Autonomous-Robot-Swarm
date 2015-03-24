#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

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

#define MOTOR_TWO_RUN(x) do {                     \
    if(x < 255)                                   \
      digitalWrite(MOTOR_TWO_ENABLE, HIGH);       \
    else                                          \
      analogWrite(MOTOR_TWO_ENABLE, motorSpeed);  \
  } while(0)

class Motor {
  public:
    Motor(int SPEED);
    void DriveForward(void);
    void DriveBackward(void);
    void DriveLeft(void);
    void DriveRight(void);
    void RotateLeft(void);
    void RotateRight(void);
    void DriveStop(void);

  private:
    int motorSpeed;

};

#endif
