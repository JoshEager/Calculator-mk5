#include <Arduino.h>
#include "config.h"
#include "interfaces/KeypadInterface.h"

KeypadInterface *keypad_interface;
char pressedKey = '!';

std::array<std::array<char, COLS>, ROWS> key_mappings = {{
    {'a', 'b', 'c', 'd'},
    {'e', 'f', 'g', 'h'},
    {'i', 'j', 'k', 'l'},
    {'m', 'n', 'o', 'p'},
    {'q', 'r', 's', 't'},
    {'u', 'v', 'w', 'x'},
    {'y', 'z', '0', '1'},
}};
byte rowPins[] = {ROW1_PIN, ROW2_PIN, ROW3_PIN, ROW4_PIN, ROW5_PIN, ROW6_PIN, ROW7_PIN};
byte colPins[] = {COL1_PIN, COL2_PIN, COL3_PIN, COL4_PIN};

void setup()
{

  Serial.begin(BAUD_RATE);
  while (!Serial)
  {
    ;
  }

  keypad_interface = new KeypadInterface(key_mappings, rowPins, colPins, 50);
  keypad_interface->begin();
}

void loop()
{
  xQueueReceive(keypad_interface->key_queue, &pressedKey, KEYPAD_QUEUE_WAIT_TIME_MS);

  Serial.println(pressedKey);

  vTaskDelay(1000);
}
