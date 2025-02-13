#include "PID.h"

PID::PID(float Kp, float Ki, float Kd, float max_out, float min_out, float dt)
{
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
  _max_out = max_out;
  _min_out = min_out;
  _dt = dt;
}

void PID::set_Kp(float Kp)
{
  _Kp = Kp;
}

void PID::set_Ki(float Ki)
{
  _Ki = Ki;
}

void PID::set_Kd(float Kd)
{
  _Kd = Kd;
}

void PID::set_dt(float dt)
{
  _dt = dt;
}

float PID::get_Kp()
{
  return _Kp;
}

float PID::get_Ki()
{
  return _Ki;
}

float PID::get_Kd()
{
  return _Kd;
}

float PID::get_dt(){
  return _dt;
}


void PID::set_setpoint(float setpoint)
{
  _setpoint = setpoint;
}

float PID::PID_EXECUTE(float feedback)
{
  float output;
  float e = feedback - _setpoint;
  
  if(!is_saturated){
    _integral_e += e*_dt;
  }
  float _derivative_e = (e - _last_e) / _dt; 
  output = _Kp*e + _Ki*_integral_e + _Kd*_derivative_e;

  if(output >= _max_out){
    output = _max_out;
    is_saturated = true;
  }else if (output <= _min_out){
    output = _min_out;
    is_saturated = true;
  }else{
    is_saturated = false;
  }

  _last_e = e;
  return output;
}

void PID::PID_RESET()
{
  _integral_e = 0;
  _last_e = 0;
}
