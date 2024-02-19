
#ifndef ARDUINO_HANDLER_H
#define ARDUINO_HANDLER_H
#include <Arduino.h>

bool hasTimeElapsed(unsigned long startTime, int waitTimeInSeconds);
void handleTimeEvents(unsigned long currentTime, unsigned long lastPrintedTime, unsigned long startTime);


#endif
