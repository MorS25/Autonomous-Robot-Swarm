
#include <SoftwareSerial.h>
#include <VirtualWire.h>

//Initialize PIN VALS for Motor Control
#define MOTOR_ONE_ENABLE      6
#define MOTOR_ONE_SET         8
#define MOTOR_TWO_ENABLE      5
#define MOTOR_TWO_SET         7
#define MOTOR_THREE_ENABLE    10
#define MOTOR_THREE_SET       12
#define MOTOR_FOUR_ENABLE     11
#define MOTOR_FOUR_SET        13

//Initialize PIN VALS for motor encoders
#define MOTOR_ONE_ENCODER     A0
#define MOTOR_TWO_ENCODER     A1
#define MOTOR_THREE_ENCODER   A2
#define MOTOR_FOUR_ENCODER    A3

//Variables to set EXACT speed per Node
#define NODE_ONE              150
#define NODE_TWO              255
#define NODE_THREE            255

//Initialize pins for Serial Communication
#define RECIEVE_PIN           2
#define TRANSMIT_PIN          3

void setup() {
  //Initialize all Motor Control Pins
  pinMode(MOTOR_ONE_ENABLE, OUTPUT);
  pinMode(MOTOR_ONE_SET, OUTPUT);
  pinMode(MOTOR_TWO_ENABLE, OUTPUT);
  pinMode(MOTOR_TWO_SET, OUTPUT);
  pinMode(MOTOR_THREE_ENABLE, OUTPUT);
  pinMode(MOTOR_THREE_SET, OUTPUT);
  pinMode(MOTOR_FOUR_ENABLE, OUTPUT);
  pinMode(MOTOR_FOUR_SET, OUTPUT);
  
  //Initialize all pins for motor encoders
  pinMode(MOTOR_ONE_ENCODER, INPUT);
  pinMode(MOTOR_TWO_ENCODER, INPUT);
  pinMode(MOTOR_THREE_ENCODER, INPUT);
  pinMode(MOTOR_FOUR_ENCODER, INPUT);
  
  //Initialize all pins for Serial Communications
  Serial.begin(115200);
  //vw_set_tx_pin(TRANSMIT_PIN);
  vw_set_rx_pin(RECIEVE_PIN);
  vw_set_ptt_inverted(true);
  vw_setup(4000);
  vw_rx_start();
}

void loop() {
  StopDrive();
  
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    String a = String(buf[0], DEC);

    if (a == "119")
      DriveForward();
    else if (a == "115")
      DriveBackward();
    else if (a == "97")
      LeftStrafe();
    else if (a == "100")
      RightStrafe();
      
    delay(1500);
    StopDrive();

    digitalWrite(A5, LOW);
  }
}


//Functions to handle robot movement
static void DriveForward() {
  analogWrite(MOTOR_ONE_ENABLE, HIGH);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  analogWrite(MOTOR_TWO_ENABLE, HIGH);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  analogWrite(MOTOR_THREE_ENABLE, HIGH);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  analogWrite(MOTOR_FOUR_ENABLE, HIGH);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}
static void DriveBackward() {
  analogWrite(MOTOR_ONE_ENABLE, HIGH);
  digitalWrite(MOTOR_ONE_SET, LOW);
  analogWrite(MOTOR_TWO_ENABLE, HIGH);
  digitalWrite(MOTOR_TWO_SET, LOW);
  analogWrite(MOTOR_THREE_ENABLE, HIGH);
  digitalWrite(MOTOR_THREE_SET, LOW);
  analogWrite(MOTOR_FOUR_ENABLE, HIGH);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
static void LeftStrafe() {
  analogWrite(MOTOR_ONE_ENABLE, HIGH);
  digitalWrite(MOTOR_ONE_SET, LOW);
  analogWrite(MOTOR_TWO_ENABLE, HIGH);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  analogWrite(MOTOR_THREE_ENABLE, HIGH);
  digitalWrite(MOTOR_THREE_SET, LOW);
  analogWrite(MOTOR_FOUR_ENABLE, HIGH);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}
static void RightStrafe() {
  digitalWrite(MOTOR_ONE_ENABLE, HIGH);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  digitalWrite(MOTOR_TWO_ENABLE, HIGH);
  digitalWrite(MOTOR_TWO_SET, LOW);
  digitalWrite(MOTOR_THREE_ENABLE, HIGH);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  digitalWrite(MOTOR_FOUR_ENABLE, HIGH);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
static void RotateLeft() {
  digitalWrite(MOTOR_ONE_ENABLE, HIGH);
  digitalWrite(MOTOR_ONE_SET, LOW);
  digitalWrite(MOTOR_TWO_ENABLE, HIGH);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  digitalWrite(MOTOR_THREE_ENABLE, HIGH);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  digitalWrite(MOTOR_FOUR_ENABLE, HIGH);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
static void RotateRight() {
  digitalWrite(MOTOR_ONE_ENABLE, HIGH);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  digitalWrite(MOTOR_TWO_ENABLE, HIGH);
  digitalWrite(MOTOR_TWO_SET, LOW);
  digitalWrite(MOTOR_THREE_ENABLE, HIGH);
  digitalWrite(MOTOR_THREE_SET, LOW);
  digitalWrite(MOTOR_FOUR_ENABLE, HIGH);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}
static void StopDrive() {
  digitalWrite(MOTOR_ONE_ENABLE, LOW);
  digitalWrite(MOTOR_ONE_SET, LOW);
  digitalWrite(MOTOR_TWO_ENABLE, LOW);
  digitalWrite(MOTOR_TWO_SET, LOW);
  digitalWrite(MOTOR_THREE_ENABLE, LOW);
  digitalWrite(MOTOR_THREE_SET, LOW);
  digitalWrite(MOTOR_FOUR_ENABLE, LOW);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
