#include "MotorControl.h"

MotorControl::MotorControl(int MOTOR_SPEED) {
  //Initialize all Motor Control Pins
  pinMode(MOTOR_ONE_ENABLE, OUTPUT);
  pinMode(MOTOR_ONE_SET, OUTPUT);
  pinMode(MOTOR_TWO_ENABLE, OUTPUT);
  pinMode(MOTOR_TWO_SET, OUTPUT);
  pinMode(MOTOR_THREE_ENABLE, OUTPUT);
  pinMode(MOTOR_THREE_SET, OUTPUT);
  pinMode(MOTOR_FOUR_ENABLE, OUTPUT);
  pinMode(MOTOR_FOUR_SET, OUTPUT);

  //Initialize all pins for motor encoders
  /*
  pinMode(MOTOR_ONE_ENCODER, INPUT);
  pinMode(MOTOR_TWO_ENCODER, INPUT);
  pinMode(MOTOR_THREE_ENCODER, INPUT);
  pinMode(MOTOR_FOUR_ENCODER, INPUT);
  */

  motorSpeed = MOTOR_SPEED;
}

void MotorControl::DriveForward(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  analogWrite(MOTOR_TWO_ENABLE, motorSpeed);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}
void MotorControl::DriveBackward(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, LOW);
  analogWrite(MOTOR_TWO_ENABLE, motorSpeed);
  digitalWrite(MOTOR_TWO_SET, LOW);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, LOW);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
void MotorControl::DriveLeft(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, LOW);
  analogWrite(MOTOR_TWO_ENABLE, motorSpeed);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, LOW);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}
void MotorControl::DriveRight(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  analogWrite(MOTOR_TWO_ENABLE, motorSpeed);
  digitalWrite(MOTOR_TWO_SET, LOW);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
void MotorControl::RotateLeft(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, LOW);
  analogWrite(MOTOR_TWO_ENABLE, motorSpeed);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
void MotorControl::RotateRight(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  analogWrite(MOTOR_TWO_ENABLE, motorSpeed);
  digitalWrite(MOTOR_TWO_SET, LOW);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, LOW);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}
void MotorControl::DriveStop(void) {
  digitalWrite(MOTOR_ONE_ENABLE, LOW);
  digitalWrite(MOTOR_ONE_SET, LOW);
  digitalWrite(MOTOR_TWO_ENABLE, LOW);
  digitalWrite(MOTOR_TWO_SET, LOW);
  digitalWrite(MOTOR_THREE_ENABLE, LOW);
  digitalWrite(MOTOR_THREE_SET, LOW);
  digitalWrite(MOTOR_FOUR_ENABLE, LOW);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
