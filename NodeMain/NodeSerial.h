#ifndef NodeSerial_h
#define NodeSerial_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//Initialize pins for Serial Communication
#define RECIEVE_PIN           2
#define TRANSMIT_PIN          3

//Initialize NUMBER defines
#define BIT_SERIAL_SPEED 8000

class NodeSerial {
  public:
    NodeSerial();
};

#endif
