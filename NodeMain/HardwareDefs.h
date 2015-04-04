#ifndef HardwareDefs_h
#define HardwareDefs_h

//Pins for RF Modules
#define RECEIVE_PIN           2
#define TRANSMIT_PIN          3
#define TRANSMIT_ENABLE_PIN   10

#define PING_SENSOR           A4

//Values for ping servo motor
#define SERVO_LEFT_POS        0
#define SERVO_FRONT_POS       90
#define SERVO_RIGHT_POS       180

//DATATYPES
typedef enum {
  TEST,                //Used for debugging
  USER_CONTROL,        //Used for User Control instead of autonomous
  USER_CONTROL_RETURN, //Used for User Control instead of autonomous
  INIT_NODE,
  PC_DATA_PARSE,
  NODE_DATA_CONFIRM,  //Will be put in next version
  NODE_DATA_SET,      //Will be put in next version
  ORIGIN_TO_DESTINATION,
  COLLECT_DATA,
  DESTINATION_TO_ORIGIN,
  NODE_DATA_TO_PC
} NodeState;

typedef struct {
  uint32_t timer;
  char pastMoves[20];
  int moveTimes[20];
  
  long pingDistance;
  
  float destLatDeg;
  float destLatMin;
  float destLongDeg;
  float destLongMin;
  
  float gpsLatDeg;
  float gpsLatMin;
  float gpsLongDeg;
  float gpsLongMin;
  
  NodeState nodeState;
} NodeData;

#endif
