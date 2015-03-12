#ifndef GPSModule_h
#define GPSModule_h

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define GPSECHO false

Adafruit_GPS GPS(&Serial);

boolean usingInterrupt = false;

class GPSModule {
  public:
    GPSModule();
    void GetData(void);
  private:
    uint32_t timer = millis();
};

#endif
