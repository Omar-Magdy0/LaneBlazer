#pragma once
#include <Arduino.h>
#include <stdint.h>
#include "Config.h"

/**
 * @brief Structure to hold IR sensor readings.
 */
struct IRsensors_readings_t {
    uint16_t FR_val;  ///< Front Right IR sensor value
    uint16_t FL_val;  ///< Front Left IR sensor value
    uint16_t FFC_val; ///< Front Center IR sensor value
};

/**
 * @brief Class to manage IR sensors.
 */
struct IRsensors_t {
private:
    IRsensors_readings_t sensor_readings; ///< Holds the current sensor readings

public:
    /**
     * @brief Reads the values from the IR sensors and stores them in sensor_readings.
     */
    void read() {
        sensor_readings.FR_val = analogRead(FR_IR_IN);
        sensor_readings.FL_val = analogRead(FL_IR_IN);
        sensor_readings.FFC_val = analogRead(FFC_IR_IN);
    }

    /**
     * @brief Returns the current IR sensor readings.
     * 
     * @return IRsensors_readings_t The current sensor readings.
     */
    IRsensors_readings_t getReading() {
        return sensor_readings;
    }

    /**
     * @brief Initializes the IR sensors by setting the pin modes and analog read resolution.
     */
    void init() {
        pinMode(FR_IR_IN, INPUT_ANALOG);
        pinMode(FL_IR_IN, INPUT_ANALOG);
        pinMode(FFC_IR_IN, INPUT_ANALOG);
        analogReadResolution(ANALOG_RES_BITS);
    }
};

