# Project Overview

This is an embedded C++ project for the `freenove_esp32_s3_wroom` board. It uses the Arduino framework and PlatformIO. The goal of the project is to create a calculator, as suggested by the project name "CalculatorFirmware".

The project is structured to use a real-time operating system (FreeRTOS), with different tasks for handling hardware components.

## Key Technologies

*   **Platform:** `espressif32`
*   **Board:** `freenove_esp32_s3_wroom`
*   **Framework:** `arduino`
*   **Libraries:**
    *   `Keypad`: For reading input from a keypad.
    *   `TFT_eSPI`: For controlling a TFT display.
    *   `lvgl`: A graphics library for creating user interfaces.

## Architecture

The application is designed to be event-driven, using FreeRTOS tasks and queues for communication.

*   `main.cpp`: The entry point of the application. It initializes the `KeypadInterface` and then deletes the main task.
*   `KeypadInterface`: A module that handles keypad input. It uses a dedicated FreeRTOS task to poll the keypad and sends key presses to a queue.
*   `ScreenInterface`: A module that is intended to handle the display. It is currently not implemented.

## Building and Running

This project uses PlatformIO.

*   **Build:** `pio run`
*   **Upload:** `pio run --target upload`
*   **Monitor:** `pio device monitor`

You can also use the PlatformIO extension for VSCode to build, upload, and monitor the device.

## Development Conventions

*   The code is organized into modules within the `src` and `include` directories.
*   Interfaces to hardware components are abstracted into their own namespaces (e.g., `KeypadInterface`, `ScreenInterface`).
*   The project uses FreeRTOS for task management.
*   The project uses Doxygen-style comments for documentation.

## Learning Goals

This project is intended as a learning experience. When providing assistance, please:

*   **Explain Concepts:** Clearly explain the concepts behind any new code or changes.
*   **Show Your Work:** Detail the steps you are taking and the reasoning behind them.
*   **Provide Rationale:** Explain *why* a particular approach is chosen over alternatives.
