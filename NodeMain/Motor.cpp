#include "Motor.h"

Motor::Motor(int SPEED) {
  pinMode(MOTOR_ONE_ENABLE, OUTPUT);
  pinMode(MOTOR_ONE_SET, OUTPUT);
  pinMode(MOTOR_TWO_ENABLE, OUTPUT);
  pinMode(MOTOR_TWO_SET, OUTPUT);
  //pinMode(MOTOR_THREE_ENABLE, OUTPUT);
  //pinMode(MOTOR_THREE_SET, OUTPUT);
  pinMode(MOTOR_FOUR_ENABLE, OUTPUT);
  pinMode(MOTOR_FOUR_SET, OUTPUT);

  motorSpeed = SPEED;
};

void Motor::DriveForward(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  MOTOR_TWO_RUN(motorSpeed);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}

void Motor::DriveBackward(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, LOW);
  MOTOR_TWO_RUN(motorSpeed);
  digitalWrite(MOTOR_TWO_SET, LOW);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, LOW);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}

void Motor::DriveLeft(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, LOW);
  MOTOR_TWO_RUN(motorSpeed);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, LOW);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}

void Motor::DriveRight(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  MOTOR_TWO_RUN(motorSpeed);
  digitalWrite(MOTOR_TWO_SET, LOW);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}

void Motor::RotateLeft(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, LOW);
  MOTOR_TWO_RUN(motorSpeed);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}

void Motor::RotateRight(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  MOTOR_TWO_RUN(motorSpeed);
  digitalWrite(MOTOR_TWO_SET, LOW);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, LOW);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}

void Motor::DriveStop(void) {
  digitalWrite(MOTOR_ONE_ENABLE, LOW);
  digitalWrite(MOTOR_ONE_SET, LOW);
  digitalWrite(MOTOR_TWO_ENABLE, LOW);
  digitalWrite(MOTOR_TWO_SET, LOW);
  digitalWrite(MOTOR_THREE_ENABLE, LOW);
  digitalWrite(MOTOR_THREE_SET, LOW);
  digitalWrite(MOTOR_FOUR_ENABLE, LOW);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
