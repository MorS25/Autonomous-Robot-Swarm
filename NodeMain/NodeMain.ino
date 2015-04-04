/*
    w  ->  Forward
    a  ->  Left
    s  ->  Backward
    d  ->  Right
    q  ->  Stop
    e  ->  CollectData
    r  ->  Return
*/

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
#define NODE_ONE              230
#define NODE_TWO              255
#define NODE_THREE            255

//ALL VARIABLES
Motor motor(NODE_TWO);
NodeData nodeData;

int moveIndex = 1;
char pastMove = ' ';
char nextMove = ' ';

int returnMoveIndex;

//Function Prototypes
char GetInput(void);
void ResetUserControlTimer(void);

//void ParseData(void);
//void GetGPSData(void);
//bool InitGPSModule(void);
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

  //Initialize initial motor states3
  motor.DriveStop();

  //Initialize initial node state
  nodeData.nodeState = INIT_NODE;

  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  Serial.println("Connecting...");  //Debugging purposes
}

//Timer for GPS Module
uint32_t timer = millis();

void loop(void) {
  switch (nodeData.nodeState) {
    case TEST:
      motor.DriveStop();
      break;
    case INIT_NODE:
      //Initialize node data struct
      nodeData.pingDistance = 0;

      nodeData.destLatDeg = 0;
      nodeData.destLatMin = 0;
      nodeData.destLongDeg = 0;
      nodeData.destLongMin = 0;

      nodeData.gpsLatDeg = 0;
      nodeData.gpsLatMin = 0;
      nodeData.gpsLongDeg = 0;
      nodeData.gpsLongMin = 0;

      for (int i = 0; i < 20; i++) {
        nodeData.pastMoves[i] = ' ';
        nodeData.moveTimes[i] = 0;
      }

      nodeData.timer = millis();

      nodeData.nodeState = USER_CONTROL;
      //nodeData.nodeState = TEST;
      break;

    case USER_CONTROL:
      nextMove = GetInput();

      //If next move is the same as previous move then jump iteration
      if (nextMove != pastMove) {
        pastMove = nextMove;
        switch (nextMove) {
          case 'w':
            ResetUserControlTimer();
            motor.DriveForward();
            break;
          case 'a':
            ResetUserControlTimer();
            motor.DriveLeft();
            break;
          case 's':
            ResetUserControlTimer();
            motor.DriveBackward();
            break;
          case 'd':
            ResetUserControlTimer();
            motor.DriveRight();
            break;
          case 'q':
            ResetUserControlTimer();
            motor.DriveStop();
            break;
          case 'e':
            break;
          case 'r':
            ResetUserControlTimer();
            nodeData.nodeState = USER_CONTROL_RETURN;
            motor.DriveStop();
            break;
        }
      }
      break;

    case USER_CONTROL_RETURN:
      vw_send((uint8_t *)nodeData.pastMoves, strlen(nodeData.pastMoves));
      vw_wait_tx();
      vw_send((uint8_t *)nodeData.pastMoves, strlen(nodeData.pastMoves));
      vw_wait_tx();

      //Start by searching for empty char
      for (int i = 1; i < 20; i++) {
        if (nodeData.pastMoves[i] == ' ') {
          returnMoveIndex = i - 1;
          i = 20;  //Exit out of for loop
        }
      }

      //Loop through array backwards, and reverse motor directions
      for (; returnMoveIndex > 0; returnMoveIndex--) {
        Serial.print(nodeData.pastMoves[returnMoveIndex]);
        Serial.print("  ->  ");
        Serial.println(nodeData.moveTimes[returnMoveIndex]);

        if (nodeData.pastMoves[returnMoveIndex] == 'w')
          motor.DriveBackward();
        else if (nodeData.pastMoves[returnMoveIndex] == 'a')
          motor.DriveRight();
        else if (nodeData.pastMoves[returnMoveIndex] == 's')
          motor.DriveForward();
        else if (nodeData.pastMoves[returnMoveIndex] == 'd')
          motor.DriveLeft();

        //Skip right over the 'q' type command, since this would only make the robot pause
        //for no reason while traversing back

        //Delay for same amount moved in converse direction
        delay(nodeData.moveTimes[returnMoveIndex]);
        motor.DriveStop();
      }
      
      nodeData.nodeState = USER_CONTROL;
      break;

      //    case PC_DATA_PARSE:
      //      GetGPSData();
      //      ParseData();
      //      break;
      //    case ORIGIN_TO_DESTINATION:
      //      break;
      //    case COLLECT_DATA:
      //      break;
      //    case DESTINATION_TO_ORIGIN:
      //      break;
      //    case NODE_DATA_TO_PC:
      //      break;
  } //End of Switch-Case Statement
}

