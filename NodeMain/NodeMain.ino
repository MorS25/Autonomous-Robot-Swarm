#include <SoftwareSerial.h>
#include <VirtualWire.h>

#include "MotorControl.h"

/*  Functions To Control Motors, Must pass speed for individual Nodes
 *  Driveforward(int motorSpeed);
 *  DriveBackward(int motorSpeed);
 *  DriveLeft(int motorSpeed);
 *  DriveRight(int motorSpeed);
 *  RotateLeft(int motorSpeed);
 *  RotateRight(int motorSpeed);
 *  DriveStop(int motorSpeed);
*/
MotorControl motor;  //Motors are auto-initialized as well as pins on Arduino

//Variables to set EXACT speed per Node
#define NODE_ONE              150
#define NODE_TWO              255
#define NODE_THREE            255

//Initialize pins for Serial Communication
#define RECIEVE_PIN           2
#define TRANSMIT_PIN          3

void setup() {
  //Initialize all pins for Serial Communications
  Serial.begin(115200);
  //vw_set_tx_pin(TRANSMIT_PIN);
  vw_set_rx_pin(RECIEVE_PIN);
  vw_set_ptt_inverted(true);
  vw_setup(4000);
  vw_rx_start();
}

void loop() {
  ;
}
