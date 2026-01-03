#pragma once

#include <Keypad.h>
#include <Arduino.h>
#include <array>
#include "config.h"

class KeypadInterface 
{
private:
    int polling_delay_ms;
    Keypad* kpd;

    TaskHandle_t polling_task_handle;
    

    void pollingTask();

public:
    KeypadInterface(std::array<std::array<char, COLS>, ROWS> keys, byte *rowPins, byte *colPins, int polling_delay_ms);

    QueueHandle_t key_queue;

    void begin();
    static void pollingTaskEntry(void *pvParameters);
};