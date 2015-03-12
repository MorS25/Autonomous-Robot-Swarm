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
  WAITING_PC_CMD = -9,
  PC_CMD_PARSE,
  NODE_CMD_CONFIRM,
  NODE_CONFIRMED,
  ORIGIN_TO_DESTINATION,
  COLLECT_DATA,
  DESTINATION_TO_ORIGIN,
  DATA_TO_PC
} NodeState;

typedef struct {
  NodeState nodeState;
  int originCoord;
  int destinationCoord;
} NodeData;

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

//Initializes node Serial communication
NodeSerial serial;
//Declaration of NodeData
NodeData nodeData;

void setup() {
  //Initialize all Node Data variables
  nodeData.nodeState = WAITING_PC_CMD;
  nodeData.originCoord = 0;
  nodeData.destinationCoord = 0;
}

void loop() {
  Serial.println(nodeData.nodeState);
  motor.DriveForward();
}
