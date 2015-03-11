#include "MotorControl.h"

MotorControl::MotorControl() {
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
  pinMode(MOTOR_ONE_ENCODER, INPUT);
  pinMode(MOTOR_TWO_ENCODER, INPUT);
  pinMode(MOTOR_THREE_ENCODER, INPUT);
  pinMode(MOTOR_FOUR_ENCODER, INPUT);
}

void MotorControl::DriveForward(int motorSpeed) {
  analogWrite(MOTOR_ONE_ENABLE, HIGH);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  analogWrite(MOTOR_TWO_ENABLE, HIGH);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  analogWrite(MOTOR_THREE_ENABLE, HIGH);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  analogWrite(MOTOR_FOUR_ENABLE, HIGH);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}
void MotorControl::DriveBackward(int motorSpeed) {
  analogWrite(MOTOR_ONE_ENABLE, HIGH);
  digitalWrite(MOTOR_ONE_SET, LOW);
  analogWrite(MOTOR_TWO_ENABLE, HIGH);
  digitalWrite(MOTOR_TWO_SET, LOW);
  analogWrite(MOTOR_THREE_ENABLE, HIGH);
  digitalWrite(MOTOR_THREE_SET, LOW);
  analogWrite(MOTOR_FOUR_ENABLE, HIGH);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
void MotorControl::DriveLeft(int motorSpeed) {
  analogWrite(MOTOR_ONE_ENABLE, HIGH);
  digitalWrite(MOTOR_ONE_SET, LOW);
  analogWrite(MOTOR_TWO_ENABLE, HIGH);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  analogWrite(MOTOR_THREE_ENABLE, HIGH);
  digitalWrite(MOTOR_THREE_SET, LOW);
  analogWrite(MOTOR_FOUR_ENABLE, HIGH);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}
void MotorControl::DriveRight(int motorSpeed) {
  digitalWrite(MOTOR_ONE_ENABLE, HIGH);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  digitalWrite(MOTOR_TWO_ENABLE, HIGH);
  digitalWrite(MOTOR_TWO_SET, LOW);
  digitalWrite(MOTOR_THREE_ENABLE, HIGH);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  digitalWrite(MOTOR_FOUR_ENABLE, HIGH);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
void MotorControl::RotateLeft(int motorSpeed) {
  digitalWrite(MOTOR_ONE_ENABLE, HIGH);
  digitalWrite(MOTOR_ONE_SET, LOW);
  digitalWrite(MOTOR_TWO_ENABLE, HIGH);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  digitalWrite(MOTOR_THREE_ENABLE, HIGH);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  digitalWrite(MOTOR_FOUR_ENABLE, HIGH);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
void MotorControl::RotateRight(int motorSpeed) {
  digitalWrite(MOTOR_ONE_ENABLE, HIGH);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  digitalWrite(MOTOR_TWO_ENABLE, HIGH);
  digitalWrite(MOTOR_TWO_SET, LOW);
  digitalWrite(MOTOR_THREE_ENABLE, HIGH);
  digitalWrite(MOTOR_THREE_SET, LOW);
  digitalWrite(MOTOR_FOUR_ENABLE, HIGH);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}
void MotorControl::DriveStop() {
  digitalWrite(MOTOR_ONE_ENABLE, LOW);
  digitalWrite(MOTOR_ONE_SET, LOW);
  digitalWrite(MOTOR_TWO_ENABLE, LOW);
  digitalWrite(MOTOR_TWO_SET, LOW);
  digitalWrite(MOTOR_THREE_ENABLE, LOW);
  digitalWrite(MOTOR_THREE_SET, LOW);
  digitalWrite(MOTOR_FOUR_ENABLE, LOW);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
