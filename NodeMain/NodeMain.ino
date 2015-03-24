#include <VirtualWire.h>
#include "Motor.h"

//PREPROCESSOR
//Initialize Pins for RF Modules
#define RECEIVE_PIN           2

//Define individual node speeds
#define NODE_ONE              245
#define NODE_TWO              255
#define NODE_THREE            255

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
  Serial.begin(9600);
  
  vw_set_tx_pin(3);
  vw_set_rx_pin(2);
  vw_set_ptt_pin(4);
  vw_set_ptt_inverted(true);
  vw_setup(4000);

  vw_rx_start();

  //Initialize all Node Data variable
  nodeData.nodeState = WAITING_PC_CMD;
  nodeData.gpsLat = 0;
  nodeData.gpsLong = 0;
}

void loop(void) {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    // Message with a good checksum received, print it.
    Serial.print("Got: ");

    for (i = 0; i < buflen; i++)
    {
      Serial.print(buf[i], DEC);
      Serial.print(' ');
    }
    Serial.println();
  }
}
