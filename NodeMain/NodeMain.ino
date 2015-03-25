#include <VirtualWire.h>

#include "HardwareDefs.h"
#include "Motor.h"

//Define individual node speeds
#define NODE_ONE              255
#define NODE_TWO              255
#define NODE_THREE            255

//Initialize all motors
/*
  void DriveForward(void);
  void DriveBackward(void);
  void DriveLeft(void);
  void DriveRight(void);
  void DriveStop(void);
*/
Motor motor(NODE_ONE);

NodeData nodeData;

//Function Prototypes
void ParseData(void);

void setup(void) {
  Serial.begin(9600);

  //Initialize pins for serial communication
  vw_set_tx_pin(TRANSMIT_PIN);
  vw_set_rx_pin(RECEIVE_PIN);
  vw_set_ptt_pin(TRANSMIT_ENABLE_PIN);
  vw_set_ptt_inverted(false);
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
      motor.DriveStop();
      ParseData();
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
  } //End of Switch-Case Statement

}

void ParseData(void) {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  bool startOfData = false;
  bool endOfData = false;

  //If message is received
  if (vw_get_message(buf, &buflen)) {
    //Printing out array
    for (int i = 0; i < buflen; i++) {
      Serial.print(buf[i]);
      Serial.print(' ');
    }
    Serial.println();

    //Check if first element is start of data
    if (buf[0] == 91)
      startOfData = true;
      
    //Check if end of data element is found
    if (startOfData && !endOfData) {
      for (int i = 0; i < buflen; i++) {
        if (buf[i] == 93)
          endOfData = true;
      }
    }
    
    //Parse data in between
    if(startOfData && endOfData){
      
    }
    
  } //End of main if-statement
}
