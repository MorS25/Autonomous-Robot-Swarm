#include <SoftwareSerial.h>
#include <VirtualWire.h>

#include "MotorControl.h"

MotorControl motor;

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
  motor.DriveStop();

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    String a = String(buf[0], DEC);

    if (a == "119")
      motor.DriveForward(1);
    else if (a == "115")
      motor.DriveBackward(1);
    else if (a == "97")
      motor.DriveLeft(1);
    else if (a == "100")
      motor.DriveRight(1);

    delay(1500);
    motor.DriveStop();

    digitalWrite(A5, LOW);
  }
}
