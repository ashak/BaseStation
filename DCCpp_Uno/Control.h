#ifndef CONTROL_H
#define CONTROL_H
#include "Arduino.h"
#include "PacketRegister.h"
#include "Config.h"

const int numReadings = 5;

struct Control{
//  static volatile RegisterList *mRegs;
  int loco_address;
  int dir_pin;
  int speed_pin;
  int spd;
  int dir;
  int readings[numReadings];      // the readings from the analog input
  int readIndex;              // the index of the current reading
  int total;                  // the running total
  int average;                // the average
  bool enabled;
//  Control(int, int, int);
};

void initControls(volatile RegisterList *, int);
Control* createControl();
Control** getControls();
void enableControl(int, int, int, int);
void handleControlChanges();
#endif
