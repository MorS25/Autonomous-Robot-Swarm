#include <VirtualWire.h>

#include "HardwareDefs.h"
#include "Motor.h"

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

NodeData nodeData;

//Function Prototypes
void ParseData(void);

void setup(void) {
  Serial.begin(9600);

  //Initialize pins for serial communication
  vw_set_tx_pin(3);
  vw_set_rx_pin(2);
  vw_set_ptt_pin(4);
  vw_set_ptt_inverted(true);
  vw_setup(4000);
  vw_rx_start();

  //Initialize all Node Data variable
  nodeData.nodeState = PC_DATA_PARSE;
  nodeData.gpsLat = 0;
  nodeData.gpsLong = 0;

  //Initialize initial motor states
  motor.DriveStop();
}

void loop(void) {
  switch (nodeData.nodeState) {
    case PC_DATA_PARSE:
      motor.DriveForward();
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
}

void ParseData(void) {
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
