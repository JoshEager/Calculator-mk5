#include <Arduino.h>
#include "config.h" // for the baud rate of serial
#include "interfaces/KeypadInterface.h"
#include "interfaces/ScreenInterface.h"
#include "mutexes/mutexes.h"
#include "tools/serial_print.h"


void setup()
{
  Serial.begin(BAUD_RATE);
  while (!Serial) ;
  
  mutexes::initMutexes();

  // Mutexes must be initialized before using serial_println() because it uses them. 
  serial_println("\nCalculator firmware version 1.0");

  KeypadInterface::begin();
  ScreenInterface::begin();

}

void loop()
{
  // Everything handled in tasks
  vTaskDelete(NULL);
}

