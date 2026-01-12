#pragma once

/**
 * @file pinout.h
 * @author Josh Eager
 * @brief Pin out information for the calculator
 * @date 2025-12-14
 * 
 */


// PINOUTS FOR THE LCD SCREEN ARE IN PLATFORMIO.INI IN ORDER TO PASS THEM TO TFT_eSPI!!! PLEASE CHECK THERE 


// Pinouts for the matrix keypad
#define ROW1_PIN 1 // Actually connects to the pin labeled ROW7 on the matrix pcb
#define ROW2_PIN 4 // ROW6
#define ROW3_PIN 5 // ROW5
#define ROW4_PIN 6 // ROW4
#define ROW5_PIN 7 // ROW3
#define ROW6_PIN 9 // ROW2
#define ROW7_PIN 14 // ROW1

#define COL1_PIN 21
#define COL2_PIN 18
#define COL3_PIN 17
#define COL4_PIN 2