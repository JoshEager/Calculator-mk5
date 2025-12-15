#pragma once

#include <Keypad.h>
#include <Arduino.h>
#include <array>
#include "config.h"

class KeypadInterface
{
private:
    int polling_rate_ms;
    Keypad* kpd;

    TaskHandle_t polling_task_handle;
    QueueHandle_t key_queue;

    void pollingTask();

public:
    KeypadInterface(std::array<std::array<const char, COLS>, ROWS> keys, byte *rowPins, byte *colPins);

    void begin();
    static void pollingTaskEntry(void *pvParameters);
};