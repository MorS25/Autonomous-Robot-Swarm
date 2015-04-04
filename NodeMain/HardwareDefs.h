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
  TEST,
  
  USER_CONTROL,
  USER_CONTROL_RETURN,
  
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
  char pastMoves[100];
  int moveTimes[100];
  
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
