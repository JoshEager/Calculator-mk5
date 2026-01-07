#include "tools/serial_print.h"

#include <Arduino.h>
#include "mutexes/mutexes.h"


void serial_println(String str) {
    xSemaphoreTake(mutexes::serial_mutex, 1000 / portTICK_PERIOD_MS);
    Serial.println(str);
    xSemaphoreGive(mutexes::serial_mutex);
}