#include <SoftwareSerial.h>
#include <VirtualWire.h>

#include "MotorControl.h"
#include "NodeSerial.h"

//PREPROCESSOR
//Define individual node speeds
#define NODE_ONE              245
#define NODE_TWO              255
#define NODE_THREE            255

//DATATYPES
typedef enum {
  WAITING_PC_CMD,
  PC_CMD_PARSE,
  NODE_CMD_CONFIRM,
  NODE_CONFIRMED,
  ORIGIN_TO_DESTINATION,
  COLLECT_DATA,
  DESTINATION_TO_ORIGIN,
  DATA_TO_PC
} NodeState;

//VARIABLES & OBJECTS
/*  Functions To Control Motors, Must pass speed for individual Nodes
 *  Driveforward();
 *  DriveBackward();
 *  DriveLeft(;
 *  DriveRight();
 *  RotateLeft();
 *  RotateRight();
 *  DriveStop();
 *
 *  Motors are auto-initialized as well as pins on Arduino
 *  Parameter specifies universal NODE motor speed                    */
MotorControl motor(NODE_ONE);
NodeSerial serial;

typedef struct{
  static NodeState nodeState;
  static int originCoord;
  static int destinationCoord;
}NodeData;

void setup() {
  NodeData nodeOne = {WAITING_PC_CMD, 0, 0};
}

void loop() {
  Serial.println(nodeOne.nodeState);
  motor.DriveForward();
  delay(10000);
  motor.RotateLeft();
  delay(11700);
}
