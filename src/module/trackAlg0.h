/**
 * @file trackAlg0.h
 * @brief Header file for the track algorithm module.
 * 
 * This file contains the definitions and declarations for the track algorithm
 * used in the LaneBlazer project. The algorithm controls the vehicle's movement
 * based on IR sensor readings.
 * 
 * @project LaneBlazer_V-1_arduinoCore
 * @version 1.0
 * @date 2023-10-01
 * 
 * @note This file is part of the LaneBlazer project.
 */

 #pragma once

 #include "core/delta_sys.h"
 #include "IRsensor.h"
 #include "core/core.h"
 
 #define FRWRD_SS 6
 #define FRWRD_FS 5
 #define HARD_FRWRD_LEFT 4
 #define HARD_FRWRD_RIGHT 3
 #define FRWRD_RIGHT 2
 #define FRWRD_LEFT 1
 #define STOP 0
 #define BCKWRD_LEFT -1
 #define BCKWRD_RIGHT -2
 #define HARD_BCKWRD_RIGHT 3
 #define HARD_BCKWRD_LEFT 4
 #define BCKWRD -5 
 #define ERR 0xFF
 
 #define FR_IR_BIT 0
 #define FL_IR_BIT 1
 #define FFC_IR_BIT 2
 
 #define CROSS_THRESH(c,t)(c > t)
 #define algTickFreq CNTRLLOOP_FREQ
 #define pdMsToAlgTicks(ms)((ms)* algTickFreq / 1000)
 
 /**
  * @enum currentState
  * @brief Enum to represent the current state of the vehicle.
  */
 enum class currentState{
 
 };
 
 /**
  * @struct state_tickCount_t
  * @brief Structure to hold the current and target tick counts for a state.
  */
 struct state_tickCount_t{
     uint16_t current; /**< Current tick count */
     uint16_t target;  /**< Target tick count */
 };
 
 /**
  * @class trackAlg
  * @brief Class to implement the track algorithm for the vehicle.
  */
 struct trackAlg{
     private:
         vehicle *_vehicle; /**< Pointer to the vehicle object */
         IRsensors_t *irsensors; /**< Pointer to the IR sensors object */
         uint8_t edgeBool; /**< Boolean to describe edges crossing, each bit for a boolean */
         uint8_t colorCommand; /**< To detect color commands and give them top priority */
         int8_t vehicle_moveMode; /**< Describe vehicle state in simple terminology like (Moving Forward, Backward, Steering(right/left), Hard Steering, Stopped) */
 
         /**
          * @brief Set the vehicle's movement mode.
          * 
          * @param mode The movement mode to set.
          */
         void move_mode(int8_t mode);
 
     public:
         /**
          * @brief Initialize the track algorithm with the vehicle and IR sensors.
          * 
          * @param _veh Pointer to the vehicle object.
          * @param ir Pointer to the IR sensors object.
          */
         void init(vehicle *_veh, IRsensors_t *ir);
 
         /**
          * @brief Read the IR sensor values.
          */
         void readIr();
 
         /**
          * @brief Run the track algorithm to control the vehicle's movement.
          */
         void run();
 
         /**
          * @brief Get the edge boolean value.
          * 
          * @return The edge boolean value.
          */
         uint8_t get_edgeBool();
 
         /**
          * @brief Get the vehicle's movement mode.
          * 
          * @return The vehicle's movement mode.
          */
         int8_t get_vehicleMoveMode();
 };
 