#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <VirtualWire.h>

SoftwareSerial mySerial(4, 9);
Adafruit_GPS GPS(&mySerial);

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
  Serial.begin(115200);

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

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  delay(1000);
  // Ask for firmware version
  Serial.println(PMTK_Q_RELEASE);
}

//Timer for GPS Module
uint32_t timer = millis();

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
  int 
  
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
        if (buf[i] == 93) {
          endOfData = true;
          break;
        }
      }
    }

    //Parse data in between
    if (startOfData && endOfData) {

    }

  } //End of main if-statement
}

void GetGPSData(void) {
  // read data from the GPS in the 'main loop'
  char c = GPS.read();

  // if a sentence is received, we can check the checksum, parse it
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 500) {
    timer = millis();
    Serial.print("Location: ");
    Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
    Serial.print(", ");
    Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
  }
}
