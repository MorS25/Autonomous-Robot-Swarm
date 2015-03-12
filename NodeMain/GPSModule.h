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

class GPSModule {
  public:
    GPSModule();
    void GetData(void);
  private:
    boolean usingInterrupt = false;
    uint32_t timer = millis();
};

#endif
