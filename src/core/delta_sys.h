#pragma once
#include "module/L293D.h"
#include "module/rotry_encoder.h"
#include "PID.h"
#include "core.h"
#include "debug_interface.h"
#include "../Config.h"

#define V_TO_ANGULAR_V_DIA(V, D)(2*V/D)
#define ANGULAR_V_TO_V_DIA(w, D)(w*D/2)


struct veh_state_t{
    float veh_spd_mm_s = 0;
    float veh_angV_rad_s = 0;
    float flw_angV_rad_s = 0;
    float frw_angV_rad_s = 0;
};

struct motor_power_t{
    float frw_MOT_power = 0;
    float flw_MOT_power = 0;
    float bcw_MOT_power = 0;
};

enum class veh_cntrlType{
    MOTORPOWER,
    WHEELSPEED,
    SPD_ANGV
};

static pulse_rotry_encoder<FRW_ENC_IN1, FRW_ENC_IN1_DEF_PINSTATE, FRW_ENC_IN1_EDGE> frw_ENC; //encoder right_wheel
static void FRW_ENC_IRQ(){
    frw_ENC.increment_pulse();
}

static pulse_rotry_encoder<FLW_ENC_IN1, FLW_ENC_IN1_DEF_PINSTATE, FLW_ENC_IN1_EDGE> flw_ENC; //encoder left_wheel
static void FLW_ENC_IRQ(){
    flw_ENC.increment_pulse();
}

class vehicle{
    private:
    _L293D_Drive_hal<FRW_MOT_D1, FRW_MOT_D2, FRW_MOT_EN, FRW_MOT_FRWRD_D1_LOGIC, FRW_MOT_EN_LOGIC> frw_MOT;
    _L293D_Drive_hal<FLW_MOT_D1, FLW_MOT_D2, FLW_MOT_EN, FLW_MOT_FRWRD_D1_LOGIC, FLW_MOT_EN_LOGIC> flw_MOT;
    _L293D_Drive_hal<BCW_MOT_D1, BCW_MOT_D2, BCW_MOT_EN, BCW_MOT_FRWRD_D1_LOGIC, BCW_MOT_EN_LOGIC> bcw_MOT;

    PID flw_spd_pid = PID(
        L_R_WHEEL_KP,
        L_R_WHEEL_KI,
        L_R_WHEEL_KD,
        (L_R_WHEEL_MAX_POWER - FLW_DCMOT_DEADZONE),
        0,
        FREQ_TO_PTIME(CNTRLLOOP_FREQ/CNTRLLOOP_VEHSENSORREAD_FRATIO)
    );

    PID frw_spd_pid = PID(
        L_R_WHEEL_KP,
        L_R_WHEEL_KI,
        L_R_WHEEL_KD,
        (L_R_WHEEL_MAX_POWER - FRW_DCMOT_DEADZONE),
        0,
        FREQ_TO_PTIME(CNTRLLOOP_FREQ/CNTRLLOOP_VEHSENSORREAD_FRATIO)
    );

    const uint16_t control_loop_freq = CNTRLLOOP_FREQ/CNTRLLOOP_VEHCNTRLLOOP_FRATIO;
    veh_state_t current;
    veh_state_t target;
    motor_power_t motor_power;
    veh_cntrlType control_type;
    void kinematic_map();

    public:
    void vehicle_init();
    void sensors_read();
    void control_loop();
    void motorPower_update();
    veh_state_t get_vehicleState();
    veh_state_t get_vehicleTarget();
    motor_power_t get_motorPower();
    void set_vehicleTarget(veh_state_t &_target, veh_cntrlType _control_type);
    void set_motorPower(motor_power_t &_motorPowers);
};


inline vehicle *vehicle_laneBlazer;