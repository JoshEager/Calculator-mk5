#include "interfaces/KeypadInterface.h"

#include <Arduino.h>
#include <Keypad.h>
#include <stdexcept>
#include <array>
#include "config.h"

KeypadInterface::KeypadInterface(std::array<std::array<const char, COLS>, ROWS> keys, byte *rowPins, byte *colPins) {
    kpd = new Keypad(makeKeymap(keys.data()->data()), rowPins, colPins, ROWS, COLS);
}


void KeypadInterface::pollingTask()
{
    while (1) {


        vTaskDelay(polling_rate_ms);
    }
}

void KeypadInterface::pollingTaskEntry(void *pvParameters)
{
    KeypadInterface *inst = (KeypadInterface *)pvParameters;
    inst->pollingTask();
    vTaskDelete(NULL);
}

void KeypadInterface::begin()
{
    // Start the polling task. The polling task puts the keys it reads into the key press queue.
    // Note: The task entry function must be a class method and not a normal instance method
    // because of compatibily with the c api for freeRTOS.
    xTaskCreate(
        pollingTaskEntry,
        "Keypad Driver - polling",
        2048,
        (void *)this,
        1,
        &polling_task_handle);
}