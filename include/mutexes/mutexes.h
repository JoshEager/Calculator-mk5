#pragma once

#include <Arduino.h>

/**
 * @brief Contains a namespace with mutex related functions
 * 
 */
 namespace mutexes {
    extern SemaphoreHandle_t serial_mutex;

    void initMutexes();
 }