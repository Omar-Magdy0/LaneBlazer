#pragma once
#include "../Config.h"
#include "core.h"

/*
the way to implement configurations and settings using macros defined in the config file or similar config files

#if INTEGRAL_ANTIWINDUP == NO_WINDUP
/// enable integral windup

#elif INTEGRAL_ANTIWINDUP == CLAMP

#elif INTEGRAL_ANTIWINDUP == CLEAR

#elif INTEGRAL_ANTIWINDUP == Back-calculation
#endif


#if ENABLED()

*/

/// @class PID
/// A simple PID control block with basic functionality and min_out and max_out support for overflow prevention and integral term anti-windup , advi
class PID{
  private:
    float _Kp;
    float _Ki;
    float _Kd;
    float _max_out = 0;
    float _min_out = 0;
    float _dt;

    float _last_e;
    float _integral_e;
    float _setpoint;
    float last_out;
    bool is_saturated = false;
  public:
    PID(float Kp,
        float Ki,
        float Kd,
        float max_out,
        float min_out,
        float dt);

    void set_Kp(float Kp);
    void set_Ki(float Ki);
    void set_Kd(float Kd);
    void set_dt(float dt);
    float get_Kp();
    float get_Ki();
    float get_Kd();
    float get_dt();
    void set_setpoint(float setpoint);

    /// @brief the function for output and terms update based on feedback 
    /// @param feedback
    /// @return the output from the pid controller
    float PID_EXECUTE(float feedback);
    void PID_RESET();

};


