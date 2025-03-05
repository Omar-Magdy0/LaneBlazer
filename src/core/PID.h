/**
 * @file PID.h
 * @brief Header file for the PID controller class.
 *
 * This file contains the definition of the PID class, which implements a simple PID control block with basic functionality,
 * including min_out and max_out support for overflow prevention and integral term anti-windup.
 */

#pragma once

#include "../Config.h"
#include "core.h"
#include "debug_interface.h"

/**
 * @class PID
 * @brief A simple PID control block with basic functionality.
 *
 * This class implements a PID controller with support for overflow prevention and integral term anti-windup.
 */
class PID {
private:
  float _Kp;         ///< Proportional gain
  float _Ki;         ///< Integral gain
  float _Kd;         ///< Derivative gain
  float _max_out;    ///< Maximum output value
  float _min_out;    ///< Minimum output value
  float _dt;         ///< Time step

  float _last_e;     ///< Last error value
  float _integral_e; ///< Integral of error
  float _setpoint;   ///< Desired setpoint
  float last_out;    ///< Last output value
  bool is_saturated; ///< Flag indicating if the output is saturated

public:
  /**
   * @brief Constructor for the PID class.
   * @param Kp Proportional gain
   * @param Ki Integral gain
   * @param Kd Derivative gain
   * @param max_out Maximum output value
   * @param min_out Minimum output value
   * @param dt Time step
   */
  PID(float Kp, float Ki, float Kd, float max_out, float min_out, float dt);

  /**
   * @brief Set the proportional gain.
   * @param Kp Proportional gain
   */
  void set_Kp(float Kp);

  /**
   * @brief Set the integral gain.
   * @param Ki Integral gain
   */
  void set_Ki(float Ki);

  /**
   * @brief Set the derivative gain.
   * @param Kd Derivative gain
   */
  void set_Kd(float Kd);

  /**
   * @brief Set the time step.
   * @param dt Time step
   */
  void set_dt(float dt);

  /**
   * @brief Get the proportional gain.
   * @return Proportional gain
   */
  float get_Kp();

  /**
   * @brief Get the integral gain.
   * @return Integral gain
   */
  float get_Ki();

  /**
   * @brief Get the derivative gain.
   * @return Derivative gain
   */
  float get_Kd();

  /**
   * @brief Get the time step.
   * @return Time step
   */
  float get_dt();

  /**
   * @brief Set the desired setpoint.
   * @param setpoint Desired setpoint
   */
  void set_setpoint(float setpoint);

  /**
   * @brief Update the output and terms based on feedback.
   * @param feedback Feedback value
   * @return Output from the PID controller
   */
  float PID_EXECUTE(float feedback);

  /**
   * @brief Reset the PID controller.
   */
  void PID_RESET();
};
