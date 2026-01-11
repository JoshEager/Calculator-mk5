#include "interfaces/KeypadInterface.h"

#include <Arduino.h>
#include <Keypad.h>
#include "config.h"
#include "tools/debug.h"

namespace KeypadInterface
{

    _KeypadInterface::_KeypadInterface(char keys[ROWS][COLS], byte *rowPins, byte *colPins, int polling_delay_ms)
    {
        this->polling_delay_ms = polling_delay_ms;
        kpd = new Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

        // Create a queue for storing the pressed keys
        key_queue = xQueueCreate(KEY_PRESS_QUEUE_LENGTH, sizeof(char));
    }

    void _KeypadInterface::pollingTask()
    {
        PRINTDBG("Entered pollingTask()");
        while (1)
        {
            if (kpd->getKey())
            { // getKeys() checks for any key presses, but also populates kpd->key[] if there is any
                for (int i = 0; i < LIST_MAX; i++)
                {
                    if (kpd->key[i].kstate == PRESSED)
                    {
                        xQueueSend(this->key_queue, &(kpd->key[i].kchar), pdMS_TO_TICKS(KEYPAD_QUEUE_WAIT_TIME_MS));
                        PRINTDBG(String("Key Pressed: ") + (int)kpd->key[i].kchar);
                    }
                    else if (kpd->key[i].kstate == HOLD)
                    {
                        xQueueSend(this->key_queue, &(kpd->key[i].kchar), pdMS_TO_TICKS(KEYPAD_QUEUE_WAIT_TIME_MS));
                        PRINTDBG(String("Key Held: ") + (int)kpd->key[i].kchar);
                    }
                }
            }
            vTaskDelay(this->polling_delay_ms / portTICK_PERIOD_MS);
        }
    }

    void _KeypadInterface::pollingTaskEntry(void *pvParameters)
    {
        _KeypadInterface *inst = (_KeypadInterface *)pvParameters;
        inst->pollingTask();
        vTaskDelete(NULL);
    }

    void _KeypadInterface::begin()
    {
        // Start the polling task. The polling task puts the keys it reads into the key press queue.
        // Note: The task entry function must be a class method and not a normal instance method
        // because of compatibily with the c api for freeRTOS.
        xTaskCreate(
            pollingTaskEntry,
            "Keypad Driver - polling",
            4096,
            (void *)this,
            1,
            &polling_task_handle);
    }

    static char key_mappings[ROWS][COLS] = {
        {71, 72, 73, 74},
        {61, 62, 63, 64},
        {51, 52, 53, 54},
        {41, 42, 43, 44},
        {31, 32, 33, 34},
        {21, 22, 23, 24},
        {11, 12, 13, 14},
    };
    static byte rowPins[] = {ROW1_PIN, ROW2_PIN, ROW3_PIN, ROW4_PIN, ROW5_PIN, ROW6_PIN, ROW7_PIN};
    static byte colPins[] = {COL1_PIN, COL2_PIN, COL3_PIN, COL4_PIN};

    _KeypadInterface *keypad_interface = new _KeypadInterface(key_mappings, rowPins, colPins, 50);



    char getKey()
    {
        static char key;

        if (xQueueReceive(keypad_interface->key_queue, &key, 0) == pdTRUE)
        {
            return key;
        }
        else
        {
            return 0; // NUL character, meaning that no character was on the queue
        }
    }

    void begin() {
        keypad_interface->begin();
    }

} // namespace KeypadInterface