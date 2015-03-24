#ifndef HardwareDefs_h
#define HardwareDefs_h

//Initialize Pins for RF Modules
#define RECEIVE_PIN           2
#define TRANSMIT_PIN          3
#define TRANSMIT_ENABLE_PIN   A0

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
