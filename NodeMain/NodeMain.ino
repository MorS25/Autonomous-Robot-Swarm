#include "Motor.h"

//PREPROCESSOR
//Initialize Pins for RF Modules
#define RECEIVE_PIN           2

//Define individual node speeds
#define NODE_ONE              245
#define NODE_TWO              255
#define NODE_THREE            255

//Initialize all motors
//PinMode is set in constructor
Motor motor(NODE_ONE);

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
  float gpsLat;
  float gpsLong;
} NodeData;
NodeData nodeData;

void setup(void) {
  Serial.begin(115200);

  //Initialize all Node Data variables
  nodeData.nodeState = WAITING_PC_CMD;
  nodeData.gpsLat = 0;
  nodeData.gpsLong = 0;
}

void loop(void) {
  ;
}
