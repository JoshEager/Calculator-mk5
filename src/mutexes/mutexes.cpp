#include "mutexes/mutexes.h"

#include <Arduino.h>

namespace mutexes {
    SemaphoreHandle_t serial_mutex;

    void initMutexes() {
        serial_mutex = xSemaphoreCreateMutex();
    }
}