/**
 * @file debug.h
 * @author Josh Eager
 * @brief contians definitions for tools for debugging
 * @date 2026-01-03
 * 
 */

#include "tools/serial_print.h"
#include "config.h" 

#ifdef DEBUG
    #define PRINTDBG(x) serial_println(x)
#else
    #define PRINTDBG(x)
#endif