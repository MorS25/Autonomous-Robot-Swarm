//PREPROCESSOR
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

//Define individual node speeds
#define NODE_ONE              245
#define NODE_TWO              255
#define NODE_THREE            255

#define motorSpeed  NODE_ONE

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
  Serial.begin(115200);

  //Initialize all Node Data variables
  nodeData.nodeState = WAITING_PC_CMD;
  nodeData.gpsLat = 0;
  nodeData.gpsLong = 0;
}

void loop(void) {
  DriveForward();
}

void DriveForward(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  analogWrite(MOTOR_TWO_ENABLE, motorSpeed);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}
void DriveBackward(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, LOW);
  analogWrite(MOTOR_TWO_ENABLE, motorSpeed);
  digitalWrite(MOTOR_TWO_SET, LOW);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, LOW);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
void DriveLeft(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, LOW);
  analogWrite(MOTOR_TWO_ENABLE, motorSpeed);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, LOW);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}
void DriveRight(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  analogWrite(MOTOR_TWO_ENABLE, motorSpeed);
  digitalWrite(MOTOR_TWO_SET, LOW);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
void RotateLeft(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, LOW);
  analogWrite(MOTOR_TWO_ENABLE, motorSpeed);
  digitalWrite(MOTOR_TWO_SET, HIGH);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, HIGH);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
void RotateRight(void) {
  analogWrite(MOTOR_ONE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_ONE_SET, HIGH);
  analogWrite(MOTOR_TWO_ENABLE, motorSpeed);
  digitalWrite(MOTOR_TWO_SET, LOW);
  analogWrite(MOTOR_THREE_ENABLE, motorSpeed);
  digitalWrite(MOTOR_THREE_SET, LOW);
  analogWrite(MOTOR_FOUR_ENABLE, motorSpeed);
  digitalWrite(MOTOR_FOUR_SET, HIGH);
}
void DriveStop(void) {
  digitalWrite(MOTOR_ONE_ENABLE, LOW);
  digitalWrite(MOTOR_ONE_SET, LOW);
  digitalWrite(MOTOR_TWO_ENABLE, LOW);
  digitalWrite(MOTOR_TWO_SET, LOW);
  digitalWrite(MOTOR_THREE_ENABLE, LOW);
  digitalWrite(MOTOR_THREE_SET, LOW);
  digitalWrite(MOTOR_FOUR_ENABLE, LOW);
  digitalWrite(MOTOR_FOUR_SET, LOW);
}
