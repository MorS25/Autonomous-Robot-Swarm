#include <VirtualWire.h>
#include "Motor.h"

//PREPROCESSOR
//Initialize Pins for RF Modules
#define RECEIVE_PIN           2

//Define individual node speeds
#define NODE_ONE              255
#define NODE_TWO              255
#define NODE_THREE            255

//Variables for capturing Serial Data
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;

//Initialize all motors
/*
  void DriveForward(void);
  void DriveBackward(void);
  void DriveLeft(void);
  void DriveRight(void);
  void RotateLeft(void);
  void RotateRight(void);
  void DriveStop(void);
*/
Motor motor(NODE_ONE);

//DATATYPES
typedef enum {
  WAITING_PC_DATA,
  DATA_PARSE,
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
NodeData nodeData;

void setup(void) {
  Serial.begin(9600);

  vw_set_tx_pin(3);
  vw_set_rx_pin(2);
  vw_set_ptt_pin(4);
  vw_set_ptt_inverted(true);
  vw_setup(4000);
  vw_rx_start();

  //Initialize all Node Data variable
  nodeData.nodeState = WAITING_PC_DATA;
  nodeData.gpsLat = 0;
  nodeData.gpsLong = 0;

  //Initialize initial motor states
  motor.DriveStop();
}

void loop(void) {
  switch (nodeData.nodeState) {
    case WAITING_PC_DATA_START:
      if (vw_get_message(buf, &buflen))
        ;
      break;

    case WAITING_PC_DATA:
      break;

    case WAITING_PC_DATA_END:
      break;

    case DATA_PARSE:
      break;

    case NODE_DATA_CONFIRM:
      break;

    case NODE_DATA_SET:
      break;

    case ORIGIN_TO_DESTINATION:
      break;

    case COLLECT_DATA:
      break;

    case DESTINATION_TO_ORIGIN:
      break;

    case NODE_DATA_TO_PC:
      break;
  }

void ParseData(){
  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    for (int i = 0; i < buflen; i++)
    {
      Serial.print(buf[i]);
      Serial.print(' ');
    }
    Serial.println();
  }
}