//----  HELPER FUNCTIONS  ----//
//This functions is specifically required to make sure we have valid commands
char GetInput(void) {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  //If message is received
  if (vw_get_message(buf, &buflen)) {
    if (buf[1] == 'w') {
      nodeData.pastMoves[moveIndex] = 'w';
      return 'w';
    }
    else if (buf[1] == 'a') {
      nodeData.pastMoves[moveIndex] = 'a';
      return 'a';
    }
    else if (buf[1] == 's') {
      nodeData.pastMoves[moveIndex] = 's';
      return 's';
    }
    else if (buf[1] == 'd') {
      nodeData.pastMoves[moveIndex] = 'd';
      return 'd';
    }
    else if (buf[1] == 'q') {
      nodeData.pastMoves[moveIndex] = 'q';
      return 'q';
    }
    else if (buf[1] == 'e') {
      motor.DriveStop();
      //CALL DATA COLLECTION FUNCTION
    }
    else if (buf[1] == 'r') {
      return 'r';
    }
  }
}

void ResetUserControlTimer(void) {
  nodeData.moveTimes[moveIndex - 1] = abs(millis() - timer) / 10;
  ++moveIndex;
  nodeData.timer = millis();
}

/* This function does NOT require the incoming data to be checked for errors
 * as that is ALL handled inside the Transmit.ino file
 */
/*
void ParseData(void) {
 uint8_t buf[VW_MAX_MESSAGE_LEN];
 uint8_t buflen = VW_MAX_MESSAGE_LEN;

 //If message is received
 if (vw_get_message(buf, &buflen)) {
   //Printing out array
   for (int i = 0; i < buflen; i++) {
     Serial.print(buf[i]);
     Serial.print(' ');
   }
   Serial.println();

   //HANDLES ALL PARSING OF STRING
   //VERY RUDIMENTARY CODE
   {
     char str1[10];
     char str2[10];
     char str3[10];
     char str4[10];
     char str5[10];
     {
       sprintf(str1, "%c", (char) buf[1]);
       sprintf(str2, "%c", (char) buf[2]);
       strcat(str1, str2);
       nodeData.destLatDeg = atof(str1);
     }
     {
       sprintf(str1, "%c", (char) buf[3]);
       sprintf(str2, "%c", (char) buf[4]);
       sprintf(str3, "%c", (char) buf[5]);
       sprintf(str4, "%c", (char) buf[6]);
       sprintf(str5, "%c", (char) buf[7]);
       strcat(str1, str2);
       strcat(str1, str3);
       strcat(str1, str4);
       strcat(str1, str5);
       nodeData.destLatMin = atof(str1);
     }
     {
       sprintf(str1, "%c", (char) buf[12]);
       sprintf(str2, "%c", (char) buf[13]);
       sprintf(str3, "%c", (char) buf[14]);
       strcat(str1, str2);
       strcat(str1, str3);
       nodeData.destLongDeg = atof(str1);
     }
     {
       sprintf(str1, "%c", (char) buf[15]);
       sprintf(str2, "%c", (char) buf[16]);
       sprintf(str3, "%c", (char) buf[17]);
       sprintf(str4, "%c", (char) buf[18]);
       sprintf(str5, "%c", (char) buf[19]);
       strcat(str1, str2);
       strcat(str1, str3);
       strcat(str1, str4);
       strcat(str1, str5);
       nodeData.destLongMin = atof(str1);
     }
   }

   //    Uncomment for debugging
   //    Serial.println(nodeData.destLatDeg);
   //    Serial.println(nodeData.destLatMin);
   //    Serial.println(nodeData.destLongDeg);
   //    Serial.println(nodeData.destLongMin);
 } //End of outer if-statement
}

bool InitGPSModule(void) {
 char c = GPS.read();

 if (GPS.newNMEAreceived()) {
   if (!GPS.parse(GPS.lastNMEA()))
     return false;
 }

 if (timer > millis())  timer = millis();

 if (!GPS.fix)
   return false;
 return true;
}

void GetGPSData(void) {
 char c = GPS.read();

 if (GPS.newNMEAreceived()) {
   if (!GPS.parse(GPS.lastNMEA()))
     return;
 }

 if (timer > millis())  timer = millis();

 if (GPS.fix) {
   Serial.print(GPS.latitude); Serial.print(GPS.lat);
   Serial.print(", ");
   Serial.print(GPS.longitude); Serial.println(GPS.lon);
 }
}

long GetPingDistance(void) {
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
*/
