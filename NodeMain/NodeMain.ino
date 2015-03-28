#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <VirtualWire.h>

//Pin 4 -> RX
//Pin 5 -> TX
SoftwareSerial mySerial(9, 4);
Adafruit_GPS GPS(&mySerial);

#include "HardwareDefs.h"
#include "Motor.h"

//Define individual node speeds
#define NODE_ONE              255
#define NODE_TWO              255
#define NODE_THREE            255

//ALL VARIABLES
Motor motor(NODE_ONE);
NodeData nodeData;

//Function Prototypes
void ParseData(void);
int InitGPSModule(void);
void GetGPSData(void);
long GetPingDistance(void);

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
  nodeData.nodePos = ONE;
  nodeData.gpsLat = 0;
  nodeData.gpsLong = 0;

  //Initialize initial motor states
  motor.DriveStop();

  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  delay(1000);
}

//Timer for GPS Module
uint32_t timer = millis();

void loop(void) {

  switch (nodeData.nodeState) {
    case INIT_NODE:
      //Loop until GPS does not have a fixed location
      while (!InitGPSModule())
        Serial.println("Waiting...");
      //Once fixed location is found change states
      nodeData.nodeState = PC_DATA_PARSE;
      break;

    case PC_DATA_PARSE:
      GetGPSData();
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

int InitGPSModule(void) {
  char c = GPS.read();

  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return STANDARD_ERROR;
  }

  if (timer > millis())  timer = millis();

  if (!GPS.fix)
    return STANDARD_ERROR;
    
  return SUCCESS;
}

void GetGPSData(void) {
  char c = GPS.read();

  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }

  if (timer > millis())  timer = millis();

  if (millis() - timer > 2000) {
    timer = millis();
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);

      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }
  }
}

long GetPingDistance(void){
  long duration;
  
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(PING_SENSOR, OUTPUT);
  digitalWrite(PING_SENSOR, LOW);
  delayMicroseconds(2);
  digitalWrite(PING_SENSOR, HIGH);
  delayMicroseconds(5);
  digitalWrite(PING_SENSOR, LOW);
  
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(PING_SENSOR, INPUT);
  duration = pulseIn(PING_SENSOR, HIGH);
  
  //Return distance in centimeters
  return (duration / 29 / 2);
}
