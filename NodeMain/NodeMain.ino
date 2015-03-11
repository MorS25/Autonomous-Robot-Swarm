#include <SoftwareSerial.h>
#include <VirtualWire.h>

#include "MotorControl.h"

//Variables to set EXACT speed per Node
#define NODE_ONE              245
#define NODE_TWO              255
#define NODE_THREE            255

/*  Functions To Control Motors, Must pass speed for individual Nodes
 *  Driveforward(int motorSpeed);
 *  DriveBackward(int motorSpeed);
 *  DriveLeft(int motorSpeed);
 *  DriveRight(int motorSpeed);
 *  RotateLeft(int motorSpeed);
 *  RotateRight(int motorSpeed);
 *  DriveStop(int motorSpeed);
 *
 *  Motors are auto-initialized as well as pins on Arduino
 *  Parameter specifies universal NODE motor speed                    */
MotorControl motor(NODE_ONE);

typedef enum {
  WAITING_PC_CMD,
  PC_CMD_PARSE
} NodeState;

void setup() {
  ;
}

void loop() {
  motor.DriveForward();
  delay(10000);
  motor.RotateLeft();
  delay(11700);
}
