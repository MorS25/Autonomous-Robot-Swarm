#ifndef HardwareDefs_h
#define HardwareDefs_h

//Pins for RF Modules
#define RECEIVE_PIN           2
#define TRANSMIT_PIN          3
#define TRANSMIT_ENABLE_PIN   10

//Pins for Ping Sensor and corresponding servo
#define PING_SERVO_MOTOR      A0
#define PING_SENSOR           A1

//DATATYPES
typedef enum {
  PC_DATA_PARSE,
  NODE_DATA_CONFIRM,
  NODE_DATA_SET,
  ORIGIN_TO_DESTINATION,
  COLLECT_DATA,
  DESTINATION_TO_ORIGIN,
  NODE_DATA_TO_PC
} NodeState;

typedef struct {
  NodeState nodeState;
  float gpsLat;
  float gpsLong;
} NodeData;

#endif
