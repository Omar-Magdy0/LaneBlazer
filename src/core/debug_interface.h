/**
 * @file debug_interface.h
 * @brief Debug interface for the LaneBlazer V-1 Arduino core.
 *
 * This file provides debugging functionalities for the LaneBlazer V-1 Arduino core.
 * It includes functions to output debug information through a specified UART port.
 */

#pragma once

#include "Arduino.h"
#include <stdint.h>
#include "../Config.h"
#include <string>
#include <stdarg.h>

#define UART1 1

#if defined(DEBUG_) && ENABLED(DEBUG_)
#if DEBUG_PORT == UART1

/**
 * @brief Outputs a formatted debug message with a variable.
 *
 * This function formats a debug message with a variable and sends it to the specified UART port.
 *
 * @tparam var_type The type of the variable to be included in the debug message.
 * @param str The format string for the debug message.
 * @param var The variable to be included in the debug message.
 */
template <typename var_type>
static void debug_out(const char* str, var_type var)
{
    char f_str[DEBUG_BUFFER_SIZE];
    snprintf(f_str, DEBUG_BUFFER_SIZE, str, var);
    Serial1.println(f_str);
}

/**
 * @brief Outputs a debug message.
 *
 * This function sends a debug message to the specified UART port.
 *
 * @param str The debug message to be sent.
 */
static void debug_out(const char* str)
{
    Serial1.println(str);
}

#endif 

#else 
#define debug_out(c) do {} while (0)
#define debug_out(c, d) do {} while (0)
#endif

