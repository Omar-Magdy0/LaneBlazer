
/**
 * @file rotry_encoder.h
 * @brief Rotary encoder implementation for pulse counting and angular velocity calculation.
 */
#pragma once
#include <stdint.h>
#include <math.h>
#include <Arduino.h>
#include "../Config.h"
#include "core/debug_interface.h"

#define BACKWARD -1
#define FORWARD 1

/**
 * @struct encoder_data_t
 * @brief Structure to store encoder data.
 */
struct encoder_data_t{
    float angV_rad_s;
    float ang_rad;
    uint16_t pulses;
};


/**
 * @class pulse_rotry_encoder
 * @brief Template class for a rotary encoder.
 * 
 * @tparam pin The pin number the encoder is attached to.
 * @tparam mode The pin mode (INPUT, INPUT_PULLUP, etc.).
 * @tparam edge The triggering edge (RISING, FALLING, etc.).
 */
template<uint8_t pin,uint8_t mode, uint8_t edge>
class pulse_rotry_encoder{
    private:
    volatile uint16_t pulses_count = 0; ///< Count of pulses detected.
    volatile uint32_t last_pulse_time = 0; ///< Timestamp of last detected pulse.
    volatile uint32_t prev_pulse_time = 0; ///< Timestamp of previous pulse.
    int8_t last_direction = FORWARD; ///< Last detected direction of rotation.

    public:
        /**
        * @brief Initializes the encoder pin.
        */
        void init(){
            pinMode(pin, mode);
        };

         /**
        * @brief Reads and resets the pulse count.
        * @return Signed pulse count based on direction.
        */
        uint16_t read_pulses(){
            uint16_t temp = pulses_count;
            pulses_count = 0;
            return temp*last_direction;
        }

        /**
        * @brief Computes encoder data (velocity and position).
        * @param pulses_per_rev Number of pulses per revolution.
        * @param check_dt Time interval for velocity calculation.
        * @return Encoder data structure.
        */
        encoder_data_t get_encoder_data(uint16_t pulses_per_rev, float check_dt){
            uint32_t current_time = micros();
            encoder_data_t encoder_data;
            
            // Check if encoder has stopped
            if(pulses_count > 0){
                if (current_time - last_pulse_time > ENCODER_TIMEOUT_US) {
                    encoder_data.angV_rad_s = 0;
                    encoder_data.ang_rad = pulses_count*2.0*M_PI* last_direction;
                    return encoder_data; // No recent pulses, assume speed = 0
                }
            
                uint32_t pulse_dt_us = last_pulse_time - prev_pulse_time;
                if (pulse_dt_us < ENCODER_MIN_DT_US) pulse_dt_us = ENCODER_MIN_DT_US; // Avoid division by zero
            
                if (pulses_count <= MIN_PULSES_LS){
                    // Time between last two pulses (low speed method)
                    // If we only received very few pulses recently work with the last time difference
                    encoder_data.angV_rad_s = (2.0 * M_PI * last_direction) / ((pulse_dt_us / 1000000.0) * pulses_per_rev);
                }else{
                    // High-speed method: Use pulse counting over fixed time 
                    encoder_data.angV_rad_s = (pulses_count * 2.0 * M_PI * last_direction) / (pulses_per_rev * check_dt);
                }
                // Calculate angle
                encoder_data.ang_rad = pulses_count*2.0*M_PI* last_direction;
                // Reset pulse counter
                encoder_data.pulses = pulses_count;
                pulses_count = 0;
                return encoder_data;
            }else{
                encoder_data.angV_rad_s = 0;
                encoder_data.ang_rad = 0;
                encoder_data.pulses = pulses_count;
                return encoder_data;
            }
        }

        /**
        * @brief Sets the rotation direction.
        * @param dir Direction (FORWARD or BACKWARD).
        */
        void encoder_set_direction(int8_t dir){
            last_direction = dir;
        }

        
        /**
         * @brief Increments the pulse count and updates timing.
        */
        inline void increment_pulse(){
            prev_pulse_time = last_pulse_time;
            last_pulse_time = micros();
            pulses_count++;
        }
};


