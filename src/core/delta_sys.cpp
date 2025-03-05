#include "delta_sys.h"

void vehicle::vehicle_init()
{
    frw_MOT.init();
    flw_MOT.init();
    bcw_MOT.init();
    flw_ENC.init();
    frw_ENC.init();
    attachInterrupt(FRW_ENC_IN1, FRW_ENC_IRQ, FRW_ENC_IN1_EDGE);
    attachInterrupt(FLW_ENC_IN1, FLW_ENC_IRQ, FLW_ENC_IN1_EDGE);
}

void vehicle::sensors_read()
{
    //compute current states based on sensor readings
    current.frw_angV_rad_s = frw_ENC.get_encoder_data(FRW_ENC_PULSES_PER_REV, FREQ_TO_PTIME(control_loop_freq)).angV_rad_s;
    current.flw_angV_rad_s = flw_ENC.get_encoder_data(FLW_ENC_PULSES_PER_REV, FREQ_TO_PTIME(control_loop_freq)).angV_rad_s;

    current.veh_spd_mm_s = (current.frw_angV_rad_s + current.flw_angV_rad_s) * FRW_WHEEL_DIAMETER_MM / 4.0;
    current.veh_angV_rad_s = (current.frw_angV_rad_s - current.flw_angV_rad_s) * (FRW_WHEEL_DIAMETER_MM/WHEEL_TRACK);
}

void vehicle::kinematic_map()
{
    // Compute target wheel angular velocity
    target.frw_angV_rad_s = (target.veh_spd_mm_s + (target.veh_angV_rad_s * WHEEL_TRACK / 2)) / (FRW_WHEEL_DIAMETER_MM / 2);
    target.flw_angV_rad_s = (target.veh_spd_mm_s - (target.veh_angV_rad_s * WHEEL_TRACK / 2)) / (FLW_WHEEL_DIAMETER_MM / 2);    
}

void vehicle::control_loop()
{
    if(control_type == veh_cntrlType::SPD_ANGV || control_type == veh_cntrlType::WHEELSPEED){
        // Set wheel speeds using PID control
        //MAINtain the power output with no direction info
        frw_spd_pid.set_setpoint(abs(target.frw_angV_rad_s));
        flw_spd_pid.set_setpoint(abs(target.flw_angV_rad_s));
        //APPLY some FUZZY logic + FEEDFORWARD + PID
        motor_power.frw_MOT_power = frw_spd_pid.PID_EXECUTE(abs(current.frw_angV_rad_s)) + FRW_DCMOT_DEADZONE + L_R_WHEEL_FF*abs(target.veh_angV_rad_s);
        motor_power.flw_MOT_power = flw_spd_pid.PID_EXECUTE(abs(current.flw_angV_rad_s)) + FLW_DCMOT_DEADZONE + L_R_WHEEL_FF*abs(target.veh_angV_rad_s);
        if(motor_power.frw_MOT_power > 100)motor_power.frw_MOT_power = 100;
        if(motor_power.flw_MOT_power > 100)motor_power.flw_MOT_power = 100;
        if( (motor_power.frw_MOT_power - FRW_DCMOT_DEADZONE) < L_R_MINOUTPUT_THRESH){
            motor_power.frw_MOT_power = 0;
        }
        if( (motor_power.flw_MOT_power - FLW_DCMOT_DEADZONE) < L_R_MINOUTPUT_THRESH){
            motor_power.flw_MOT_power = 0;
        }
            //Update directions here
        motor_power.frw_MOT_power = motor_power.frw_MOT_power * SIGN(target.frw_angV_rad_s);
        motor_power.flw_MOT_power = motor_power.flw_MOT_power * SIGN(target.flw_angV_rad_s);
            // Set back wheel power (if needed for thrust)
        motor_power.bcw_MOT_power = (motor_power.frw_MOT_power + motor_power.flw_MOT_power) / 2;
    }
}

void vehicle::motorPower_update()
{
    #if FRW_ENCODER_TYPE == PULSE
    // Set encoder expected directions based on reading(since we control the motor direction in this scheme)
    frw_ENC.encoder_set_direction(SIGN_PBIAS(motor_power.frw_MOT_power));
    #endif
    #if FLW_ENCODER_TYPE == PULSE
    flw_ENC.encoder_set_direction(SIGN_PBIAS(motor_power.flw_MOT_power));
    #endif
    // Apply power to motors
    frw_MOT.set_power(motor_power.frw_MOT_power);
    flw_MOT.set_power(motor_power.flw_MOT_power);
    bcw_MOT.set_power(motor_power.bcw_MOT_power);
}

veh_state_t vehicle::get_vehicleState()
{
    return current;
}

veh_state_t vehicle::get_vehicleTarget()
{
    return target;
}

motor_power_t vehicle::get_motorPower()
{
    return motor_power;
}

void vehicle::set_motorPower(motor_power_t &_motorPowers)
{
    control_type = veh_cntrlType::MOTORPOWER;
    motor_power = _motorPowers;
}

void vehicle::set_vehicleTarget(veh_state_t &_target, veh_cntrlType _control_type)
{
    control_type = _control_type;
    target = _target;
    if(control_type == veh_cntrlType::SPD_ANGV)kinematic_map();   
}


