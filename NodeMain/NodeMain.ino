#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <VirtualWire.h>

#include "GPSModule.h"
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
  float gpsLat;
  float gpsLong;
} NodeData;

//VARIABLES & OBJECTS
/*  Motors are auto-initialized as well as pins on Arduino
 *  Parameter specifies universal NODE motor speed                    */
MotorControl motor(NODE_ONE);
//Initializes node Serial communication
NodeSerial serial;
//Declaration of NodeData
NodeData nodeData;
//
GPSModule gpsModule;

void setup(void) {
  Serial.begin(9600);

  //Initialize all Node Data variables
  nodeData.nodeState = WAITING_PC_CMD;
  nodeData.gpsLat = 0;
  nodeData.gpsLong = 0;
  
  delay(1000);
}

void loop(void) {
  gpsModule.GetData();
  delay(30000);
  /*
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;
    // Message with a good checksum received, print it.
    Serial.print("Got: ");

    for (i = 0; i < buflen; i++)
    {
      String a = String(buf[i], DEC);
      Serial.print(buf[i], HEX);
      Serial.print(' ');
      Serial.print(a);
    }
    Serial.println();
  }
  */
}
