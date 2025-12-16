#include "interfaces/KeypadInterface.h"

#include <Arduino.h>
#include <Keypad.h>
#include <array>
#include "config.h"

KeypadInterface::KeypadInterface(std::array<std::array<const char, COLS>, ROWS> keys, byte *rowPins, byte *colPins, int polling_delay_ms)
{
    this->polling_delay_ms = polling_delay_ms;
    kpd = new Keypad(makeKeymap(keys.data()->data()), rowPins, colPins, ROWS, COLS);

    // Create a queue for storing the pressed keys
    key_queue = xQueueCreate(KEY_PRESS_QUEUE_LENGTH, sizeof(char));
}

void KeypadInterface::pollingTask()
{
    // Serial.println("Entered pollingTask()");
    // while (1)
    // {
    //     if (kpd->getKey())
    //     { // getKeys() checks for any key presses, but also populates kpd->key[] if there is any
    //         Serial.println("Keys changed!");
    //         for (int i = 0; i < LIST_MAX; i++)
    //         {
    //             if (kpd->key[i].kstate == PRESSED)
    //             {
    //                 xQueueSend(this->key_queue, &(kpd->key[i].kchar), pdMS_TO_TICKS(KEYPAD_QUEUE_WAIT_TIME_MS));
    //                 Serial.println(kpd->key[i].kchar);
    //             }
    //             else if (kpd->key[i].kstate == HOLD)
    //             {
    //                 xQueueSend(this->key_queue, &(kpd->key[i].kchar), pdMS_TO_TICKS(KEYPAD_QUEUE_WAIT_TIME_MS));
    //                 Serial.println(kpd->key[i].kchar);

    //             }
    //         }
    //     }
    //     vTaskDelay(this->polling_delay_ms);
    // }
    // Use the globally defined pin arrays for manual access (assuming your keypad object stored them)
    // Note: For simplicity, we are using the COL1_PIN and ROW1_PIN macros directly from pinout.h

    Serial.println("--- Starting Manual Pin Scan Test ---");

    // 1. Configure the Row Pin (ROW1_PIN: GPIO 33) as INPUT with PULLUP
    pinMode(ROW3_PIN, INPUT_PULLUP); 

    // 2. Configure the Column Pin (COL1_PIN: GPIO 17) as OUTPUT
    pinMode(COL1_PIN, OUTPUT);

    while (1)
    {
        // 3. Set the Column Pin LOW (This is what creates the short circuit condition)
        digitalWrite(COL1_PIN, LOW); 

        // 4. Read the Row Pin
        if (digitalRead(ROW3_PIN) == LOW) 
        {
            Serial.println("!!! KEY DETECTED on R1/C1 !!!");

            // Add a small delay/wait so it doesn't spam the key press
            while (digitalRead(ROW3_PIN) == LOW) {
                vTaskDelay(pdMS_TO_TICKS(10));
            }
        } 
        else 
        {
            // This will spam if no key is pressed, proving the task is running
            Serial.print("."); 
        }

        // 5. Restore Column Pin (Set HIGH) and wait
        digitalWrite(COL1_PIN, HIGH);
        vTaskDelay(pdMS_TO_TICKS(100)); // Poll every 100ms
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
    xTaskCreatePinnedToCore(
        pollingTaskEntry,
        "Keypad Driver - polling",
        4096,
        (void *)this,
        1,
        &polling_task_handle, 
        1);
}