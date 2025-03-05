#pragma once
#include <stdint.h>
#include <Arduino.h>

#include "../Config.h"

/**
 * @file L293D.h
 * @brief Header file for the L293D motor driver module.
 *
 * This file contains the initialization function for setting up the pins
 * and PWM settings for the L293D motor driver.
 */

 /**
     * @brief Initializes the motor driver pins and sets up PWM resolution and frequency.
     * 
     * This function configures the specified pins (D1_pin, D2_pin, EN_pin) as output pins.
     * It also sets the PWM resolution and frequency for the motor driver.
     * 
     * @tparam D1_pin The pin number for the first direction control.
     * @tparam D2_pin The pin number for the second direction control.
     * @tparam EN_pin The pin number for the enable control.
     * @tparam D1_logic The logic level for the first direction control.
     * @tparam EN_logic The logic level for the enable control.
*/
template<uint8_t D1_pin, uint8_t D2_pin, uint8_t EN_pin, uint8_t D1_logic, uint8_t EN_logic>
struct _L293D_Drive_hal{
   
     /** 
     * @brief Initializes the motor driver pins and PWM settings.
     *
     * This function sets the specified pins as output and configures the PWM
     * resolution and frequency for motor control.
     *
     */
    void init(){
        pinMode(D1_pin, OUTPUT);
        pinMode(D2_pin, OUTPUT);
        pinMode(EN_pin, OUTPUT);
        analogWriteResolution(MOT_PWM_RES_BITS);
        analogWriteFrequency(MOT_PWM_RES_FREQ);
    }

    /**
    * @brief Sets the power level for the motor.
    *
    * This function controls the motor's power level by setting the direction
    * and the PWM value based on the input power percentage.
    *
    * @param pwr The power level as a percentage (-100 to 100). Positive values
    *            indicate forward direction, and negative values indicate reverse
    *            direction.
    */
    void set_power(float pwr){
        if(pwr > 0){
            digitalWrite(D1_pin, D1_logic);
            digitalWrite(D2_pin, !D1_logic);
        }else{
            digitalWrite(D1_pin, !D1_logic);
            digitalWrite(D2_pin, D1_logic);
        }

        uint16_t pwm_val = (abs(pwr)/100) * ( (1<<MOT_PWM_RES_BITS) - 1);

        if(EN_logic == HIGH){
            analogWrite(EN_pin, pwm_val);
        }else{
            analogWrite(EN_pin, (1<<MOT_PWM_RES_BITS) - pwm_val);
        }
    }
};
